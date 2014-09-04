/*============================================================================
Project: Lab4
File: ReversiGame.cpp
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4/23/14
============================================================================*/

#include "stdafx.h"
#include "ReversiGame.h"
#include "GameBoard.h"
#include <iostream>
#include <sstream>
#include <fstream>

string ReversiGame::curPlrTurn = "";

// Constructor
ReversiGame::ReversiGame(string plrOnBlack, string plrOnWhite)
	:GameBase(RGROWS,RGCOLS), plrOnBlack_(plrOnBlack), plrOnWhite_(plrOnWhite)
{
	// Black gets first turn
	curPlrTurn = plrOnBlack_;

	ifstream ifsInitial(gameName);
	//no existing file to be opened. Create new file.
	if (!ifsInitial.is_open())
	{
		ofstream ofs(gameName);
		if (!ofs.is_open())
		{
			throw CANNOT_CREATE_FILE;
		}
		ofs << "NO DATA" << endl;
	} // Ofs destroyed (and automatically closed) when out of scope

	ifstream ifs(gameName);
	string name;
	getline(ifs, name);
	if (name == "NO DATA")
	{

		//add GamePieces to board
		for (int i = 0; i < rows_; ++i)
		{
			for (int j = 0; j < cols_; ++j)
			{
				GamePiece piece = GamePiece();

				pieces.push_back(piece); 

				if(int(piece.disp_.size()) > longestDisp_)
				{
					longestDisp_ = piece.disp_.size();
				}
			}
		}

		// Insert black pieces
		pieces[unsigned(.5*rows_*cols_ + .5*cols_)] = BLACK_PIECE;
		pieces[unsigned((.5*rows_-1)*cols_ + (.5*cols_ -1))] = BLACK_PIECE;

		// Insert white pieces
		pieces[unsigned((.5*rows_-1)*cols_ + .5*cols_)] = WHITE_PIECE;
		pieces[unsigned((.5*rows_)*cols_ + .5*cols_ -1)] = WHITE_PIECE;
	}
	else
	{
		//convert strings to ints as needed.
		string ints; 

		//Hold whomever's turn it was
		getline(ifs, ints);
		istringstream iss9(ints);
		if( !(iss9 >> curPlrTurn) )
		{
			throw CANNOT_CAST_TO_INT;
		}
		if(curPlrTurn != plrOnBlack_ && curPlrTurn != plrOnWhite_)
		{
			string input;
			cout << "Wrong name supplied. You can choose to terminate the saved game" << endl;
			cout << "or supply the correct name from the saved file after an error." << endl;
			cout << "To terminate, type \"Terminate\" " << endl;
			cin >> input;
			if(input == "Terminate")
			{
				ofstream ofs(gameName);
				if (!ofs.is_open())
				{
					throw CANNOT_CREATE_FILE;
				}
				ofs << "NO DATA" << endl;
				throw FORCED_TERMINATE;
			} // Ofs destroyed (and automatically closed) when out of scope
			else
				throw CHANGED_NAME_EXCEPTION;
		}

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

/* Operator calls print pieces and prints out the board */
ostream& operator<< (ostream& o, const ReversiGame & game)
{
	//using the printPieces function from GameBoard.
	try{
		printPieces(o, game.longestDisp_, game.pieces, RGROWS, RGCOLS);
	}
	catch(rtnValues)
	{
		throw;
	}

	return o;
}

// Prints by calling the friend operator on *this
void ReversiGame::print() 
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

/* 
* Returns true:
* (1) all pieces on the board are of the same color, or 
* (2) there are more pieces of one color than another color 
* on the board and either of the following is true: 
*	(a) all squares are filled; or 
*	(b) there are no remaining legal moves for either player
* Otherwise returns false.
*/
bool ReversiGame::done()
{
	bool hasWhite = false;
	int whiteCount = DEFAULT;
	bool hasBlack = false;
	int blackCount = DEFAULT;
	for(GamePiece gp: pieces)
	{
		if(gp.color_ == WHITE)
		{
			hasWhite = true;
			++whiteCount;
		}

		if(gp.color_ == BLACK)
		{
			hasBlack = true;
			++blackCount;
		}
	}

	// return true if all the pieces on the board are the same color
	if( (hasWhite || hasBlack) && !(hasWhite && hasBlack) )
	{
		if(blackCount > whiteCount)
		{
			cout << "Winner! " << plrOnBlack_ << endl;
		}
		else 
			cout << "Winner! " << plrOnWhite_ << endl;
		return true;
	}

	// return true if more pieces than another + other condition
	else if(whiteCount != blackCount)
	{
		if( (whiteCount + blackCount) == TOTAL_NUM_PIECES)
		{
			if(blackCount > whiteCount)
			{
				cout << "\nWinner! " << plrOnBlack_ << endl;
			}
			else 
				cout << "\nWinner! " << plrOnWhite_ << endl;
			return true;
		}
		else
		{
			if(!(this->movesRemain()))
			{
				if(blackCount > whiteCount)
				{
					cout << "\nWinner! " << plrOnBlack_ << endl;
				}
				else 
					cout << "\nWinner! " << plrOnWhite_ << endl;
				return true;
			}
			else
				return false;
		}
	}
	else
		return false;
}

/* 
* Returns true:
* (1) there are the same number of black pieces and white pieces on the board and 
*  either of the following is true:
*	(a) all squares are filled; or 
*	(b) there are no remaining legal moves for either player
* Otherwise return false.
*/
bool ReversiGame::stalemate()
{
	int whiteCount = DEFAULT;
	int blackCount = DEFAULT;
	for(GamePiece gp: pieces)
	{
		if(gp.color_ == WHITE)
			++whiteCount;
		if(gp.color_ == BLACK)
			++blackCount;
	}

	// Checks if #black = #white *and* if all pieces are in play or if no moves remain
	return ((whiteCount == blackCount) && (whiteCount + blackCount == TOTAL_NUM_PIECES || !(this->movesRemain())));
}

/* 
* The turn method for a ReversiGame.  Keeps track of whose turn it is.
*/
int ReversiGame::turn()
{

	bool invalidInput = true;
	int move = SUCCESS;
	unsigned x, y;

	if(curPlrTurn == plrOnBlack_)
	{
		cout << endl;
		try{
			print();
		}
		catch(rtnValues)
		{
			throw;
		}
		cout << curPlrTurn << "'s turn (X)." << endl;

		if( !(this->movesRemain(curPlrTurn)) )
		{
			cout << "No available moves for Black! White's turn (if possible)!" << endl;
			curPlrTurn = plrOnWhite_;
		}
		else
		{	
			while (invalidInput) 
			{
				cout << "Where would you like to place a piece?  <x,y>\n" << endl;
				try {
					move = prompt(x, y);

				}
				catch (rtnValues)
				{
					return USER_QUIT;
				}

				int index = y * cols_ + x;
				if(pieces[index].color_ == NONE)
				{
					// This gamepiece, inputted by reference, will refer to the end of the valid
					// continguous line of the white colors needing changed.
					vector<int> connectors;
					if(this->isValidMove(pieces[index], index, x, y, BLACK, connectors))
					{
						pieces[index] = BLACK_PIECE;
						for(int i:connectors)
						{
							pieces[i] = BLACK_PIECE;
						}
						invalidInput = false;	
					}
					else
					{
						cout << "Please select a valid destination." << endl;
					}
				}
				else
				{
					cout << "Please select an empty square." << endl;
				}
			}
		}
		curPlrTurn = plrOnWhite_;
		invalidInput = true;
	}

	if(curPlrTurn == plrOnWhite_)
	{
		cout <<endl;
		try{
			print();
		}
		catch(rtnValues)
		{
			throw;
		}
		cout << curPlrTurn << "'s turn (O)." << endl;

		if( !(this->movesRemain(curPlrTurn)) )
		{
			cout << "No available moves for White! Black's turn (if possible)!" << endl;
			curPlrTurn = plrOnBlack_;
		}
		else
		{	
			while (invalidInput) 
			{
				cout << "Where would you like to place a piece?  <x,y>\n" << endl;
				try {
					move = prompt(x, y);

				}
				catch (rtnValues)
				{
					return USER_QUIT;
				}

				int index = y * cols_ + x;
				if(pieces[index].color_ == NONE)
				{
					// This gamepiece, inputted by reference, will refer to the end of the valid
					// continguous line of the white colors needing changed.
					vector<int> connectors;
					if(this->isValidMove(pieces[index], index, x, y, WHITE, connectors))
					{
						pieces[index] = WHITE_PIECE;
						for(int i:connectors)
						{
							pieces[i] = WHITE_PIECE;
						}
						invalidInput = false;	
					}
					else
					{
						cout << "Please select a valid destination." << endl;
					}
				}
				else
				{
					cout << "Please select an empty square." << endl;
				}
			}
		}
		curPlrTurn = plrOnBlack_;
		invalidInput = true;
	}
	if(curPlrTurn != plrOnBlack_ && curPlrTurn != plrOnWhite_)
		CHANGED_NAME_EXCEPTION;
	return SUCCESS;
}

/*
* Helper method that helps identify whether or not
* valid moves remain.  Used in stalemate() and done().
* For each gamepiece that has a color:
* 1. Find if any adjacent pieces are of opposite color.
* 2. Record the direction of any such piecees.
* 3. Recurse in that direction until a original color is found or a black space is found.
*	- if blank return true;
*	- if opposite color, pop out of recursion and repeat for the next game piece
*/
bool ReversiGame::movesRemain()
{
	GamePiece current;
	int index;
	for(int i = 0; i < rows_; ++i)
	{
		for(int j = 0; j < cols_; ++j)
		{
			index = i*cols_ + j;
			current = pieces[index];
			if(current.color_ != NONE)
			{
				if(boundsHelper(i, j, current, index))
					return true;
			}
		}
	}
	return false;
}

/*
* SAME METHOD AS ABOVE EXCEPT SPECIFIED FOR A GIVEN PLAYER.
* Helper method that helps identify whether or not
* valid moves remain.  Used in stalemate() and done().
* For each gamepiece that has a color:
* 1. Find if any adjacent pieces are of opposite color.
* 2. Record the direction of any such piecees.
* 3. Recurse in that direction until a original color is found or a black space is found.
*	- if blank return true;
*	- if opposite color, pop out of recursion and repeat for the next game piece
*/
bool ReversiGame::movesRemain(string player)
{
	GamePiece current;
	int index;
	for(int i = 0; i < rows_; ++i)
	{
		for(int j = 0; j < cols_; ++j)
		{
			index = i*cols_ + j;
			current = pieces[index];
			if(player == plrOnBlack_)
			{
				if(current.color_ == BLACK)
				{
					if(boundsHelper(i, j, current, index))
						return true;
				}
			}
			else if (player == plrOnWhite_)
			{
				if(current.color_ == WHITE)
				{
					if(boundsHelper(i, j, current, index))
						return true;
				}
			}
		}
	}
	return false;
}

// This helper finds the bounds of the possible neighbors and enters them as parameters with
// the current GamePiece and its index in another helper.
bool ReversiGame::boundsHelper(unsigned i, unsigned j, GamePiece current, int index)
{
	unsigned int low_y, up_y, low_x, up_x;

	if (i == 0)
	{
		low_y = i;
		up_y = i + 1;
	}
	else if (i == rows_-1)
	{
		up_y = i;
		low_y = i - 1;
	}
	else{
		up_y = i + 1;
		low_y = i - 1;
	}
	if (j == 0)
	{
		low_x = j;
		up_x = j + 1;
	}
	else if (j == cols_-1)
	{
		up_x = j;
		low_x = j - 1;
	}
	else{
		up_x = j + 1;
		low_x = j - 1;
	}
	return findValidNeighbor(low_y, up_y, low_x, up_x, current, index);
}

// This helper takes in the bounds, iterates through the potential spots for neighbors,
// and attempts to identify a neighbor of differing color.  If successful, it returns the 
// helper that will iterate in that same direction attempting to find a valid move.
bool ReversiGame::findValidNeighbor(unsigned low_y, unsigned up_y, unsigned low_x, unsigned up_x, GamePiece current, int index)
{
	for (unsigned int k = low_y; k <= up_y; ++k)
	{
		for(unsigned int l = low_x; l <= up_x; ++ l)
		{
			unsigned neighbor_index = (cols_ * k) + l;
			GamePiece neighbor = pieces[neighbor_index];
			if(neighbor.color_ != current.color_)
			{
				if(iterateThroughNeighbor(k, l, neighbor, index, neighbor_index))
					return true;
			}
		}
	}
	return false;
}

// This method iterates through a given direction to identify if a valid move remained from some original piece.
bool ReversiGame::iterateThroughNeighbor(unsigned i, unsigned j, GamePiece current, int index, int currIndex)
{
	unsigned int low_y, up_y, low_x, up_x;

	if (i == 0)
	{
		low_y = i;
		up_y = i + 1;
	}
	else if (i == rows_-1)
	{
		up_y = i;
		low_y = i - 1;
	}
	else{
		up_y = i + 1;
		low_y = i - 1;
	}
	if (j == 0)
	{
		low_x = j;
		up_x = j + 1;
	}
	else if (j == cols_-1)
	{
		up_x = j;
		low_x = j - 1;
	}
	else{
		up_x = j + 1;
		low_x = j - 1;
	}

	GamePiece neighbor;
	unsigned neighbor_index = currIndex + (currIndex - index);

	for (unsigned int k = low_y; k <= up_y; ++k)
	{
		for(unsigned int l = low_x; l <= up_x; ++ l)
		{
			// Make sure neighbor_index is in fact within the bounds of the block of possible neighbors
			if(neighbor_index == k* cols_ + l)
			{
				neighbor = pieces[neighbor_index];
				if(neighbor.color_ == NONE) // Empty space => destination for valid move
					return true;
				else if(neighbor.color_ == current.color_) // same color => still possibly valid move, iterate again to see.
				{
					i = neighbor_index / cols_;
					j = neighbor_index % cols_;
					return iterateThroughNeighbor(i, j, neighbor, currIndex, neighbor_index);
				}
				else // Different color => no valid move in relation to original piece in this direction.
					return false; // Returning false pops the stack to the original movesRemain() method
				// which will simply loop to the next piece trying to find a move there.
			}
		}
	}

	return false;

}

// This method iterates through a given direction to identify if a valid move remained from some original piece.
bool ReversiGame::iterateThroughNeighborReverse(unsigned i, unsigned j, GamePiece current, int index, int currIndex)
{
	unsigned int low_y, up_y, low_x, up_x;

	if (i == 0)
	{
		low_y = i;
		up_y = i + 1;
	}
	else if (i == rows_-1)
	{
		up_y = i;
		low_y = i - 1;
	}
	else{
		up_y = i + 1;
		low_y = i - 1;
	}
	if (j == 0)
	{
		low_x = j;
		up_x = j + 1;
	}
	else if (j == cols_-1)
	{
		up_x = j;
		low_x = j - 1;
	}
	else{
		up_x = j + 1;
		low_x = j - 1;
	}

	GamePiece neighbor;
	unsigned neighbor_index = currIndex + (currIndex - index);

	for (unsigned int k = low_y; k <= up_y; ++k)
	{
		for(unsigned int l = low_x; l <= up_x; ++ l)
		{
			// Make sure neighbor_index is in fact within the bounds of the block of possible neighbors
			if(neighbor_index == k* cols_ + l)
			{
				neighbor = pieces[neighbor_index];
				if(neighbor.color_ == NONE) // Empty space => illegitmate direction for a valid move
					return false; // Pops stack, will check for legitimate neighbor again.
				else if(neighbor.color_ == current.color_) // same color => still possibly valid move, iterate again to see.
				{
					i = neighbor_index / cols_;
					j = neighbor_index % cols_;
					return iterateThroughNeighborReverse(i, j, neighbor, currIndex, neighbor_index);
				}
				else // Different color => valid move in relation to original piece in this direction.
				{
					return true;
				}
			}
		}
	}

	return false;

}

// Checks whether or not a specified empty space is a valid move
bool ReversiGame::isValidMove(GamePiece current, int index, unsigned j, unsigned i, kPieceColor curCol, vector<int> & toChange)
{
	unsigned int low_y, up_y, low_x, up_x;

	if (i == 0)
	{
		low_y = i;
		up_y = i + 1;
	}
	else if (i == rows_-1)
	{
		up_y = i;
		low_y = i - 1;
	}
	else{
		up_y = i + 1;
		low_y = i - 1;
	}
	if (j == 0)
	{
		low_x = j;
		up_x = j + 1;
	}
	else if (j == cols_-1)
	{
		up_x = j;
		low_x = j - 1;
	}
	else{
		up_x = j + 1;
		low_x = j - 1;
	}


	for (unsigned int k = low_y; k <= up_y; ++k)
	{
		for(unsigned int l = low_x; l <= up_x; ++ l)
		{
			unsigned neighbor_index = (cols_ * k) + l;
			GamePiece neighbor = pieces[neighbor_index];
			if(curCol != neighbor.color_ && neighbor.color_ != NONE)
			{
				if(iterateThroughNeighborReverse(k, l , neighbor, index, neighbor_index)){
					int dest = neighbor_index;
					while (pieces[dest].color_ != curCol)
					{
						toChange.push_back(dest);
						dest += neighbor_index - index;
					}
				}

			}
		}
	}
	return !toChange.empty();

}
