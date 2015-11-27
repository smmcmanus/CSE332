// Lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>

using namespace std;

#include "Header1.h"
#include "Games.h"
#include "GameBase.cpp"
#include "TicTacToe.cpp"
#include "Gomoku.cpp"


int main(int argc, char* argv[])
{
	GameBase* gb;
	try {
		gb = chooseGame(argc, argv);
	}
	catch (int BAD_ALLOC) {
		return BAD_ALLOC;
	}

	if (gb != 0) {
		shared_ptr<GameBase> ptr(gb);
		return gb->play();
	}
	else return usage_message(argv[0], "TicTacToe|Gomoku");
}

int usage_message(string program_name, string info)
{
	cout << "Usage: " << program_name << " " << info << endl;
	return INVALID_START;
}
