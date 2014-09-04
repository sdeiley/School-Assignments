/*============================================================================
Project: Lab4
File: NineAlmonds.h
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4/23/14
============================================================================*/

#ifndef NINEALMONDS_H
#define NINEALMONDS_H

#include "GameBase.h"

using namespace std;

//CONSTANTS
enum nineAlmondsConstants {ALMONDROWS = 5, ALMONDCOLS = 5, CENTER_X = 2, CENTER_Y = 2};

const string ALMOND_DISPLAY = "A";
const string ALMOND_EMPTY_DISPLAY = " ";

//CLASSES

class NineAlmonds: public GameBase{
	friend ostream & operator<< (ostream&, const NineAlmonds&);

public:
	NineAlmonds();

	virtual void print() override;

	virtual bool done();

	int isValidMove(int&, int&, int&, int&);

	virtual bool stalemate();

	virtual int turn();

};

//FUNCTIONS

ostream & operator<< (ostream&, const NineAlmonds&);

bool isAlmond(const GamePiece &);

bool isCoordsSet(unsigned int beg_x = 0, unsigned int beg_y = 0, unsigned int end_x = 0, unsigned int end_y = 0);

bool isEmpty(const GamePiece &);

bool promptYesNo();

int resetCoords(unsigned int&, unsigned int&, unsigned int&, unsigned int&);



#endif