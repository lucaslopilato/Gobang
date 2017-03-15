//Player.hpp
//
#include <map>
#include <iostream>
#include <string>
#include "Board.hpp"
#include <stdlib.h>
#include <time.h>

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
	Move* random();

	bool timeToGuess(clock_t start);

private:
	Color color;
	Color other;
	Board* board;
	int size;

	//Scoring Dictionary
	std::map<std::string, int> scores;

};