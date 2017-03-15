//Class representing a move in Gobang
#include <utility>
#include <iostream>


typedef std::pair<int,int> Position;
//Possible Pieces
enum Color{LIGHT, DARK, EMPTY};

class Move
{
public:
	Move(Position pos, Color color);
	~Move();

	Position position();
	Color color();

	void setAttributes(Position pos, Color color);
	void print();

private:
	Position pos;
	Color col;
};