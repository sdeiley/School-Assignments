/*============================================================================
Project: Lab4
File: MagicSquare.h
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4/23/14
============================================================================*/

#ifndef MAGICSQUARE_H
#define MAGICSQUARE_H

#include "GameBase.h"

using namespace std;

//CONSTANTS
enum magicSquareConstants {MAGICROWS = 4, MAGICCOLS = 4};

const string MAGIC_EMPTY_DISPLAY = " ";


class MagicSquare: public GameBase
{
	friend ostream & operator<< (ostream&, const MagicSquare&);

public:
	MagicSquare();

	virtual void print();

	virtual bool done();

	virtual bool stalemate();

	virtual void prompt(unsigned&);

	virtual int turn();

private:
	vector<int> numbers;

};

void printAvailable(vector<int>);

int strToNum(string);

string numToStr(int);

ostream & operator<< (ostream&, const MagicSquare&);

bool containsPiece(GamePiece);

string numToString(unsigned);

#endif