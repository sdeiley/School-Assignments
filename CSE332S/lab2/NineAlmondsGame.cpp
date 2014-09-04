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
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// We define the operator to print out the NineAlmondsGame using the previously
// defined piece_print_out method with one alteration - it also prints the indices
// on the outside of the game board so those indices can be referenced as specified.
// This function finally returns another ostream so that it can be called repeatedly.
ostream & operator<< (ostream & oss, const NineAlmondsGame & game)
{
	piece_print_out(game.almonds, game.columns, game.rows);
	return oss;
}

// This is the done() function, returning true iff there is a piece
// at (2,2).  This would be true if the index of the almong game_piece vector
// had an almond at 12 because width*2 + 2 = 12.
bool NineAlmondsGame::done()
{
	int cols = (int) columns;
	int rowz = (int) rows;
	for (int i = 0; i < cols*rowz; ++i)
	{
		if (i == 12)
		{
			if (almonds[i].piece_name != "almond")
				return false;
		}
		else
		{
			if (almonds[i].piece_name == "almond")
				return false;
		}
	}
	return true;
}

// This checks whether there exist any possible moves on the board.
// Return true if there is in fact no legitimate moves.
bool NineAlmondsGame::stalemate()
{
	// Return false if done is true
	if (done())
		return false;
	
	// Now check all possible moves in a double for loop through the almonds vector.
	// If there is even one possible move, it will return false.  Otherwise, the 
	// function will eventually return true.
	int counter = 0;
	int counterTwo = 0;
	int cols = (int) columns;
	int rowz = (int) rows;

	for (int i = 0; i < cols*rowz; ++i)
	{
		if (almonds[i].piece_name == "almond")
		{			
			for (int j = 0; j < cols*rowz; ++j)
			{
				if (almonds[j].piece_name != "almond")
				{
					int startCol = i % cols;
					int startRow = i / cols;
					int endCol = j % cols;
					int endRow = j / cols;

					if (is_valid_move(startCol, startRow, endCol, endRow))
					{
						return false;
					}
				}
			}
		}
	}

	// No other possible move options...
	return true;
}

// This function prompts the user for the potential move.
void NineAlmondsGame::prompt(unsigned & column, unsigned & row)
{
	// Initial message the prompt user
	cout << "Select position #,# or quit." << endl;

	string input;
	getline(cin, input);
	

	// Check to see if quit was the input
	if (input == "quit")
		throw quit_command;

	// Now replace commas with spaces
	auto position = input.find(',');
	if (position != string::npos)
		input.replace(input.find(','), 1, " ");

	// Check to see the current string is the correct size,
	// namely three, since it should be #_#.
	// The specificity of this conditional ensures correct input.
	// The prompt message is specific enough that this shouldn't be a problem
	string space(" ");
	if (input.size() == 3 && input.find(space) == 1)
	{
		// Wrap it in the string stream and extract to unsigneds
		istringstream iss(input);
		iss >> column;
		iss >> row;
		if ((column < 0 || column > 4) || (row < 0 || row > 4))
		{
			cout << '\n' << "Whoa: input was out of bounds.  Confine to " << endl;
			cout << " range of [0,4] in the format \"#,\" (w/o quotes)" << endl;
			return prompt(column, row);
		}
	}
	else
	{
		cout << '\n' << "BAD INPUT: Read the following carefully: " << endl;
		cout << "Please type (without the quotation marks) one of the following options: " << endl;
		cout << "Enter the coordinates of your next move with \"#,#\" or \"quit\" to then press enter." << endl;
		return prompt(column, row);
	}
}

// Turn will prompt the user for the beginning and ending spaces for a move.
// The prompt command will within itself control for appropriate input.  If the 
// user quits, turn will catch the throw quit_command error and return the appropriate
// turn over failure.
void NineAlmondsGame::turn()
{
	// Initial prompting - will then call transition helper method
	// so that the ending positions can always be the starting positions in
	// subsequent rounds if need be
	unsigned startCol, startRow;
	try
	{
		cout << "Select your initial piece to move!" << endl;
		prompt(startCol, startRow);
	}
	catch (result quit_command){
		throw quit_command;
	}

	// Moves will be a string that holds the path of moves
	string moves;
	stringstream sstrm;
	sstrm << moves << startCol << "," << startRow;
	moves = sstrm.str();
	return turn_transition_helper(startCol, startRow, moves);
}

