/*============================================================================
Project: Lab4
File: ReversiGame.h
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4/23/14
============================================================================*/

#ifndef REVERSIGAME_H
#define REVERSIGAME_H

#include "GameBase.h"

using namespace std;

enum reversiGameConstants {RGROWS= 4, RGCOLS = 4, TOTAL_NUM_PIECES = 64,
						BLACK_INDEX_ONE = 27, BLACK_INDEX_TWO = 36,
						WHITE_INDEX_ONE = 28, WHITE_INDEX_TWO = 35,
						LOWER_EDGE = 0, UPPER_EDGE = 7,
						DEFAULT = 0};

const GamePiece BLACK_PIECE = GamePiece(BLACK, "Black_Piece", "X");
const GamePiece WHITE_PIECE = GamePiece(WHITE, "White_Piece", "O");

class ReversiGame: public GameBase {
	friend ostream & operator<< (ostream&, const ReversiGame&);

public:
	static string curPlrTurn;

	ReversiGame(string, string);

	virtual void print() override;

	virtual bool done();

	virtual bool stalemate();

	virtual int turn();

	bool isValidMove(GamePiece, int, unsigned, unsigned, kPieceColor, vector<int> &);

	bool movesRemain();

	bool movesRemain(string);
	
	bool boundsHelper(unsigned, unsigned, GamePiece, int);

	bool findValidNeighbor(unsigned, unsigned, unsigned, unsigned, GamePiece, int);

	bool iterateThroughNeighbor(unsigned, unsigned, GamePiece, int, int);

	bool iterateThroughNeighborReverse(unsigned, unsigned, GamePiece, int, int);

private:
	string plrOnBlack_;
	string plrOnWhite_;
	
};



ostream & operator<< (ostream&, const ReversiGame&);




#endif //REVERSIGAME_H