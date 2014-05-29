/*============================================================================
Project: Lab4
File: Lab4.cpp
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4/23/14
============================================================================*/

#include "stdafx.h"
#include "GameBase.h"
#include <memory>
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
	try{
		GameBase::instantiate(argv, argc);

		return GameBase::instance()->play();
		
	}
	catch(bad_alloc b)
	{
		return usefulMsg("Lab4", "Memory could not be allocated.", OUT_OF_MEMORY);
	}
	catch(rtnValues r)
	{
		if (r == INVALID_BOARD_DIMENSIONS)
			return usefulMsg("Lab4", "Board must be a square with side length other than 2.", INVALID_BOARD_DIMENSIONS);
	
		if (r == GAMEPIECE_MISSING_OR_INVALID)
			return usefulMsg("Lab4", "Invalid or missing game piece(s).", GAMEPIECE_MISSING_OR_INVALID);
		
		if (r == WRONG_SIZE_GAMEPIECE_VECTOR)
			return usefulMsg("Lab4", "Invalid gamepiece vector.", WRONG_SIZE_GAMEPIECE_VECTOR);

		if (r == NONNUMERIC_GAMEPIECE)
			return usefulMsg("Lab4", "Textual display for game pieces must be numerical values.", NONNUMERIC_GAMEPIECE);
	
		if (r == NEGATIVE_GAMEPIECE)
			return usefulMsg("Lab4", "Game pieces must have positive values.", NEGATIVE_GAMEPIECE);
		
		if (r == NULL_POINTER)
			return usefulMsg("Lab4", "Static GameBase pointer has not been initialized.", NULL_POINTER);

		if (r == NOT_NULL_POINTER)
			return usefulMsg("Lab4", "Static GameBase pointer already instantiated.", NOT_NULL_POINTER);

		if (r == TOO_FEW_ARGS)
			return usefulMsg("Lab4", "Too few arguments given. Proper usage: <file_name> <game_name>\nIf \"Reversi\", specify <playerOnBlack> <playerOnWhite> as well.", TOO_FEW_ARGS);

		if (r == TOO_MANY_ARGS)
			return usefulMsg("Lab4", "Too many arguments given. Proper usage: <file_name> <game_name>\nIf \"Reversi\", specify <playerOnBlack> <playerOnWhite> as well.", TOO_MANY_ARGS);

		if (r == INVALID_ARGS)
			return usefulMsg("Lab4", "Wrong number of arguments given. Proper usage: <file_name> <game_name>\nIf \"Reversi\", specify <playerOnBlack> <playerOnWhite> as well.", INVALID_ARGS);

		if (r == INVALID_GAME_NAME)
			return usefulMsg("Lab4", "Invalid game name given. Proper usage: <file_name> <game_name>\nIf \"Reversi\", specify <playerOnBlack> <playerOnWhite> as well.", INVALID_GAME_NAME);

		if (r == CANNOT_CREATE_FILE)
			return usefulMsg("Lab4", "Could not create valid output file.", CANNOT_CREATE_FILE);
	
		if (r == CANNOT_CAST_TO_INT)
			return usefulMsg("Lab4", "Invalid line in file. Could not parse.", CANNOT_CAST_TO_INT);

		if (r == CHANGED_NAME_EXCEPTION)
			return usefulMsg("Lab4", "The names specified do not match the saved game's current player record.\nRetry with the names of the previous players.", CHANGED_NAME_EXCEPTION);
		
		if (r == FORCED_TERMINATE)
			return usefulMsg("Lab4", "Game save was reset. Please restart game.", FORCED_TERMINATE);
	}
}

