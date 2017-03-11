//Player.hpp
//
#include <iostream>
#include "Board.hpp"

class Player
{
public:
	Player(int size, Color color);
	~Player();

	void play();

private:
	Color color;
	Board* board;
};