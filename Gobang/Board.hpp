//Board.hpp
#include <vector>
#include <iostream>
#include "Move.hpp"
#include "Direction.hpp"
#include <math.h>
#include <stdexcept>



//Representation of the board
class Board
{
public:
	Board(int size);
	Board(Board* obj, Move* move) throw(std::invalid_argument);
	~Board();

	//Actions 
	bool move(Move* move);


	//Inquiries 
	//Find the next best move
	Move* bestMove(Color color);
	bool isFull();
	int score(Position pos, Color color);

	bool validPosition(Position pos);
	bool validMove(Move* move);

	Color get(Position pos);

	//Returns winning color or EMPTY if no one has won
	Color winner(); 

	//Utility Functions
	void print();
	void printPosition(Position pos);

private:
	int size;
	Color** board;

	int maxcap; //Max capacity
	int in; //Count of Pieces in board

	/*******Helpers******/
	void scoreDirection(Position origin, Color color, Dir dir, std::vector<int>* agg); 

	//Find Number of characters in a positive number
	int characters(int target);

	int boardScore;


	int score();
	/*int scorePosition(Position UL, Color col);
	int scoreDirection(Position pos, Dir dir, Color col);
	int scoreFriendly(Direction d, Dir dir, Color friendly);
	int scoreEnemy(Direction d, Dir dir , Color enemy);
	int maxConsecutive(Position pos, Dir dir, Color target);*/
};