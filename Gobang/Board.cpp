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
	available.erase(move->position()); //remove the position from available options

	this->print();
	move->print();

	return true;
}


/********************Inquiries************************/

bool Board::isFull(){return (in >= maxcap);}

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

//Returns the color at a location
Color Board::get(Position pos){
	return board[pos.first][pos.second];
}

//Returns the color at a location, or if the position is in the screenmove, will return that
Color Board::get(Position pos, std::map<Position, Color> *screenmoves){
	try{
		return screenmoves->at(pos);
	}
	catch(...){
		return board[pos.first][pos.second];
	}
}

Color Board::winner(){
	if(in < 10) return EMPTY;
	std::map<Position, Color> overlay;
	std::string temp;

	//Directions to Check
	Dir dirs[] = {RIGHT, LR, DOWN, LL};
	for(int i=0; i<this->size; i++){
		for(int j=0; j<this->size; j++){
			for(int k=0; k<4; k++){
				temp = parseDirectionStr(Position(i,j), dirs[k], LIGHT, &overlay);
				if(occurrences("XXXXX", temp)) return LIGHT;
				temp = parseDirectionStr(Position(i,j), dirs[k], DARK, &overlay);
				if(occurrences("XXXXX", temp)) return DARK;
			}
		}
	}


	return EMPTY;
}

//Gets the score of board had these moves been played
int Board::getScore(Color color,std::map<std::string,int> *scores, std::map<Position, Color> *screenmoves){
	return score(color, scores, screenmoves);
}

int Board::getScore(){ return this->boardScore;}
int Board::getIn(){return this->in;}

/**********************Setup / Teardown ************/

//Create a new empty board
Board::Board(int size) : size(size) {
	std::cout << "Size: "<<size<<", Depth: 1"<<std::endl;

	//Instantiate the board
	this->board = new Color*[size];
	for(int i=0; i<size; i++){
		this->board[i] = new Color[size];

		//Set values equal to EMPTY
		for(int j=0; j<size; j++){
			this->board[i][j] = EMPTY;
			//Populate possible moves
			available.insert(Position(i,j));
		}
	}

	//Instantiate Member Vars
	this->in = 0;
	this->maxcap = size * size;
	this->boardScore = 0;
	this->lastmove = NULL;
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

void Board::printColor(Color color){
	if(color == EMPTY) std::cout << "EMPTY" <<std::endl;
	else if(color == LIGHT) std::cout << "LIGHT" <<std::endl;
	else std::cout << "DARK" <<std::endl;
}

/***************************Helpers***************/


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


int Board::score(Color color, std::map<std::string, int> *scores, std::map<Position,Color> *screenmoves){
	std::vector<std::string> strs;
	std::string temp;

	//Directions to Check
	Dir dirs[] = {RIGHT, LR, DOWN, LL};
	for(int i=0; i<this->size; i++){
		for(int j=0; j<this->size; j++){
			for(int k=0; k<4; k++){
				temp = parseDirectionStr(Position(i,j), dirs[k], color, screenmoves);
				if(!temp.empty())
					strs.push_back(temp);
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
std::string Board::parseDirectionStr(Position pos, Dir dir, Color color, std::map<Position, Color> *screenmoves){
	Direction d = Direction(pos);
	std::string str = "";
	bool interesting = false; //Keeps track of wheter and X was ever found

	//Get the preceeding character
	if(!validPosition(d.opposite(dir))){
		str += "Y";
		d.next(dir); //Move Cursor back
	}

	//Get First Position
	Color current = get(pos, screenmoves);

	while(validPosition(pos)){
		current = get(pos, screenmoves);

		//Parse Current Position
		if(current == EMPTY){str += 'E';}
		else if(current == color){
			str+= 'X';
			interesting = true;
		}//Friendly
		else{ str += 'Y';} //Enemy

		//Get New Position
		pos = d.next(dir);
	}


	//Push Final String
	if(str.length() >= 5 && interesting){
		return str;
	}

	return "";
}


//Score a string using regex matching
int Board::scoreString(std::string str,std::map<std::string, int> *scores){
	int score = 0;

	for(std::map<std::string, int>::const_iterator iter = scores->begin(); iter != scores->end(); ++iter){
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
	if(occ > 0){
		//std::cout << "Pattern found: " << substring <<"found in "<<bigstr<<std::endl;
	}
	return occ;
}

