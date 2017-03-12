//Board.hpp
#include <vector>
#include <iostream>
#include "Move.hpp"
#include "Direction.hpp"
#include <math.h>

//Representation of the board
class Board
{
public:
	Board(int size);
	~Board();

	//Actions 
	bool move(Move* move);


	//Inquiries 
	//Find the next best move
	Move* bestMove(Color color);
	bool isFull();
	int score(Position pos, Color color);

	bool validPosition(Position pos);

	Color get(Position pos);

	//Utility Functions
	void print();

private:
	int size;
	Color** board;

	int maxcap; //Max capacity
	int in; //Count of Pieces in board

	/*******Helpers******/
	void scoreDirection(Position origin, Color color, Dir dir, std::vector<int>* agg); 

	//Find Number of characters in a positive number
	int characters(int target);
};