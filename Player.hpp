//Player.hpp

//Types of pieces to be placed
enum Color{ LIGHT, DARK};

class Player
{
public:
	Player(int size, Color color);
	~Player();

private:
	int size;
	Color color;
};