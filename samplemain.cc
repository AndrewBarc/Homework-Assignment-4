/*****************************************************
This is a sample of what the main should like for the third phase of 
the Mancala game.The only change is that the game now announces tells 
the human whether or not they have won.
	John Dolan	Ohio University		Spring 2018
*************************************************************/
/********************************
Name:	Andrew Barcus
Date:	4/27/2018
File:	samplemain.cc
Project 6
Part: 	6-3
********************************/
#include<iostream>
#include "mancala.h"
using namespace std;
using namespace main_savitch_14;


int main(){
    mancala stonegame;
	game::who winner;
	winner=stonegame.play();
	if (winner == game::HUMAN)
		std::cout<<"YOU WIN!\n";
	else
		std::cout<<"YOU LOSE!\n";
return 0;
}

