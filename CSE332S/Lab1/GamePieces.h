/*
* Project: Lab1
* Shane Deiley
* CSE 332S
* email: shanedeiley@wustl.edu
* Date Completed: 2/12/14
*/

#ifndef GAMEPIECES_H
#define GAMEPIECES_H

#include <string>
using namespace std;


enum piece_color { No_color, Invalid_color, Red, Black, White};

// Required method: takes piece_color, returns string.
string piece_color_toString(piece_color);

// Required method: takes string, returns piece_color.
piece_color string_to_piece_color(string &);

struct game_piece {
	piece_color colored;
	string piece_name;
	string representation;

	game_piece();
	game_piece(piece_color, string , string );
};

#endif