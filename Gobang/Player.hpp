//Player.hpp
//
#include <map>
#include <iostream>
#include <string>
#include "Board.hpp"
#include <queue>

class Player
{
public:
	Player(int size, Color color);
	~Player();

	void play();

	//Turn Handling
	Move* humanTurn();
	Move* comTurn();

	//Minimax
	Move* minimax();

private:
	Color color;
	Color other;
	Board* board;
	int size;

	//Scoring Dictionary
	std::map<std::string, int> scores;

};