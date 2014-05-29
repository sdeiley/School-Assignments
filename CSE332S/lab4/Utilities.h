/*============================================================================
Project: Lab4
File: Utilities.h
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4-23-14
============================================================================*/

#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
using namespace std;


//relevant indices
enum indices {PROGRAM_NAME, INPUT_FILE_NAME, NUM_CMD_ARGS, IN_BETWEEN_ARGUMENT_COUNT, 
			  REVERSI_CMD_ARGS, GAME_NAME = 1, PLAYER_ONE = 2, PLAYER_TWO = 3};   

//possible success and failure return values
enum rtnValues {SUCCESS, CANNOT_OPEN_FILE, TOO_FEW_ARGS, TOO_MANY_ARGS, INVALID_ARGS,
				READ_LINE_ERROR, LINE_READ_NO_BOARD_DIMS,
				NO_WELL_FORMED_PIECES_READ, WRONG_SIZE_GAMEPIECE_VECTOR,
				GAMEPIECE_MISSING_OR_INVALID, NO_BOARD_DIMS_IN_FILE, USER_QUIT, 
				INVALID_COORDINATE, STALEMATE, USER_CANCEL, INVALID_SOURCE, INVALID_DESTINATION,
				INVALID_JUMP, INVALID_DISTANCE, OUT_OF_MEMORY, NONNUMERIC_GAMEPIECE,
				NEGATIVE_GAMEPIECE, INVALID_BOARD_DIMENSIONS, NULL_POINTER, NOT_NULL_POINTER,
				INVALID_GAME_NAME, CANNOT_CREATE_FILE, CANNOT_CAST_TO_INT, CHANGED_NAME_EXCEPTION,
				FORCED_TERMINATE}; 

//FUNCTIONS//
int parser(vector<string> &, char *);
int usefulMsg (const string &, const string &, int);
void makeLower(string &);

#endif