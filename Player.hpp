//Player.hpp
//
#include "Board.hpp"

class Player
{
public:
	Player(int size, Color color);
	~Player();

private:
	Color color;
	Board* board;
};