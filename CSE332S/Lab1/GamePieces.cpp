/*
* Project: Lab1
* Shane Deiley
* CSE 332S
* email: shanedeiley@wustl.edu
* Date Completed: 2/12/14
*/

#include "stdafx.h"
#include "GamePieces.h"
#include "oosdlStandard.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;


string piece_color_toString(piece_color color)
{
	switch (color)
	{
		case No_color:
			return "no color";
		case Red:
			return "red";
		case Black:
			return "black";
		case White:
			return "white";
		default:
			return "invalid color";
	}

}

piece_color string_to_piece_color(string &color)
{
	make_lowercase(color);
	if (color == "red") return Red;
	else if (color == "white") return White;
	else if (color == "black") return Black;
	else if (color == ""
		  || color == " "
		  || color == "no color"
		  || color == "	") return No_color;
	else return Invalid_color;
}

game_piece::game_piece()
: colored(No_color), piece_name("Default piece"), representation("Default display") {}

game_piece::game_piece(piece_color color, string name, string representation)
: colored(color), piece_name(name), representation(representation) {}


