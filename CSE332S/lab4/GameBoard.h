/*============================================================================
Project: Lab4
File: GameBoard.h
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4/23/14
============================================================================*/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "GamePiece.h"
#include <fstream>
#include <vector>


using namespace std;

//FUNCTIONS//
int readDimensions (ifstream &, unsigned int &, unsigned int &);
int readPieces (ifstream &, vector<GamePiece> &, unsigned int, unsigned int);
ostream& printPieces (ostream&, int, const vector<GamePiece> &, unsigned int, unsigned int);
int adjacentPieces (const vector<GamePiece> &, unsigned int, unsigned int);


#endif