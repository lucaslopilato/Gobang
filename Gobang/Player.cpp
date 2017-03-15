//Player.cpp

#include "Player.hpp"


//Play the game
void Player::play(){
	Move* hold = NULL;
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
			if(!this->board->move(hold)) std::cout<<"fucking up " <<std::endl;
			delete hold;
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
Move* Player::comTurn(){
	//Print Console Message
	color == LIGHT ? std::cout << "Light" : std::cout <<"Dark";
	std::cout << " player (COM) plays now" << std::endl;
	color == LIGHT ? std::cout << "Light" : std::cout <<"Dark";
	std::cout << " player (COM) is calculating its next move...";
	std::cout << "(this might take up to 30 seconds)" << std::endl;

	if(board->getIn() <= 2){
		if(board->get(Position(size/2, size/2)) == EMPTY)
			return new Move(Position(size/2, size/2), color);
		else return new Move(Position(), color);
	}

	return minimax();
}

//Parse Arguments for the human's turn
Move* Player::humanTurn(){
	Position pos;
	std::string input;
	Move* move = NULL;

	//Print Console Information
	(other == LIGHT) ? std::cout << "Light" : std::cout << "Dark";
	std::cout << " player (human) plays now" << std::endl;

	//Loop Until Valid Input
	while(true){
		std::cin >> input;
		try{
			//Parse Input
			pos = Position(input[0] - 'a', std::stoi(input.substr(1))-1);
			move = new Move(pos,other);
			if(board->validMove(move))
				return new Move(pos, other);
		}
		catch(...){} //Ignore the error and just ask for more input
		std::cout << "Error: You tried an invalid option \""<< input;
		std::cout << "\", please try another move" << std::endl;
		if(move != NULL) delete move;
		move = NULL;
	}
}

Move* Player::minimax(){
	Position max;
	Position min;
	int score = 0;

	int maxtemp = 0;
	int mintemp = 0;

	int count = 0;

	//Iterate over all possible moves
	std::set<Position>::iterator maxpos, minpos;
	std::map<Position,Color> screenmoves;
	for(maxpos = (board->available.begin()); maxpos != board->available.end(); ++maxpos){
		count++;
		screenmoves[*maxpos]=color;

		maxtemp = board->getScore(color, &scores, &screenmoves);

		//Create a move to represent a potential max move
		for(minpos = board->available.begin(); minpos != board->available.end(); ++minpos){
			if(minpos != maxpos){
				screenmoves[*minpos]=other; //simulate the move by the other player

				//Get the score if these moves were played
				mintemp = board->getScore(other, &scores, &screenmoves);

				if(score == 0){
					max = *maxpos;
					min = *minpos;
					score = maxtemp - mintemp;
				}else{
					if(maxtemp - mintemp > score){
						max = *maxpos;
						min = *minpos;
						score = maxtemp - mintemp;
					}
				}

				screenmoves.erase(*minpos); //erase the move
			}
		}

		screenmoves.erase(*maxpos);
	}
	return new Move(max, color);
}





Player::Player(int size, Color color):color(color), size(size){
	this->board = new Board(size);
	(color == LIGHT) ? other = DARK : other = LIGHT;

	//Initialize Scoring Dictionary
	scores["XXXXX"]=1000000;	
	scores["EXXXXE"]=300000;	
	scores["XXXXE"]=2500;	
	scores["EXXXX"]=2500;
	scores["XXXEX"]=3000;	
	scores["XEXXX"]=3000;	
	scores["XXEXX"]=2600;
	scores["EEXXXEE"]=3000;	
	scores["XXXEE"]=500;	
	scores["EEXXX"]=500;	
	scores["EXEXXE"]=800;	
	scores["EXXEXE"]=800;	
	scores["XEEXX"]=600;	
	scores["XXEEX"]=600;	
	scores["XEXEX"]=550;	
	scores["EEEXXEEE"]=650;	
	scores["XXEEE"]=150;	
	scores["EEEXX"]=150;	
	scores["EEXEXEE"]=250;	
	scores["EXEEXE"]=200;	


	/*scores["XXXXX"]=100000; //5 In a Row

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
	scores["EEEXE"]=1;*/
}

Player::~Player(){
	delete(this->board);
}

