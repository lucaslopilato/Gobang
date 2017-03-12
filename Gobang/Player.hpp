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
	void otherTurn();

private:
	Color color;
	Color other;
	Board* board;
	int size;

};