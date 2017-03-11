//Board.hpp
#include <iostream>
#include "Move.hpp"

//Representation of the board
class Board
{
public:
	Board(int size);
	~Board();

	//Actions 
	bool move(Move move);


	//Inquiries 
	//Find the next best move
	void bestMove(Move* move, Color color);
	bool isFull();

	//Utility Functions
	void print();

private:
	int size;
	Color** board;

	int maxcap; //Max capacity
	int in; //Count of Pieces in board
};