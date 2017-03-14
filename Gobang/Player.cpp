//Player.cpp

#include "Player.hpp"


//Play the game
void Player::play(){
	Board* hold = NULL;
	Color last = LIGHT;

	//Print Preliminary Board
	board->print();
	std::cout << "Move played: --" << std::endl;

	//Loop Using MinMax
	Color winner;
	while((winner = board->winner()) == EMPTY && !board->isFull()){
		std::cout << "winner: "<< winner;
		if(last == other){ //COM turn
			last = color;
			hold = comTurn();
		}
		else{ //Otherwise human's turn
			last = other;
			hold = humanTurn();
		}

		//Build a new board with the move
		try{
			if(hold == NULL) std::cout << "Invalid Board" << std::endl;
			delete this->board;
			this->board = hold;
			hold = NULL;
		}
		catch(...){
			std::cout << "Unhandled invalid Move" << std::endl;
		}
	}


	//Print Winning Message
	std::cout << "Game over" << std::endl;
	if(winner == EMPTY) std::cout << "It's a tie!";
	else{
		winner == LIGHT ? std::cout << "Light" : std::cout <<"Dark";
		std::cout << " player";
		winner == color ? std::cout << " (COM)" : std::cout <<" (human)";
		std::cout << " wins!";
	}
	std::cout << std::endl;
}


/************************Turn Handling***************************/
Board* Player::comTurn(){
	//Print Console Message
	color == LIGHT ? std::cout << "Light" : std::cout <<"Dark";
	std::cout << " player (COM) plays now" << std::endl;
	color == LIGHT ? std::cout << "Light" : std::cout <<"Dark";
	std::cout << " player (COM) is calculating its next move...";
	std::cout << "(this might take up to 30 seconds)" << std::endl;

	return new Board(board, board->bestMove(color));
}

//Parse Arguments for the human's turn
Board* Player::humanTurn(){
	Position pos;
	std::string input;
	Move * move = NULL;

	//Print Console Information
	(other == LIGHT) ? std::cout << "Light" : std::cout << "Dark";
	std::cout << " player (human) plays now" << std::endl;

	//Loop Until Valid Input
	while(true){
		std::cin >> input;
		try{
			//Parse Input
			pos = Position(input[0] - 'a', std::stoi(input.substr(1))-1);
			move = new Move(pos, 0, other);
			//std::cout << "Other=Dark" << (other == DARK) << std::endl;
			//board->printPosition(pos);

			//Submit move if valid
			return new Board(board, move);
		}
		catch(...){} //Ignore the error and just ask for more input
		std::cout << "Error: You tried an invalid option \""<< input;
		std::cout << "\", please try another move" << std::endl;
		if(move != NULL) delete move;
		move = NULL;
	}
}

Player::Player(int size, Color color):color(color), size(size){
	this->board = new Board(size);
	(color == LIGHT) ? other = DARK : other = LIGHT;
}

Player::~Player(){
	delete(this->board);
}

