/*============================================================================
Project: Lab4
File: GamePiece.cpp
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4/23/14
============================================================================*/

#include "stdafx.h"
#include "GamePiece.h"
#include "Utilities.h"


using namespace std;

/*
Default constructor of GamePiece
*/
GamePiece::GamePiece(): color_(NONE), name_(""), disp_(" ") {}

/*
The constructor of GamePiece
*/
GamePiece::GamePiece(kPieceColor color, string name, string disp):
	color_(color), name_(name), disp_(disp) {}


/*
Takes a variable of type kPieceColor and returns its literal string name.
*/
string colorEnumToString (kPieceColor color)
{
	switch(color)
	{
	case RED:
		return "red";
	case BLACK:
		return "black";
	case WHITE:
		return "white";
	case BROWN:
		return "brown";
	case NONE:
		return "none";
	default:
		return "invalid";
	}
}

/*
Takes a string and returns its corresponding variable of type kPieceColor .
*/
kPieceColor colorStringToEnum (string color)
{
	makeLower(color);
	if (color == "red")
		return RED;
	else if (color == "white")
		return WHITE;
	else if (color == "black")
		return BLACK;
	else if (color == "brown")
		return BROWN;
	else if (color == "none" || color == " ")
		return NONE;
	else
		return INVALID;
}