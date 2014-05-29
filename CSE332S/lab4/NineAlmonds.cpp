/*============================================================================
Project: Lab4
File: NineAlmonds.cpp
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4/23/14
============================================================================*/

#include "stdafx.h"
#include "NineAlmonds.h"
#include "GameBoard.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;



//Returns true if only almond remaining in center square
bool NineAlmonds::done()
{
	//iterate through game piece vector
	int remaining_pieces(0);
	for (auto itr = pieces.begin(); itr < pieces.end(); ++itr)
	{
		if (isAlmond(*itr))
		{
			++remaining_pieces;
		}
	}
	int center_squre_index = CENTER_Y*cols_ + CENTER_X;
	return (remaining_pieces == 1 && isAlmond(pieces[center_squre_index]));
}

//Checks if move is valid
int NineAlmonds::isValidMove(int& beg_x, int& beg_y, int& end_x, int& end_y)
{
	int beg_index = beg_y * cols_ + beg_x;
	int end_index = end_y * cols_ + end_x;

	//1. check that the beginning square contains an almond.
	if (isAlmond(pieces[beg_index]))
	{
		//2. check that destination squre is empty.
		if (isEmpty(pieces[end_index]))
		{
			//3. check that destination is 2 squares away from source in all directions.
			int x_dist = abs(end_x - beg_x);
			int y_dist = abs(end_y - beg_y);
			if ((x_dist == 2 &&  y_dist == 2) || (x_dist == 2 && y_dist == 0) || (x_dist == 0 && y_dist == 2))
			{
				//4. check that square between source and destination has an almond.
				if (isAlmond(pieces[(end_y + beg_y)/2*cols_ + (end_x + beg_x)/2]))
				{
					return SUCCESS;
				}
				else
				{
					return	INVALID_JUMP;
				}
			}
			else
			{
				return INVALID_DISTANCE;
			}
		}
		else
		{
			return INVALID_DESTINATION;
		}
	}
	else
	{
		return INVALID_SOURCE;
	}
}

