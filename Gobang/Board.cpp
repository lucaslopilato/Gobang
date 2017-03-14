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
}

//Create a new board from an old board and another position
//New Position must be a valid position (in bounds and at an empty spot)
Board::Board(Board* obj, Move* move) throw(std::invalid_argument){
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


	//Rescore new board
	this->boardScore = obj->boardScore;

	//Print out board and last move
	this->print();
	move->print();

	delete move;
}





//Destruct Board
Board::~Board(){
	for(int i=0; i<size; i++){
		delete [] board[i];
	}

	delete [] board;
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

//Score 5x5 Square for the 
int Board::scorePosition(Position UL, Color col){
	int score = 0;

	//Score Upper Left Diagonal


	return score;
}

int Board::scoreDirection(Position pos, Dir dir, Color col){
	if(col == EMPTY) return 0;
	int score = 0;

	//Get Base Direction and decide other color
	Direction d = Direction(pos);
	Color other;
	(col == LIGHT) ? other = DARK : other = LIGHT; 


	//3 Cases, Friendly, Enemy, or Empty
	switch(get(d.next(dir))){
	case(EMPTY):
		for(int i=0; i<3; i++){
			if(get(d.next(dir)) == other) return 0;
		}
		score = 15; //Connect One
		break;
	case(LIGHT):
		for(int i=0; i<3; i++){
			if(get(d.gext(dir)) == 
		}
		break;
	case(DARK):
		break;

	}

	return score;
}

int Board::scoreFriendly(Direction d, Dir dir, Color friendly){
	int consecutive = 0;

	for(int i=0; i<3; i++){
		if(get(d.next(dir)) == friendly) consecutive++;
		else break;
	}

	switch(consecutive){
	case 0: return 300; //Connect 2
	case 1: return 1200 //Connect 3
	case 3: return 
	}


	return score;
}

int Board::scoreEnemy(Direction d, Dir dir, Color enemy){
	int consecutive = 0;

	for(int i=0; i<3; i++){
		if(get(d.next(dir)) == enemy) consecutive++;
		else break;
	}

	return score;
}

int Board::maxConsecutive(Position pos, Dir dir, Color target){
	Dir opp;
	switch(dir){
	case UL: opp = LR; break;
	case UP: opp = DOWN; break;
	case UR: opp = LL; break;
	case LEFT: opp = RIGHT; break;
	case RIGHT: opp = LEFT; break;
	case LL: opp = UR; break;
	case DOWN: opp = UP; break;
	case LR: opp = UL; break;
	}

	int max = 0;

	for(int i=0; i<5; i++){

	}
}