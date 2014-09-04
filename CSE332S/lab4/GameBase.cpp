/*============================================================================
Project: Lab4
File: GameBase.cpp
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4/23/14
============================================================================*/

#include "stdafx.h"
#include "GameBase.h"
#include "NineAlmonds.h"
#include "MagicSquare.h"
#include "ReversiGame.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

shared_ptr<GameBase> GameBase::ptr = nullptr;
int GameBase::turns = 0;
string GameBase::gameName = "";

//Instantiates GameBase
GameBase::GameBase(int rows, int cols): rows_(rows), cols_(cols), longestDisp_(0), pieces(vector<GamePiece>()){};

//creates a new game object.
void GameBase::instantiate(char* args[], int numArgs)
{
	if (ptr != nullptr)
	{
		throw NOT_NULL_POINTER;
	}

	if (numArgs < NUM_CMD_ARGS) //check for correct number of arguments.
	{
		throw TOO_FEW_ARGS;
	}
	else if (numArgs == IN_BETWEEN_ARGUMENT_COUNT)
	{
		throw INVALID_ARGS;
	}
	else if (numArgs > REVERSI_CMD_ARGS)
	{
		throw TOO_MANY_ARGS;
	}
	else
	{
		if ( (string(args[GAME_NAME]) == "NineAlmonds") && (numArgs == NUM_CMD_ARGS) )
		{
			try{
				gameName = args[GAME_NAME];
				ptr = make_shared<NineAlmonds>();
			}
			catch(bad_alloc)
			{
				throw;
			}	
		} 
		else if ( (string(args[GAME_NAME]) == "MagicSquare") && (numArgs == NUM_CMD_ARGS) )
		{
			if (MAGICCOLS == MAGICROWS || MAGICCOLS == BAD_MAGIC_LENGTH && MAGICROWS == BAD_MAGIC_LENGTH)
			{
				try{
					gameName = args[GAME_NAME];
					ptr = make_shared<MagicSquare>();
				}
				catch(bad_alloc)
				{
					throw;
				}
			}
			else
			{
				throw INVALID_BOARD_DIMENSIONS;
			}
		}
		else if ( (string(args[GAME_NAME]) == "Reversi") && (numArgs == REVERSI_CMD_ARGS) )
		{
			try{
				gameName = args[GAME_NAME];
				ptr = make_shared<ReversiGame>(string(args[PLAYER_ONE]), string(args[PLAYER_TWO]));
			}
			catch(bad_alloc)
			{
				throw;
			}
		}
		else
		{
			throw INVALID_GAME_NAME;
		}
	}

}

//Runs the game. manages the turns
int GameBase::play()
{

	while (true)
	{
		try{
			if (!done())
			{
				if (!stalemate())
				{
					if (turn() != USER_QUIT)
					{
						++turns;
					}
					else
					{
						try{
							savePrompt();
						}
						catch(rtnValues)
						{
							throw;
						}
						cout<< '\n' << turns << " turns were taken before you quit." << endl;
						return USER_QUIT;
					}
				}
				else
				{
					cout<< '\n' << turns << " turns were taken." << endl;
					cout << "No valid moves remain.  Stalemate." << endl;
					ofstream oss (gameName);
					if (!oss.is_open())
					{
						throw CANNOT_CREATE_FILE;
					}
					oss << "NO DATA" << endl;		//overwrite file to start new game.
					return STALEMATE;
				}
			}
			else
			{
				cout <<endl;
				try
				{
					print();
				}
				catch(rtnValues)
				{
					throw;
				}
				cout<< "\nCongratulations! It took " << turns << " turns to finish the game." << endl;
				ofstream oss (gameName);
				if (!oss.is_open())
				{
					throw CANNOT_CREATE_FILE;
				}
				oss << "NO DATA" << endl;		//overwrite file to start new game.
				return SUCCESS;
			}
		}
		catch(rtnValues)
		{
			throw;
		}
	}
}

//Prompts the user for input.
int GameBase::prompt(unsigned int & x, unsigned int & y)
{
	bool invalid_input = true;
	int attempts = 0;
	while (invalid_input)
	{
		string input;
		getline (cin, input);
		if (input == "quit")
		{
			throw (USER_QUIT);	//quit program
		}
		if (input == "cancel") //cancel currently selected piece.
		{
			return USER_CANCEL;
		}
		auto ptr = find(input.begin(), input.end(), ','); //find the comma
		if (ptr != input.end()){
			*ptr = ' '; //set comma to empty space
			istringstream iss(input);
			if (iss >> x && iss >> y)
			{
				// ensure x and y are within proper range
				if (x >= 0 && int(x) < cols_ && y >= 0 && int(y) < rows_)
				{
					invalid_input = false;
				}
				else
				{
					cout << '\n' << endl;
					try{
						print();
					}
					catch(rtnValues)
					{
						throw;
					}
					cout << "\nCoordinates must be within the gameboard's dimensions." << endl;
					cout << "Please give valid input.\n" << endl;
					continue;
				}
			}	
			else
			{
				cout << '\n' << endl;
				try{
					print();
				}
				catch(rtnValues)
				{
					throw;
				}
				cout << "\nCoordinates should be integers separated by a comma. ex. 2,3" << endl;
				cout << "Please give valid input.\n" << endl;
				continue;
			}
		}
		else
		{
			cout << '\n' << endl;
			try{
				print();
			}
			catch(rtnValues)
			{
				throw;
			}
			cout << "\nCoordinates should be integers separated by a comma. ex. 2,3" << endl;
			cout << "Please give valid input.\n" << endl;
			continue;
		}
	}
	return SUCCESS;
}

// Checks if the game has been instantiated; if so, returns ptr, otherwise null.
shared_ptr<GameBase> GameBase::instance()
{
	if (ptr == nullptr)
	{
		throw NULL_POINTER;
	}
	else
	{
		return ptr;
	}
}

// This is called when a user quits.  Gives the user the option to
// save the state of the game.  Then this mehtod writes the game's members
// to a file for future reading.
void GameBase::savePrompt()
{
	bool invalidInput = true;
	string input;
	ofstream oss(gameName);
	if (!oss.is_open())
	{
		throw CANNOT_CREATE_FILE;
	}
	cout <<  "Would you like to save the game?" << endl;
	while (invalidInput)
	{
		cin >> input;
		if (input == "y"||input=="Y"||input=="yes"||input=="Yes") //acceptable yes values
		{
			oss << gameName << endl;
			if(gameName == "Reversi")
			{
				oss << ReversiGame::curPlrTurn << endl;
			}
			oss << rows_ << endl;
			oss << cols_ << endl;
			oss << turns << endl;
			oss << longestDisp_ << endl;
			for (GamePiece piece: pieces)
			{
				oss << colorEnumToString(piece.color_) << " " << piece.name_ << " " << piece.disp_ << endl;
			}
			return;
		}
		else if (input=="n"||input=="N"||input=="No"||input=="no") //acceptable no values
		{
			oss << "NO DATA" << endl;
			return;
		}
		else
		{
			cout << "Invalid input. Please indicate \"Yes\" or \"No\"." << endl;
		}
	}
}