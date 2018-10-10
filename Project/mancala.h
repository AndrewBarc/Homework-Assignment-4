/********************************
Name:	Andrew Barcus
Date:	4/27/2018
File:	mancala.h
Project 6
Part: 	6-3
********************************/

#ifndef MANCALA_H
#define MANCALA_H
#include <string>
#include <iostream>
#include "game.h"
//using namespace main_savitch_14;
class mancala :public main_savitch_14::game{
	public:
		static const size_t MAX = 14;
		mancala();
		void display_status( )const;
		void make_move(const std::string& move);
		void restart();
		bool is_legal(const std::string& move)const;
		game* clone()const;
		void compute_moves(std::queue<std::string>& moves)const;
		int evaluate()const;
		bool is_game_over()const;
		mancala::who winning()const;
		
	private:
		int Mancala[MAX];
};
#endif
