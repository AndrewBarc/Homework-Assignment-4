/********************************
Name:	Andrew Barcus
Date:	4/27/2018
File:	mancala.cc
Project 6
Part:	6-3
********************************/
#include "mancala.h"
#include "colors.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <ctype.h>
#include <stdlib.h>
using namespace std;

mancala::mancala(){
	for(size_t i = 0; i < 6; i++){
		Mancala[i] = 4;
	}
	Mancala[6] = 0;
	for(size_t j = 7; j < 13; j++){
		Mancala[j] = 4;
	}
	Mancala[13] = 0;
}

void mancala:: restart(){
		for(size_t i = 0; i < 6; i++){
		Mancala[i] = 4;
	}
	Mancala[6] = 0;
	for(size_t j = 7; j < 13; j++){
		Mancala[j] = 4;
	}
	Mancala[13] = 0;
	game::restart();
}

void mancala:: display_status()const{
	int row = 0;
	int i = 0;
	string topbot = "|------*------|";
	string filler = "|"+B_WHITE + "             "+B_BLACK +"|";
	string cfiller = "|" + B_RED + "             " + B_BLACK +"|";
	string ufiller = "|" + B_BLUE + "             " + B_BLACK +"|";
	string border = "|-------------|";
	string left = "|      ";
	string right = "      |";
	cout << B_BLACK << endl;;
	while(row != 15){
		if(row == 0 || row == 14){ //top and bottom 
			i = 0;
			cout << GREEN << topbot;
			while ( i != 6){
				//cout << WHITE << topbot;
				cout << GREEN << "|------" << i + 1 << "------|";
				i++;
			}
			cout << topbot << WHITE<<  endl;
		}
		
		else if(row == 3){ //cpu's cups
			cout << cfiller;
			i = 12;
			while(i != 6){
				cout << "|" << B_RED <<"      " << WHITE << Mancala[i] << "      " << GREEN <<B_BLACK << "|";
				i--;
			}
			cout << ufiller <<  endl;
		}
		
		else if(row == 6 || row == 8){ // borderline
			cout << cfiller;
			i = 0;
			while(i != 6){
				cout << border;
				i++;
			}
			cout << ufiller << endl;
		}

		else if(row == 7){ //point standings
			cout << "|"<<B_RED << WHITE <<"   CPU: " << setfill('0') << setw(2) << Mancala[13] << "   " << GREEN<<B_BLACK << "|";
			i = 0;
			while(i != 6){
				cout << filler;
				i++;
			}
			cout <<B_BLACK<< "|"<<B_BLUE << WHITE <<"   YOU: " << setfill('0') << setw(2) << Mancala[6] << "   " << B_BLACK << GREEN << "|" << endl;;
		}
		
		else if(row == 11){//player's cups
			cout << cfiller;
			i = 0;
			while(i != 6){
				cout << "|" << B_BLUE <<"      " << WHITE << Mancala[i] << "      " << GREEN <<B_BLACK << "|";
				i++;
			}
			cout << ufiller << endl;
		}
		
		else{//empty space
			i = 0;
			if(row == 1 || row == 2 || row == 4 || row == 5){
				while (i != 7){
					cout << GREEN << cfiller;
					i++;
				}
				cout << GREEN << ufiller;
			}
			else{
				cout << GREEN <<cfiller;
				while (i != 7){
					cout << GREEN<< ufiller;
					i++;
				}
			}
		cout << endl;
		}
		row++;
	}
	cout << B_BLACK << endl;
}

bool mancala:: is_legal(const std::string& move)const{
	int position = 0;
	if(next_mover() == HUMAN){
		if(move == "1" || move == "2" || move == "3" || move == "4" || move == "5" || move == "6"){
			position = atoi(move.c_str());
			position = position - 1; 
			if(Mancala[position] == 0){
				cout << "The cup you selected is empty.\n";
				cout << "Please select a different cup.\n";
				return false;
			}
			else{
				return true;
			}
		}
		else{
			cout << "That was an invalid choice.\n";
			cout << "Please choose a cup between 1 and 6.\n";
			return false;
		}
	}
	else if(next_mover() == COMPUTER){
		if(move == "1" || move == "2" || move == "3" || move == "4" || move == "5" || move == "6"){
			position =  13 - atoi(move.c_str()); 
			if(Mancala[position] == 0){
				return false;
			}
			else{
				return true;
			}
		}
		else{
			return false;
		}
	}
}

