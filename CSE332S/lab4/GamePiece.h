/*============================================================================
Project: Lab4
File: GamePiece.h
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4/23/14
============================================================================*/

#ifndef GAMEPIECE_H
#define GAMEPIECE_H
#include <string>

using namespace std;

//VARIABLES//
enum kPieceColor {RED, BLACK, WHITE, BROWN, NONE, INVALID};	//possible GamePiece colors

//FUNCTIONS//
string colorEnumToString (kPieceColor);
kPieceColor colorStringToEnum (string);

//STRUCTS//
struct GamePiece{
	GamePiece();
	GamePiece(kPieceColor color, string name, string disp);
	kPieceColor color_;
	string name_;
	string disp_;
};

#endif