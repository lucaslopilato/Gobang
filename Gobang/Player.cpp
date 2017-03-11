//Player.cpp

#include "Player.hpp"


//Play the game
void Player::play(){
	Position move;

	//If Player is DARK, make the first move
	if(color == DARK)
		move = board->bestMove(color);

	
}

Player::Player(int size, Color color): color(color){
	this->board = new Board(size);
}

Player::~Player(){
	delete(this->board);
}

