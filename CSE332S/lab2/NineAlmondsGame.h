/*
* Project: Lab2
* Shane Deiley
* CSE 332S
* email: shanedeiley@wustl.edu
* Date Completed: 2/26/14
*/

#ifndef NINEALMONDSGAME_H
#define NINEALMONDSGAME_H

#include "GameBoard.h"
#include "GamePieces.h"
#include "oosdlStandard.h"
#include <iostream>

// This is the NineAlmondsGame Class
class NineAlmondsGame {

	// We make this ostream operator a friend so that it can change and access the private member variables
	friend ostream & operator<< (ostream &, const NineAlmondsGame &);
public:
	// Constructors:
	// First is default, used in main. Second takes in ifstream, used for testing.
	// Third is used for in method uses of NineAlmondsGames. 
	NineAlmondsGame();
	NineAlmondsGame(ifstream &);
	NineAlmondsGame(vector<game_piece>, unsigned, unsigned);

	// This is the done() method as specified - description in source file
	bool done();

	// This is the stalemate method as specified - description in source file
	bool stalemate();

	// This is the prompt method as specified - description in source file
	void prompt(unsigned &, unsigned &);

	// This is the turn method as specified - description in source file
	void turn();

	// This is a helper method for turn() that helps
	// a subsequent turns input use the previous turn's result
	void turn_transition_helper(unsigned, unsigned, string);

	// This is a helper method for turn() that prompts the user
	// for an answer to take another turn
	void turn_change_helper(unsigned, unsigned, string);

	// This is a helper that returns true if the proposed move is valid w/ helpful printouts
	bool is_valid_move_print(unsigned, unsigned, unsigned, unsigned);

	// This is a helper that returns true if the proposed move is valid w/o printouts
	bool is_valid_move(int, int, int, int);

	// This is the play method as specified - description in source file
	int play();

private:
	// These are the private member variables for a NineAlmondsGame object
	// They are all assigned value by reading in from a input file stream
	vector<game_piece> almonds;
	unsigned rows;
	unsigned columns;
};

// This is the ostream operator for a NineAlmondsGame -  - description in source file
ostream & operator<< (ostream &, const NineAlmondsGame &);

#endif