/*
* Project: Lab1
* Shane Deiley
* CSE 332S
* email: shanedeiley@wustl.edu
* Date Completed: 2/12/14
*/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "GamePieces.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

// Reads the board dimensions from the first line of the input file parameter
int board_dimensions_read(fstream &, unsigned &, unsigned &);

// Reads the game pieces from the lines after the first line of the input file
int game_pieces_read(fstream &, vector<game_piece> &, unsigned , unsigned );

// Prints out the pieces on the game board
int piece_print_out(const vector<game_piece> &, unsigned, unsigned);

#endif