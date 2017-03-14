//Board.cpp
//
#include "Board.hpp"


/**********************Actions***********************/

//Returns True if Successful
bool Board::move(Move* move){
	int col = move->position().first;
	int row = move->position().second;

	//Validate Input
	if(!validPosition(move->position()))
		return false;

	//Make sure valid color
	if(move->color() == EMPTY) return false;

	//Make sure space is empty
	if(board[col][row] != EMPTY) return false;

	//If valid, update and return success
	board[col][row] = move->color();
	in++;

	this->print();
	move->print();

	return true;
}


/********************Inquiries************************/

bool Board::isFull(){return (in >= maxcap);}

//Find the Best Possible Move Given a Color
Move* Board::bestMove(Color color){

	//Record Keeping for the Best Possible Move
	Position best = Position(0,0);
	int bscore = score(best, color);
	int nscore;
	Position npos;

	//Check all spots for the best move
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			npos = Position(i,j);
			nscore = score(npos, color);
			if(nscore > bscore){
				bscore = nscore;
				best = npos;
			}
		}
	}

	return new Move(best, bscore, color);
}

//Find the score of the position on the board
int Board::score(Position pos, Color color){
	int score = 0;
	
	//Keep Track of all consecutive pieces in all directions
	std::vector<int> total = std::vector<int>();

	//Check if the spot is open
	if(!validPosition(pos)) return -1;
	if(get(pos) != EMPTY) return -1;

	//Find Consecutive pieces in All Directions
	Dir dirs[8] = {UL,UR, LL, LR, UP, DOWN, LEFT, RIGHT};
	for(int i=0; i<8; i++){
		scoreDirection(pos, color, dirs[i], &total);
	}

	//Calculate Score
	for(unsigned int i=0; i<total.size(); i++){
		score += pow(10, total[i]);
	}

	return score;
}




//Determine if position given is valid on the board
bool Board::validPosition(Position pos){
	if(pos.first >= 0 && 
	   pos.first < size &&
	   pos.second >= 0 &&
	   pos.second < size)
	   return true;
	else return false;
}

//Determines if a move is valid
bool Board::validMove(Move* move){
	if(move==NULL || (move->color() == EMPTY) || !validPosition(move->position()) || (get(move->position()) != EMPTY))
		return false;
	else return true;
}

Color Board::get(Position pos){
	return board[pos.first][pos.second];
}

Color Board::winner(){
	Dir dirs[8] = {UL,UR,LL,LR,UP,DOWN,LEFT,RIGHT};
	Position pos;
	Position cursor;
	Color col;
	bool found;

	//Parse Vertical Winners
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++){

			//Get the Current position
			pos = Position(i,j);
			col = get(pos);

			//If the color found is empty, there is no winner in this position
			if(col == EMPTY) continue;

			for(int k=0; k<8; k++){
				//Set the origin
				Direction dir = Direction(pos);
				found = true;

				//Check the direction for 5 in a rows
				for(int l=0; l<4; l++){
					cursor = dir.next(dirs[k]);
					if(!validPosition(cursor) || get(cursor) != col){
						found = false;
						break;
					}
				}

				if(found) return col;
			}

		}


	return EMPTY;
}





/**********************Setup / Teardown ************/

//Create a new empty board
Board::Board(int size) : size(size) {
	std::cout << "Size: "<<size<<", Depth: 1"<<std::endl;

	//Instantiate the board
	this->board = new Color*[size];
	for(int i=0; i<size; i++){
		this->board[i] = new Color[size];

		//Set values equal to EMPTY
		for(int j=0; j<size; j++)
			this->board[i][j] = EMPTY;
	}

	//Instantiate Member Vars
	this->in = 0;
	this->maxcap = size * size;
	this->boardScore = 0;
	this->lastmove = NULL;
}

//Create a new board from an old board and another position
//New Position must be a valid position (in bounds and at an empty spot)
Board::Board(Board* obj, Move* move, std::map<std::string, int> *scores) throw(std::invalid_argument){
	if(move == NULL || obj == NULL || !obj->validMove(move))
		throw std::invalid_argument("Invalid value for copy constructor");


	//Instantiate the board
	this->size = obj->size;

	this->board = new Color*[size];
	for(int i=0; i<size; i++)
		this->board[i] = new Color[size];

	//Copy values over
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			this->board[i][j] = obj->board[i][j];
		}
	}

	//Copy Over Move
	this->board[move->position().first][move->position().second] = move->color();

	this->in = obj->in + 1;
	this->maxcap = obj->maxcap;
	this->lastmove = move;


	//Rescore new board
	this->boardScore = this->score(move->color(), scores);
}





//Destruct Board
Board::~Board(){
	for(int i=0; i<size; i++){
		delete [] board[i];
	}

	delete [] board;

	if(lastmove != NULL) delete lastmove;
}



/***************Utility Functions**************/