void mancala:: make_move(const std::string& move){
	int stones; int position; int special; std::string newCup;
	queue<string> moves;
	if(next_mover() == HUMAN){
		position = atoi(move.c_str());
		position--;
		stones = Mancala[position];
		Mancala[position] = 0;
		while(stones != 0){
			if(position == 14){
				position = 0;
			}
			else if(position == 5 && stones == 1){/*last stone lands in mancala*/
					position++;
					Mancala[position]++;
					stones--;
					display_status();
					if(is_game_over()){
						break;
					}
					cout << "Nice!\t Pick another cup to move: ";
					getline(cin, newCup);
					while (!is_legal(newCup)){
						cout << "Illegal move.\n" << "Try Again\n";
						getline(cin,newCup);
					}
					position = atoi(newCup.c_str()) - 1;
					stones = Mancala[position];
					Mancala[position] = 0;
				}
			else{
				if(stones == 1 && Mancala[position+1] == 0 && position <6 && Mancala[12-position -1] !=0){//last stone lands in empty cup
					stones = Mancala[12- position-1] + 1;
					Mancala[12-position-1] = 0;
					Mancala[6] = Mancala[6] + stones;
					stones = 0;
				}
				else{
					position++;
					if(position == 13){position = 0;}
					Mancala[position]++;
					stones--;
				}
			}
		}
	}
	//COMPUTER's Next move
	else if(next_mover() == COMPUTER){
		position =  13 - atoi(move.c_str()); 
		stones = Mancala[position];
		Mancala[position] = 0;
		while(stones != 0){
			if(position == 12 && stones == 1){/*last stone lands in mancala*/
					position++;
					Mancala[position]++;
					stones--;
					if(is_game_over()){
						break;
					}
					//getline(cin, newCup)
					compute_moves(moves);
					newCup = moves.front();
					/*while (!is_legal(newCup)){
						getline(cin,newCup);
					}*/
					position = 13 - atoi(newCup.c_str());
					stones = Mancala[position];
					Mancala[position] = 0;
				}
			else if(position > 12){/*last stone makes it to other players side*/
				position = 0;
				for(int i = 0; i < stones; i++){
					if(position +i == 6){ position = 6;}
					Mancala[position + i]++;
				}
				stones = 0;
			}
			else { // last stone stays on current players side.
				if(stones == 1 && Mancala[position+1] == 0 && position > 6 && Mancala[12-position-1] != 0){//last stone lands in empty cup
					stones = Mancala[12- position-1] + 1;
					Mancala[12-position-1] = 0;
					Mancala[13] = Mancala[13] + stones;
					stones = 0;
				}
				else{//nothing special happens
					position++;
					Mancala[position]++;
					stones--;
				}
			}
		}
	}
	if(is_game_over()){
		int sum = 0; int sum2 = 0;
		for(int i = 0; i < 6; i++){
			sum = sum + Mancala[i];
			Mancala[i] = 0;
		}
		for(int j = 7; j < 13; j++){
			sum2 = sum2 + Mancala[j];
			Mancala[j] = 0;
		}
		if(sum2 == 0){
			Mancala[6] = Mancala [6] + sum;
			
		}
		else if(sum == 0){
			Mancala[13] = Mancala[13] + sum2;

		}
	}
	game::make_move(move);
}

bool mancala:: is_game_over()const{
	int sum = 0; int sum2 = 0;
	for(int i = 0; i < 6; i++){
		sum = sum + Mancala[i];
	}
	for(int j = 7; j < 13; j++){
		sum2 = sum2 + Mancala[j];
	}
	if(sum2 == 0){
		return true;
	}
	else if(sum == 0){
		return true;
	}
	else
		return false;
}

mancala::who mancala::winning() const{
	int computer = Mancala[13];
	int player = Mancala[6];
	if(player > computer){
		return HUMAN;
	}
	else if( computer > player){
		return COMPUTER;
	}
	else{
		return NEUTRAL;
	}
}

mancala::game* mancala:: clone()const{
	mancala* ptr;
	ptr = new mancala;
	ptr == this;
	ptr->game::make_move("Filler"); // this is to make the clone equal to a computer move
	return ptr;
}

void mancala::compute_moves(queue<string>& moves)const{
	if(is_legal("1")){
		moves.push("1");
	}
	else if(is_legal("2")){
		moves.push("2");
		}
	else if(is_legal("3")){
		moves.push("3");
	}	
	else if(is_legal("4")){
		moves.push("4");
	}	
	else if(is_legal("5")){
		moves.push("5");
	}		
	else{
		if(is_legal("6")){
			moves.push("6");
		}
	}
}

int mancala::evaluate()const{
	return Mancala[13];
}


