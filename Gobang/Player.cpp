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

	/*std::queue<Move*> queue;
	Position pos;
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			pos = Position(i,j);
			if(board->get(pos) == EMPTY) queue.push(new Move(pos, 0, color));
		}
	}*/

	/*if(board->getIn() < 2){
		if(board->get(Position(size/2, size/2)) == EMPTY)
			return new Move(Position(size/2, size/2), color);
		else return new Move(Position(size/2 -1, size/2 - 1), color);
	}
	else*/ return minimax();


	/*Board* max = NULL;
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

	return max;*/
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
			//std::cout << "Other=Dark" << (other == DARK) << std::endl;
			//board->printPosition(pos);

			//Submit move if valid
			//return new Board(board, move, &scores);
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

	//Iterate over all possible moves
	std::set<Position>::iterator maxpos, minpos;
	std::map<Position,Color> screenmoves;
	for(maxpos = (board->available.begin()); maxpos != board->available.end(); ++maxpos){
		screenmoves[*maxpos]=color;

		maxtemp = board->getScore(color, scores, screenmoves);

		//Create a move to represent a potential max move
		for(minpos = board->available.begin(); minpos != board->available.end(); ++minpos){
			if(minpos != maxpos){
				screenmoves[*minpos]=other; //simulate the move by the other player

				//Get the score if these moves were played
				mintemp = board->getScore(other, scores, screenmoves);

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


	//Now check each candidate of the newly generated board for 
	//The score we want to minimize
	/*Board* maxhold = NULL;
	Board* minhold = NULL;
	std::queue<Move*> minqueue;

	//Go through all possibilities for max
	while(!maxqueue.empty()){
		maxhold = new Board(board, maxqueue.front(), &scores);

		//Build queue for the minimum
		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				pos = Position(i,j);
				if(maxhold->get(pos) == EMPTY)
					minqueue.push(new Move(pos, 0, other));
			}
		}

		//Find largest min for given previous move
		Board* mintemp = NULL;
		while(!minqueue.empty()){
			mintemp = new Board(maxhold, minqueue.front(), &scores);
			if(minhold == NULL){
				minhold = mintemp;
				mintemp = NULL;
			}
			else{
				if(mintemp->getScore() > minhold->getScore()){
					delete minhold;
					minhold = mintemp;
					mintemp = NULL;
				}
				else{
					delete mintemp;
					mintemp = NULL;
				}
			}

			minqueue.pop();
		}

		//Check if the holds are better than the current max's and mins
		if(min == NULL || max == NULL){
			max = maxhold;
			min = minhold;
			maxhold = NULL;
			minhold = NULL;
		}
		else{
			//If the holds are a better option, switch over
			if(maxhold->getScore() - minhold->getScore() > max->getScore() - min->getScore()){
				//Delete old vals
				delete max;
				delete min;
				
				max = maxhold;
				min = minhold;

				maxhold = NULL;
				minhold = NULL;
			}
			else{
				delete minhold;
				delete maxhold;

				maxhold = NULL;
				minhold = NULL;
			}
		}

		maxqueue.pop();
	}

	if(min != NULL) delete min;
	if(maxhold != NULL) delete maxhold;
	if(minhold != NULL) delete minhold;

	return max;*/
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

