/*============================================================================
Project: Lab4
File: GameBase.h
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4/23/14
============================================================================*/

#ifndef GAMEBASE_H
#define GAMEBASE_H
#include "GamePiece.h"
#include "Utilities.h"
#include <memory>

using namespace std;

enum badSideLengths {BAD_MAGIC_LENGTH = 2};


class GameBase {
public:
	GameBase(int, int);

	virtual bool done() = 0;

	static void instantiate(char**, int);

	virtual int play(); 

	virtual void print() = 0;

	virtual int prompt(unsigned int&, unsigned int&);

	virtual bool stalemate() = 0;

	virtual int turn() = 0;

	static shared_ptr<GameBase> instance();

	void savePrompt();

protected:
	static shared_ptr<GameBase> ptr;
	static string gameName;
	static int turns;
	int rows_;
	int cols_;
	int longestDisp_;
	vector<GamePiece> pieces;
};


#endif