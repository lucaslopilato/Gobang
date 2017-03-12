#include "Direction.hpp"	

Direction::~Direction(){}

Position Direction::next(Dir choice){
	switch(choice){
		case UL: return UpperLeft();
		case UR: return UpperRight();
		case LL: return LowerLeft();
		case LR: return LowerRight();
		case UP: return Up();
		case DOWN: return Down();
		case LEFT: return Left();
		case RIGHT: return Right();
	}
}

Position Direction::UpperLeft() {base = Position(base.first - 1, base.second - 1); return base;}
Position Direction::UpperRight() {base = Position(base.first + 1, base.second - 1); return base;}
Position Direction::LowerLeft() {base = Position(base.first - 1, base.second + 1); return base;}
Position Direction::LowerRight() {base = Position(base.first + 1, base.second + 1); return base;}
Position Direction::Up() {base = Position(base.first, base.second - 1); return base;}
Position Direction::Down() {base = Position(base.first, base.second + 1); return base;}
Position Direction::Left() {base = Position(base.first - 1, base.second); return base;}
Position Direction::Right() {base = Position(base.first + 1, base.second); return base;}