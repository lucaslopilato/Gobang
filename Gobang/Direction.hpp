#include <utility>

typedef std::pair<int,int> Position;
enum Dir{UL,UR,LL,LR,UP,DOWN,LEFT,RIGHT};


#pragma once
class Direction
{
public:

	Direction(Position base) : base(base) {};
	~Direction(void);

	Position next(Dir choice);
private:
	Position base;

	//Simple functions to move the position in a specific direction
	Position UpperLeft();
	Position UpperRight();
	Position LowerLeft();
	Position LowerRight();
	Position Up();
	Position Down();
	Position Left();
	Position Right();
};