//Defines the nineAlmonds class and initializes the gamepieces in its vector.
NineAlmonds::NineAlmonds(): GameBase(ALMONDROWS, ALMONDCOLS) 
{
	ifstream ifsInitial(gameName);
	//IF no existing file can be opened then create new file - this will happen on first gameplay.
	if (!ifsInitial.is_open())
	{
		ofstream ofs(gameName);
		if (!ofs.is_open())
		{
			throw CANNOT_CREATE_FILE;
		}
		ofs << "NO DATA" << endl;
	} // ofs closed when destroyed - it goes out of scope

	ifstream ifs(gameName);
	string name;
	getline(ifs, name); // Will either be the (previously checked) name of the game or "NO DATA" to signal a fresh game start.
	if (name == "NO DATA")
	{

		//construct default game.
		for (int i = 0; i < rows_; ++i)
		{
			for (int j = 0; j < cols_; ++j)
			{
				GamePiece almond;
				if ((i * j) % 4 != 0 || (i==2 && j==2))	//equivalent to the 3x3 center of the board.
				{
					almond = GamePiece(BROWN, "almond", ALMOND_DISPLAY); //almond pieces
				}
				else
				{
					almond = GamePiece(); //empty spaces
				}

				pieces.push_back(almond); 

				if(int(almond.disp_.size()) > longestDisp_)
				{
					longestDisp_ = almond.disp_.size();
				}
			}
		}
	}

	//construct game from previously saved version.
	else
	{
		//convert strings to ints as needed.
		string ints; 

		//rows
		getline(ifs, ints);
		istringstream iss(ints);
		if (!(iss >> rows_) )
		{
			throw CANNOT_CAST_TO_INT;
		}

		//cols
		getline(ifs, ints);
		istringstream iss2(ints);
		if (!(iss2 >> cols_) )
		{
			throw CANNOT_CAST_TO_INT;
		}

		//turns
		getline(ifs, ints);
		istringstream iss3(ints);
		if (!(iss3 >> turns) )
		{
			throw CANNOT_CAST_TO_INT;
		}

		//longestDisp
		getline(ifs, ints);
		istringstream iss4(ints);
		if (!(iss4 >> longestDisp_) )
		{
			throw CANNOT_CAST_TO_INT;
		}

		//pieces
		string piece;
		while (getline(ifs, piece))
		{
			istringstream iss5(piece);
			GamePiece gPiece;
			string color;
			iss5 >> color;
			gPiece.color_ = colorStringToEnum(color);
			iss5 >> gPiece.name_;
			iss5 >> gPiece.disp_;
			

			//add piece to vector
			pieces.push_back(gPiece);
		}
	}
}

	//Prints the game board.
	void NineAlmonds::print()
	{
		try
		{
			cout << *this << endl;
		}
		catch(rtnValues)
		{
			throw;
		}
	}

	//Checks if there is a stalemate.
	bool NineAlmonds::stalemate()
	{
		bool valid_moves = false;
		int index, x, y;
		int num_valid_moves = 0;
		//iterate thru pieces and check for any valid moves
		for (auto piece = pieces.begin(); piece < pieces.end(); ++piece)
		{
			if (isAlmond(*piece))
			{
				index = piece - pieces.begin();
				x = index%cols_;
				y = index/cols_;
				//cout << x << "," << y << endl;
				//iterate thru possible destinations
				for (int x2 = x-2; x2 <= x + 2; x2+=2)
				{
					if (x2 > 0 && x2 < cols_)
					{
						for (int y2 = y-2; y2 <= y + 2; y2+=2)
						{
							if(y2 > 0 && y2 < cols_)
							{
								int test = isValidMove(x, y, x2, y2);
								if(test == SUCCESS)
								{
									++num_valid_moves;
								}
							}
						}
					}
				}
			}
		}
		if (num_valid_moves > 0)
		{
			valid_moves = true;
		}
		return !valid_moves; 
	}

	//Runs one game turn.
	int NineAlmonds::turn()
	{
		// beginning and ending coordinates initialized with an invalid value
		cout << '\n' << endl;
		try{
			print();
		}
		catch(rtnValues)
		{
			throw;
		}
		unsigned int beg_x, beg_y, end_x, end_y;
		bool keep_trying = true;
		bool user_has_continued = false;
		ostringstream valid_moves;
		cout << "\nEnter \"cancel\" to cancel selection or\n\"quit\" to exit game." << endl;
		while (keep_trying)
		{
			//prompt user for beginning coordinates
			resetCoords(beg_x, beg_y, end_x, end_y);	
			int move = SUCCESS;
			cout << "\nWhich piece would you like to move? (x,y)\n" << endl;
			try
			{
				move = prompt(beg_x, beg_y);
			}
			//user quit
			catch(rtnValues quit)
			{
				return quit;
			}
			//user cancelled move
			if (move == USER_CANCEL)
			{
				continue;
			}
			//ensure source square contains an almond.
			if (isAlmond(pieces[beg_y*cols_ + beg_x]))
			{
				//add source coordinates to valid move output.
				valid_moves.str("");
				valid_moves.clear();
				valid_moves << beg_x << ',' << beg_y;

				bool continue_move = true;
				while(continue_move)
				{
					//prompt user for destination coordinates
					cout << "\nWhere would you like to move?\n" << endl;
					try{
						move = prompt(end_x, end_y);
					}
					catch(rtnValues quit)
					{
						return quit;
					}
					if (move == USER_CANCEL)
					{
						//if user tries to cancel mid-streak, turn is ended.
						if (user_has_continued)
						{
							keep_trying = false;
							break;
						}
						else{
							break; // go back to beginning (asking for source).
						}
					}
					int beg_x1 = (int)beg_x;
					int beg_y1 = (int)beg_y;
					int end_x1 = (int)end_x;
					int end_y1 = (int)end_y;
					move = isValidMove(beg_x1, beg_y1, end_x1, end_y1);
					if (move == SUCCESS){  //ensure move validity
						//replace pieces where appropriate

						GamePiece almond = GamePiece(BROWN, "almond", ALMOND_DISPLAY);
						GamePiece empty = GamePiece();
						pieces[beg_y * cols_ + beg_x] = empty;	//set source to empty
						pieces[end_y * cols_ + end_x] = almond;	//set dest to almond
						pieces[(end_y + beg_y)/2*cols_ + (end_x + beg_x)/2] = empty; //set inbetween space to empty.

						keep_trying = false; //don't ask for source anymore this turn.
						cout << '\n' << endl;

						//add valid move to valid list output.
						valid_moves << " to " << end_x << ',' << end_y;

						cout << "\nPlease enter coordinate \"x, y\"," <<endl;
						cout << "\"cancel\" to cancel piece selection, or \"quit\" to exit game.\n" << endl;

						//print display
						cout << '\n';
						print();
						cout << '\n' << endl;
						cout << valid_moves.str() << endl;

						//move again?
						continue_move = promptYesNo();
						user_has_continued = continue_move;
						//old destination is new source.
						beg_x = end_x;
						beg_y = end_y;
					}
					else if (move == INVALID_DESTINATION)
					{
						cout << '\n';
						print();
						cout << "\nDestination square must not contain an almond." << endl;
						continue;
					}
					else if (move == INVALID_JUMP)
					{
						cout << '\n';
						print();
						cout << "\nSquare between source and destination must contain an almond." << endl;
						continue;
					}
					else if (move == INVALID_DISTANCE)
					{
						cout << '\n';
						print();
						cout << "\nMoves can be vertical, horizontal, or diagonal but must jump an adjacent almond." << endl;
						continue;
					}
				}
			}
			else
			{
				cout << '\n';
				print();
				cout << "\nSource square must contain an almond." << endl;
				continue;
			}
		}
		return SUCCESS;
	}


	//Checks if GamePiece is an Almond.
	bool isAlmond(const GamePiece& piece)
	{
		return (piece.disp_ == ALMOND_DISPLAY);
	}

	//Checks that coordinates have been set.  All arguments default to zero, so any or all coords
	//can be checked.
	bool isCoordsSet(unsigned int beg_x, unsigned int beg_y, unsigned int end_x, unsigned int end_y)
	{
		return (beg_x != ALMONDCOLS && beg_y != ALMONDROWS && end_x != ALMONDCOLS && end_y != ALMONDROWS);
	}

	//Checks if GamePiece is empty.
	bool isEmpty(const GamePiece& piece)
	{
		return (piece.disp_ == ALMOND_EMPTY_DISPLAY);
	}

	//Overloads the << operator to print instances of nineAlmonds.
	ostream& operator<< (ostream& o, const NineAlmonds & game)
	{
		//using the printPieces function from GameBoard.
		try{
			int rows = game.rows_;
			int cols = game.cols_;
			printPieces(o, game.longestDisp_, game.pieces, rows, cols);

		}
		catch(rtnValues)
		{
			throw;
		}
		return o;
	}

	//Asks the user whether they would like to continue the turn.
	bool promptYesNo()
	{
		string response = "";
		bool invalid_input = true;
		int attempts = 0;
		while (invalid_input)
		{
			++attempts;
			if (attempts > 1){
				cout << "\nPlease give valid answer." << endl;
			}
			cout << "Continue this turn? (y/n)" << endl;
			getline(cin, response);
			if (response == "y" || response == "yes" || response == "Y" || response == "Yes")
			{
				return true;
			}
			else if (response == "n" || response == "no" || response =="N" || response == "No")
			{
				return false;
			}
		}
		return false; //shouldn't ever reach this point. Added so all control paths return a value.
	}

	//Resets the source and destination coordinates
	int resetCoords(unsigned int& beg_x, unsigned int& beg_y, unsigned int& end_x, unsigned int& end_y)
	{
		beg_x = ALMONDCOLS;
		beg_y = ALMONDROWS;
		end_x = ALMONDCOLS;
		end_y = ALMONDROWS;
		return SUCCESS;
	}




