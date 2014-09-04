/*
* Project: Lab2
* Shane Deiley
* CSE 332S
* email: shanedeiley@wustl.edu
* Date Completed: 2/26/14
*/

#include "stdafx.h"
#include "NineAlmondsGame.h"
#include "GameBoard.h"
#include "GamePieces.h"
#include "oosdlStandard.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;


int main(int argc, char * argv[])
{
	string NineAlmonds = "NineAlmonds";
	if (argc == number_arguments && argv[file_name] == NineAlmonds)
	{
		NineAlmondsGame toPlay = NineAlmondsGame();
		return toPlay.play();
	}
	else
	{
		string message = "Try just one argument (besides program name): <NineAlmonds>";
		return usage_message(argv[program_name], message, not_NineAlmonds_error);
	}
}

