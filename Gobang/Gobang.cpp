//Gobang.cpp
//Lucas Lopilato
//CS165A Machine Problem 2
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "Player.hpp"


//Displays Appropriate Error Message
int mainError(int code){
	std::cerr << ("Error In Main: ");
	switch(code){
		case 0: mainError(1);
		case 1: std::cerr << "Invalid Error Code 0 Given\n"; break;
		case 2: break; //Usage Error
		default: std::cerr << "Unknown\n";
	}

	exit(code);
}


//Displays Usage Information
void usage(){
	std::cout << "Usage: ./Gobang [-n size] [-l]" << std::endl;
	std::cout << "-n size  Specififies size of the board. " << std::endl;
	std::cout << "          N must be between 5 and 26 including both 5 and 26" << std::endl;
	std::cout << "-l       Specifies the light color for human player" <<std::endl;
	std::cout << "          if not specified, player will use light pieces" << std::endl;
	mainError(1);
}


int main(int argc, char ** argv)
{
	//Default Values
	int n = 11; //N Defaults to 11
	Color color = LIGHT; //color defaults to LIGHT

	//Parse Args and Instantiate
	int c;
	while((c = getopt(argc, argv, "n:l")) != -1){
		switch(c){
			case 'n': 
				n = atoi(optarg);
				if(n < 5 || n > 26) usage(); 
				break;
			case 'l': color = DARK; break;
			default: usage();
		}
	}

	//Instantiate the Player
	Player player = Player(n, color);

	//Tell Player To Play The Game
	player.play();
	
	return 0;
}





