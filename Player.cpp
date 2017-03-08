//Player.cpp

#include "Player.hpp"

Player::Player(int size, Color color): color(color){
	this->board = new Board(size);
}

Player::~Player(){
	delete(this->board);
}