// This is really the nuts and bols of the turn() method.  By using a helper method,
// it is straight-forward how the a subsequent turn's next position bounces from the previous turn's.
void NineAlmondsGame::turn_transition_helper(unsigned startCol, unsigned startRow, string moves)
{
	unsigned endCol, endRow;
	try
	{
		cout << '\n' << "Select position to move to next." << endl;
		prompt(endCol, endRow);
	}
	catch (result quit_command){
		throw quit_command;
	}

	// Check to see if there is in fact an almond in the selected position initially
	int positionStart = columns*startRow + startCol;
	int positionEnd = columns*endRow + endCol;
	if (almonds[positionStart].piece_name != "almond")
	{
		cout << '\n' << "An almond was not successfully selected - turn will restart.  Try again" << '\n' << endl;
		return turn();
	}

	// Confirm the proposed move is otherwise valid.
	// Useful messages contained within the valid_move_print function.
	if (!is_valid_move_print(startCol, startRow, endCol, endRow))
	{
		return turn_transition_helper(startCol, startRow, moves);
	}
	
	// Now that we now it is valid, we execute the move
	game_piece almond = game_piece(Brown, "almond", "A");
	game_piece empty = game_piece();
	almonds[positionEnd] = almond;
	almonds[positionStart] = empty;
	int midX = (startCol + endCol) / 2;
	int midY = (startRow + endRow) / 2;
	int midIndex = columns*midY + midX;
	almonds[midIndex] = empty;

	// Print out updated display
	NineAlmondsGame toPrint = NineAlmondsGame(almonds, columns, rows);
	cout << toPrint << endl;

	// Need to update the path of moves
	stringstream sstrm;
	sstrm << moves << " to " << endCol << "," << endRow;
	moves = sstrm.str();
	
	return turn_change_helper(endCol, endRow, moves);
}

void NineAlmondsGame::turn_change_helper(unsigned endCol, unsigned endRow, string moves)
{
	// Prints out the moves thus far
	cout << "Moves thus far: " << '\n' << moves << '\n' << endl;

	// Asks whether or not we should continue playing
	cout << "Continue to next move (Yes/No)?" << endl;

	// This is how we ascertain a valid answer
	string answer;
	getline(cin, answer);

	if (answer == "No")
	{
		cout << '\n' << "Next turn is starting (if there are possible moves)." << endl;
		return;
	}
	else if (answer == "Yes")
		return turn_transition_helper(endCol, endRow, moves);
	else
	{
		cout << '\n' << "Invalid response: type \"Yes\" or \"No\" ";
		cout << "without the quotation marks "  << endl;
		cout << "and press enter." << '\n' << endl;
		return turn_change_helper(endCol, endRow, moves);
	}
}

// This method prints the board, then runs turn repeatedly until:
// 1. Done() returns true, in which case success is returned.
// 2. Stalemate is true, in which case stalemate_failure is returned.
// or 3. The user decides to quit, in which case quit_command is returned.
int NineAlmondsGame::play()
{
	int turnCounter = 0;
	NineAlmondsGame toPlay = NineAlmondsGame(almonds, columns, rows);
	cout << toPlay << endl;

	while (!done() && !stalemate())
	{
		try
		{
			turn();
			++turnCounter;
		}
		catch (result quit_command)
		{
			cout << '\n' << "User quit!  The game was played for " << turnCounter << " turns." << endl;
			cerr << quit_command << endl;
			return quit_command;
		}
	}

	if (stalemate())
	{
		cout << "No valid moves remain!  The game ended after " << turnCounter << " turns." << endl;
		cerr << stalemate_failure << endl;
		return stalemate_failure;
	}

	if (done())
	{
		cout << "It took " << turnCounter << " turns to finish successfully." << '\n' << "Great Job!" << endl;
		return success;
	}

	return success;
}

