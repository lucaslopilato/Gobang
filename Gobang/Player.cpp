//Player.cpp

#include "Player.hpp"


//Play the game
void Player::play(){
	Move* best = new Move(Position(size/2, size/2), 0, color);

	//If Player is DARK, make the first move
    if(color == DARK){
		board->move(best);
	}
	else{
		otherTurn();
	} 

	if(best != NULL){
		delete best;
		best = NULL;
	}

	
}

//Parse Arguments for the other player's turn
void Player::otherTurn(){
	Position pos;
	std::string input;
	Move * move = NULL;

	//Loop Until Valid Input
	while(true){
		std::cin >> input;
		try{
			pos = Position(input[0] - 'a', std::stoi(input.substr(1))-1);
			move = new Move(pos, 0, other);
			if(board->move(move)){
				if(move != NULL) delete move;
				return;
			}
			if(move != NULL){
				delete move;
				move = NULL;
			}
		}
		catch(...){
			std::cout << "Invalid Option. Enter new move"<< std::endl;
		}
		std::cout << "Invalid Option. Enter new move"<< std::endl;
	}
}

Player::Player(int size, Color color):color(color), size(size){
	this->board = new Board(size);
	if(color == LIGHT) other = DARK;
	else other = LIGHT;
}

Player::~Player(){
	delete(this->board);
}

