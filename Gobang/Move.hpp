//Class representing a move in Gobang
#include <utility>
#include <iostream>


typedef std::pair<int,int> Position;
//Possible Pieces
enum Color{LIGHT, DARK, EMPTY};

class Move
{
public:
	Move(Position pos, int score, Color color);
	~Move();

	Position position();
	int score();
	Color color();

	void setAttributes(Position pos, int score, Color color);
	void print();

	//Operator Overloading
	bool operator <(const Move& other) {return this->sco < other.sco;}
	bool operator >(const Move& other) {return this->sco > other.sco;}
	bool operator ==(const Move& other) {return this->sco == other.sco;}
	bool operator <=(const Move& other) {return this->sco <= other.sco;}
	bool operator >=(const Move& other) {return this->sco >= other.sco;}
private:
	Position pos;
	int sco; //score
	Color col;
};