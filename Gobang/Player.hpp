//Player.hpp
//
#include <iostream>
#include <string>
#include "Board.hpp"

class Player
{
public:
	Player(int size, Color color);
	~Player();

	void play();

	//Turn Handling
	Board* humanTurn();
	Board* comTurn();

private:
	Color color;
	Color other;
	Board* board;
	int size;

};