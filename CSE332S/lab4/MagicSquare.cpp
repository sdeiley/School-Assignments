/*============================================================================
Project: Lab4
File: MagicSquare.cpp
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4/23/14
============================================================================*/

#include "stdafx.h"
#include "MagicSquare.h"
#include "GameBoard.h"
#include <sstream>
#include <iostream>

using namespace std;

//Defines the MagicSquare class and initializes the gamepieces in its vector.
MagicSquare::MagicSquare(): GameBase(MAGICROWS, MAGICCOLS), numbers(vector<int>())
{
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

		//fill vector with available numbers.
		for (int i = 1; i <= rows_*cols_; ++i)
		{
			numbers.push_back(i);
		}

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
	}
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

		//fill vector with available numbers.
		for (int i = 1; i <= rows_*cols_; ++i)
		{
			numbers.push_back(i);
		}

		//remove already used numbers from vector
		for (GamePiece g:pieces)
		{
			for (int i:numbers)
			{
				if ( (g.disp_ != " ") && strToNum(g.disp_) == i)
				{
					numbers[i-1] = 0;
				}
			}
		}

	}
}

//Prints the game board.
void MagicSquare::print()
{
	try
	{
		cout << *this << endl;
	}
	catch(rtnValues)
	{
		throw;
	}

	printAvailable(numbers);
}

//Checks if the game is over. i.e. all rows, columns, and diagonals
//sum to the same "magic" number.
bool MagicSquare::done()
{
	//check that all spaces are filled.
	for (GamePiece g: pieces)
	{
		if (!containsPiece(g))
		{
			return false;
		}
	}


	//magic sum forumla
	int magicSum = rows_*(rows_*cols_ + 1)/2;

	//check rows
	for (int i = 0; i< rows_*cols_; i+=cols_)
	{
		int sum = 0;
		for (int j = i; j< i+cols_; ++j)
		{
			try
			{
				sum+=strToNum(pieces[j].disp_);
			}
			catch(rtnValues) //if piece display is not a positive number.
			{
				throw;
			}
		}
		if (sum != magicSum)
		{
			return false;
		}
	}

	//check columns

	for (int i = 0; i< cols_; ++i)
	{
		int sum = 0;
		for (int j = i; j<rows_*cols_; j+=rows_)
		{
			try
			{
				sum += strToNum(pieces[j].disp_);
			}
			catch(rtnValues)
			{
				throw;
			}
		}
		if (sum!=magicSum)
		{
			return false;
		}
	}

	//check diagonals

	int sum = 0;
	for (int i = 0; i<rows_*cols_; i = i+cols_+1)
	{
		try
		{
			sum += strToNum(pieces[i].disp_);
		}
		catch(rtnValues)
		{
			throw;
		}
	}
	if (sum!= magicSum)
	{
		return false;
	}

	sum = 0;
	for (int i = rows_*(cols_ - 1); i > 0; i = i-cols_ + 1)
	{
		try
		{
			sum += strToNum(pieces[i].disp_);
		}
		catch(rtnValues)
		{
			throw;
		}
	}
	//check is complete.
	return (sum == magicSum);
}

//Checks if a stalemate has occurred.
bool MagicSquare::stalemate()
{
	//make sure all spaces are filled
	for (GamePiece g: pieces)
	{
		if (!containsPiece(g))
		{
			return false;
		}
	}

	return (!done());
}

//Prompts the user for a piece selection.
void MagicSquare::prompt(unsigned& piece)
{
	bool invalid_input = true;
	cout << "\n\nPlease enter a piece to place\nor \"quit\" to exit game.\n" <<endl;
	int value = 0;
	while (invalid_input)
	{
		string input;
		getline (cin, input);
		if (input == "quit")
		{
			throw USER_QUIT;	//quit program
		}
		try
		{
			value = strToNum(input);
		}
		catch(rtnValues)
		{
			cout << "\nPlease enter a valid available piece.\n" <<endl;
			continue;
		}
		if (value <= rows_*cols_ && numbers[value-1] == value)
		{
			invalid_input = false;
		}
		else
		{
			cout << "\nPlease enter a valid available piece.\n" <<endl;
			continue;
		}
	}
	piece = value;

}

//Runs one game turn.
int MagicSquare::turn(){

	bool selectionMade = false;
	bool allSelectionsMade = false;
	unsigned piece = 0;
	unsigned x = 0;
	unsigned y = 0;
	int prompted = 0;
	int index = 0;

	while(!allSelectionsMade)
	{
		selectionMade = false;
		cout << '\n' << endl;
		try{
			print();
		}
		catch(rtnValues)
		{
			throw;
		}
		//obtain piece to move
		piece = 0;
		try
		{
			prompt(piece);
		}
		catch(rtnValues) //user quit
		{
			return USER_QUIT;
		}

		while(!selectionMade)
		{
			//obtain destination coordinates
			cout << "\nWhere would you like to move the " <<  piece << "?" <<endl;
			cout << "Enter valid x,y coordinates, \"cancel\" to cancel selection,\nor \"quit\" to quit." << endl;
			x = 0;
			y = 0;
			prompted = 0;


			try
			{
				prompted = GameBase::prompt(x,y);
			}
			catch(rtnValues)
			{
				return USER_QUIT;
			}
			if (prompted == USER_CANCEL) //cancel piece selection.
			{
				selectionMade = true;
				allSelectionsMade = false;
				continue;
			}

			index = y*cols_ + x;

			if (containsPiece(pieces[index]))
			{
				selectionMade = false;
				cout << "\nPlease select an empty destination square." << endl;
				continue;
			}
			else
			{
				selectionMade = true;
				allSelectionsMade = true;
			}
		}
	}
	string disp = numToString(piece);
	if (int(disp.size()) > longestDisp_)
	{
		longestDisp_ = disp.size();

	}
	GamePiece number = GamePiece(NONE, numToString(piece), disp); //make the piece to be added
	pieces[index] = number; //add piece to display
	numbers[piece-1] = 0; //remove piece from available list.

	return SUCCESS;
}

//Checks if gamepiece is empty or not.
bool containsPiece(GamePiece g)
{
	return (g.disp_ != MAGIC_EMPTY_DISPLAY);
}

//Converts numerical string into its integer representation.
int strToNum(string s)
{
	istringstream iss(s);
	int result;
	if (!(iss >> result))	//attempt conversion from string to int.
	{
		throw NONNUMERIC_GAMEPIECE;
	}
	if (result <= 0)
	{
		throw NEGATIVE_GAMEPIECE;
	}
	return result;
}

//Converts integer into its string representation.
string numToString(unsigned i)
{
	ostringstream output;
	output << i;
	return output.str();

}

//Overloads the << operator to print instances of MagicSquare.
ostream& operator<< (ostream& o, const MagicSquare & game)
{
	//using the printPieces function from GameBoard.
	try{
		printPieces(o, game.longestDisp_, game.pieces, MAGICROWS, MAGICCOLS);
	}
	catch(rtnValues)
	{
		throw;
	}

	return o;
}

//Prints out the available pieces.
void printAvailable(vector<int> numbers)
{
	ostringstream oss;
	oss << "Available pieces: ";
	for (int i: numbers)
	{
		if (i != 0)
		{
			oss << i << " ";
		}
	}
	cout << oss.str();

}
