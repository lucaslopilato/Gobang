//Board.cpp
//
#include "Board.hpp"


/**********************Actions***********************/

//Returns True if Successful
bool Board::move(Move move){
	int col = move.position().first;
	int row = move.position().second;

	//Validate Input
	if(col < 0 || col > size || row < 0 || row > size)
		return false;

	//Make sure valid color
	if(move.color() == EMPTY) return false;

	//If valid, update and return success
	board[col][row] = move.color();
	return true;
}


/********************Inquiries************************/

bool Board::isFull(){return (in >= maxcap);}

//Find the Best Possible Move Given a Color
void Board::bestMove(Move* move, Color color){

	//Record Keeping for the Best Possible Move

	//Check all spots for the best move
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){

		}
	}
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
	int j;

	for(int i=0; i< (size); i++){
		for(j=0; j< (size); j++){
			c = this->board[i][j];
			if(c == EMPTY) std::cout << "E";
			else if(c == LIGHT) std::cout << "L";
			else std::cout << "D";
			std::cout << "|";
		}

		//Print separators
		std::cout << std::endl;
		for(j=0; j<size; j++){
			std::cout << "--";
		}
		std::cout << std::endl;
	}
}