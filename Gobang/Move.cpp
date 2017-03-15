#include "Move.hpp"

Move::Move(Position pos, Color color): pos(pos), col(color){}
Move::~Move(){}

Position Move::position(){return this->pos;}
Color Move::color(){return this->col;}

void Move::setAttributes(Position pos, Color color){
	this->pos.first = pos.first;
	this->pos.second = pos.second;
	this->col = color;
}

void Move::print(){
	std::cout << "Move played: "<< (char)('a' + pos.first) << this->pos.second + 1 << std::endl;
}