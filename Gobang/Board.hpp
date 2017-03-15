//Board.hpp
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "Move.hpp"
#include "Direction.hpp"
#include <math.h>
#include <stdexcept>
#include <set>
#include <assert.h>
#include <pthread.h>



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
	bool validMove(Move* move);
	int getScore();
	int getScore(Color color, std::map<std::string, int> *scores, std::map<Position, Color> *screenMoves);
	int getIn();

	Color get(Position pos);
	Color get(Position pos, std::map<Position, Color> *screenmoves);

	//Returns winning color or EMPTY if no one has won
	Color winner(); 

	//Utility Functions
	void print();
	void printPosition(Position pos);
	void printLastMove();
	void printColor(Color color);

	std::set<Position> available;
	

private:
	//Board Information
	int size;
	Color** board;
	int maxcap; //Max capacity
	int in; //Count of Pieces in board
	Move* lastmove; //Last Move Played


	/*******Helpers******/

	//Find Number of characters in a positive number
	int characters(int target);

	int boardScore;


	int score(Color col, std::map<std::string, int> *scores, std::map<Position, Color> *screenmoves);
	std::vector<std::string>* parseDirectionStr(Position pos, Dir dir, Color color, std::map<Position, Color> *screenmoves);
	int scoreString(std::string str, std::map<std::string, int> *scores);
	int occurrences(std::string substring, std::string bigstr);
};