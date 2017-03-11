#include "Move.hpp"

Move::Move(Position pos, int score, Color color): pos(pos), sco(score), col(color){}

Position Move::position(){return this->pos;}
int Move::score(){return this->sco;}
Color Move::color(){return this->col;}

void Move::setAttributes(Position pos, int score, Color color){
	this->pos.first = pos.first;
	this->pos.second = pos.second;
	this->sco = score;
	this->col = color;
}