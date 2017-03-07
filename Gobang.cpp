//Gobang.cpp
//Lucas Lopilato
//CS165A Machine Problem 2
#import <stdlib.h>
#import <stdio.h>
#import <iostream>
#import <unistd.h>
#import "Player.hpp"

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

void usage(){
	std::cout << "Usage: ./Gobang [-n size] [-l]" << std::endl;
	std::cout << "-n size  specififies size of the board" << std::endl;
	std::cout << "-l       specifies the light color for this player" <<std::endl;
	std::cout << "          if not specified, player will use dark pieces" << std::endl;
	mainError(2);
}

int main(int argc, char ** argv)
{
	//Parse Args and Instantiate
	int c;
	while((c = getopt(argc, argv, "n:l")) != -1){
		switch(c){
			case 'n': break;
			case 'l': break;
			default: usage();
		}
	}

	
	return 0;
}





