//Board.cpp
//
#include "Board.hpp"


/**********************Actions***********************/

//Returns True if Successful
bool Board::move(Move* move){
	int col = move->position().first;
	int row = move->position().second;

	//Validate Input
	if(col < 0 || col > size || row < 0 || row > size)
		return false;

	//Make sure valid color
	if(move->color() == EMPTY) return false;

	//If valid, update and return success
	board[col][row] = move->color();
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
	for(int i=1; i<size; i++){
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
	Position moving = pos;
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
	for(int i=0; i<total.size(); i++){
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

Color Board::get(Position pos){
	return board[pos.first][pos.second];
}





/**********************Setup / Teardown ************/

//Create a new empty board
Board::Board(int size) : size(size) {

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
			c = this->board[i][j];
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