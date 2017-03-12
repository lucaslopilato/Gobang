//Player.cpp

#include "Player.hpp"


//Play the game
void Player::play(){
	Move* best = NULL;

	//If Player is DARK, make the first move
   //if(color == DARK)
	best = board->bestMove(color);

	//Print Move
	board->move(best);
	board->print();
	best->print();


	if(best != NULL){
		delete best;
	}

	
}

Player::Player(int size, Color color): color(color){
	this->board = new Board(size);
}

Player::~Player(){
	delete(this->board);
}

