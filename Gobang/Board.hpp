//Board.hpp
#include <vector>
#include <map>
#include <string>
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
	Board(Board* obj, Move* move, std::map<std::string, int> *scores) throw(std::invalid_argument);
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
	int getScore();

	Color get(Position pos);

	//Returns winning color or EMPTY if no one has won
	Color winner(); 

	//Utility Functions
	void print();
	void printPosition(Position pos);
	void printLastMove();

private:
	int size;
	Color** board;

	int maxcap; //Max capacity
	int in; //Count of Pieces in board
	Move* lastmove;


	/*******Helpers******/
	void scoreDirection(Position origin, Color color, Dir dir, std::vector<int>* agg); 

	//Find Number of characters in a positive number
	int characters(int target);

	int boardScore;


	int score(Color col, std::map<std::string, int> *scores);
	std::vector<std::string> parseDirectionStr(Position pos, Dir dir, Color color);
	int scoreString(std::string str, std::map<std::string, int> *scores);
	int occurrences(std::string substring, std::string bigstr);
};