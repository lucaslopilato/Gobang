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

			this->board->print();
			this->board->printLastMove();
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

	std::queue<Move*> queue;
	Position pos;
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			pos = Position(i,j);
			if(board->get(pos) == EMPTY) queue.push(new Move(pos, 0, color));
		}
	}


	Board* max = NULL;
	Board* hold = NULL;

	while(!queue.empty()){
		hold = new Board(board, queue.front(), &scores);
		if(max == NULL || max->getScore() < hold->getScore()){
			if(max != NULL) delete max;
			max = hold;
			hold = NULL;
			std::cout << "New Max: ";
			queue.front()->print();
			std::cout << "With score: " << max->getScore() << std::endl;
		}
		else{
			delete hold;
			hold = NULL;
		}
		queue.pop();
	}

	return max;
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
			return new Board(board, move, &scores);
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

	//Initialize Scoring Dictionary
	scores["XXXXX"]=100000; //5 In a Row

	//4 Combos
	scores["EXXXXE"]=50000; 
	scores["EXXXXY"]=2000; 
	scores["XEXXX"]=2000; 
	scores["XEXXXE"]=2000;
	scores["XXEXX"]=2000;

	//3 Combos
	scores["EXXXE"]=1800;
	scores["EXEXXE"]=1800;
	scores["EEXXXY"]=600;
	scores["EXEXXY"]=600;
	scores["EXXEXY"]=600;
	scores["EXEEXXE"]=600;
	scores["EXEXEXE"]=600;
	scores["YEXXXEY"]=600;

	//2 Combos
	scores["EEXXEE"]=300;
	scores["EXEXE"]=300;
	scores["EXEEXE"]=300;
	scores["EEXEXY"]=100;
	scores["EXEEXY"]=100;
	scores["EXEEEXE"]=100;
	scores["YEXEXEY"]=100;
	scores["YEXXEEY"]=100;
	
	//1 Combos
	scores["XEEEE"]=1;
	scores["EEEEX"]=1;
	scores["EEXEE"]=1;
	scores["EXEEE"]=1;
	scores["EEEXE"]=1;
}

Player::~Player(){
	delete(this->board);
}