// This is simply a method verifying a proposed move is a valid one.
// It checks the ending position is empty, the middle one is an almond, 
// and that it is at most two away.
bool NineAlmondsGame::is_valid_move_print(unsigned startCol, unsigned startRow, unsigned endCol, unsigned endRow)
{
	// Check to see if ending position selection does not already have an almond
	int positionEnd = columns*endRow + endCol;
	if (almonds[positionEnd].piece_name == "almond")
	{
		cout << '\n' << "An almond already exists at that space. Try again." << '\n' << endl;
		return false;
	}

	// Check to see that the position skipped has an almond
	int midX = (startCol + endCol) / 2;
	int midY = (startRow + endRow) / 2;
	int midIndex = columns*midY + midX;
	if (almonds[midIndex].piece_name != "almond")
	{
		cout << '\n' << "An almond was not jumped - not a valid move. Try again." << endl;
		cout << endl;
		return false;
	}

	// Check to see if a diagonal move, that it is correct
	int sx = startCol;
	int sy = startRow;
	int ex = endCol;
	int ey = endRow;
	if ((abs(sx - ex) != 0) && (abs(sy - ey) != 0))
	{
		if ((abs(sx - ex) != 2) || (abs(sy - ey) != 2))
		{
			cout << '\n' << "Incorrect diagonal move.  Check and try again." << endl;
			cout << endl;
			return false;
		}

	}

	// Check to see the position selected was at most two moves away or not adjacent
	if ((abs(sx - ex) > 2 || abs(sy - ey) > 2) || (abs(sx - ex) == 1 || abs(sy - ey) == 1))
	{
		cout << '\n' << "A space was selected more than two places away, either" << '\n';
		cout << " horizontally, vertically, or diagonally. Try again." << endl;
		cout << endl;
		return false;
	}

	return true;
}

// This is simply a method verifying a proposed move is a valid one.
// It checks the ending position is empty, the middle one is an almond, 
// and that it is at most two away.  ** does not have printouts - used in stalemate()
bool NineAlmondsGame::is_valid_move(int startCol, int startRow, int endCol, int endRow)
{
	// Check to see if starting position has almond
	int positionStart = columns*startRow + startCol;
	if (almonds[positionStart].piece_name != "almond")
	{
		return false;
	}

	// Check to see if ending position selection does not already have an almond
	int positionEnd = columns*endRow + endCol;
	if (almonds[positionEnd].piece_name == "almond")
	{
		return false;
	}

	// Check to see that the position skipped has an almond
	int midX = (startCol + endCol) / 2;
	int midY = (startRow + endRow) / 2;
	int midIndex = columns*midY + midX;
	if (almonds[midIndex].piece_name != "almond")
	{
		return false;
	}

	// Check to see if a diagonal move, that it is correct
	int sx = startCol;
	int sy = startRow;
	int ex = endCol;
	int ey = endRow;
	if ((abs(sx - ex) != 0) && (abs(sy - ey) != 0))
	{
		if (!(abs(sx - ex) == 2) || !(abs(sy - ey) == 2))
		{
			return false;
		}
	}

	// Check to see the position selected was at most two moves away or not adjacent
	if ((abs(sx - ex) > 2 || abs(sy - ey) > 2) || (abs(sx - ex) == 1 || abs(sy - ey) == 1))
	{
		return false;
	}

	return true;
}

// This is the NineAlmondsGame constructor.
// By taking in the file from the ifstream, we read the dimensions,
// then construct an appropriately sized vector, and then finally read in 
// the correct pieces.
NineAlmondsGame::NineAlmondsGame(ifstream & ifs)
: turnCounter(0)
{
	board_dimensions_read(ifs, columns, rows);

	int rowz = rows;
	int colz = columns;
	for (int i = 0; i < rowz*colz; ++i)
	{
		almonds.push_back(game_piece(No_color, "", " "));
	}
	
	game_pieces_read(ifs, almonds, columns, rows);
}

// This is another NineAlmondGame constructor;
// This one takes in as parameters its member variables
NineAlmondsGame::NineAlmondsGame(vector<game_piece> almonds, unsigned columns, unsigned rows)
: almonds(almonds), columns(columns), rows(rows), turnCounter(0) {}

// This is the default NineAlmondsGame constructor;
// It automatically constructs the base board, and needs no file.
NineAlmondsGame::NineAlmondsGame()
: rows(5), columns(5), turnCounter(0) {

	for (int i = 0; i < 25; ++i)
	{
		almonds.push_back(game_piece(No_color, "", " "));
	}

	for (int j = 6; j < 9; ++j)
	{
		almonds[j] = game_piece(Brown, "almond", "A");
	}
	for (int j = 11; j < 14; ++j)
	{
		almonds[j] = game_piece(Brown, "almond", "A");
	}
	for (int j = 16; j < 19; ++j)
	{
		almonds[j] = game_piece(Brown, "almond", "A");
	}
}