//Print the board for debugging
void Board::print(){
	Color c;
	int j,i;

	//Generate Column Names
	int maxpadding = characters(size)+1;
	//std::cout << "maxpad"<<maxpadding<<std::endl;

	for(i=0; i<maxpadding; i++)
		std::cout << " ";
	for(i=0; i<size; i++){
		std::cout << (char)('a'+i) << "|";
	}
	std::cout << std::endl;

	//Generate Divider
	for(i=0; i<maxpadding; i++){std::cout << " ";}
	for(int i=0; i<size; i++){
		std::cout << "--";
	}
	std::cout << std::endl;


	for(i=0; i< (size); i++){
		//Generate Padded row numbers
		std::cout << (1 + i);
		for(j=0; j<(maxpadding + 1 - characters(1+i)); j++){std::cout << " ";}

		for(j=0; j< (size); j++){
			c = this->board[j][i];
			if(c == EMPTY) std::cout << "E";
			else if(c == LIGHT) std::cout << "L";
			else std::cout << "D";
			std::cout << "|";
		}

		//Print separators
		std::cout << std::endl;
		for(j=0; j<maxpadding; j++){ std::cout << " "; }
		for(j=0; j<size; j++){
			std::cout << "--";
		}
		std::cout << std::endl;
	}
}

void Board::printPosition(Position pos){
	std::cout << "Position(col,row): ("<<pos.first << ","<< pos.second<<") ";
	std::cout << "or (" << (char)(pos.first + 'a') <<","<< pos.second+1<<")" <<std::endl;
}

void Board::printLastMove(){ this->lastmove->print(); }

/***************************Helpers***************/
void Board::scoreDirection(Position origin, Color color, Dir dir, std::vector<int>* agg){
	if(agg == NULL){
		std::cout << "ERROR: nonvalid agg vector passed to scoreDirection" <<std::endl;
	}
	Direction d = Direction(origin);
	Position current;
	
	std::vector<int> consecutive = std::vector<int>(1);
	for(int i=0; i<4; i++){
		current = d.next(dir);
		//Check if position is valid
		if(!validPosition(current)) return;

		//If valid, score
		if(get(current) == EMPTY) consecutive.push_back(0);
		else if(get(current) == color) consecutive[consecutive.back()] = consecutive[consecutive.back()] + 1;
		else return;
	}

	//update aggregation vector
	agg->insert(agg->end(), consecutive.begin(), consecutive.end());
}

int Board::characters(int target){
	if(target <  0) return 0;
	int count = 1;

	while(target){
		target /= 10;
		count++;
	}

	return count;
}



/*************************Scoring Functions****************************/


int Board::score(Color color, std::map<std::string, int> *scores){
	std::vector<std::string> strs;
	std::vector<std::string> temp;

	//Directions to Check
	Dir dirs[] = {RIGHT, LR, DOWN, LL};
	for(int i=0; i<this->size; i++){
		for(int j=0; j<this->size; j++){
			for(int k=0; k<4; k++){
				temp = parseDirectionStr(Position(i,j), dirs[k], color);
				strs.insert(strs.end(), temp.begin(), temp.end());
			}
		}
	}

	//Now Parse Vector of Strings to Score
	int score = 0;
	for(std::vector<std::string>::iterator it = strs.begin();
		it != strs.end(); ++it){
		score += scoreString(*it, scores);
	}

	return score;
}

//Parse direction for the scoring string
std::vector<std::string> Board::parseDirectionStr(Position pos, Dir dir, Color color){
	Direction d = Direction(pos);
	std::vector<std::string> ret;
	std::string str = "";

	//Get the preceeding character
	if(!validPosition(d.opposite(dir))){
		str += "Y";
		d.next(dir); //Move Cursor back
	}

	//Get First Position
	Color current = get(pos);

	while(validPosition(pos)){
		current = get(pos);

		//Parse Current Position
		if(current == EMPTY){str += 'E';}
		else if(current == color){ str+= 'X'; }//Friendly
		else{ str += 'Y';} //Enemy

		//Get New Position
		pos = d.next(dir);
	}

	//Add one more to display you cannot move further
	str += 'Y';

	//Push Final String
	if(str.length() >= 5)
		ret.push_back(str);

	return ret;
}


//Score a string using regex matching
int Board::scoreString(std::string str, std::map<std::string, int> *scores){
	int score = 0;
	if(scores == NULL){
		std::cout << "scores should not be null"<<std::endl;
		return score;
	}

	for(std::map<std::string, int>::iterator iter = scores->begin(); iter != scores->end(); ++iter){
		score += occurrences(iter->first, str) * iter->second;
	}

	return score;
}

//Count unique occurrences of a substring in a larger string
int Board::occurrences(std::string substring, std::string bigstr){
	int occ = 0;

	size_t npos = bigstr.find(substring);
	while(npos != bigstr.npos){
		occ++;
		npos = bigstr.find(substring, npos+1);
	}
	return occ;
}

int Board::getScore(){ return this->boardScore;}