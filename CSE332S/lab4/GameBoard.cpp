/*============================================================================
Project: Lab4
File: GameBoard.cpp
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4/23/14
============================================================================*/

#include "stdafx.h"
#include "GameBoard.h"
#include "Utilities.h"
#include <sstream>
#include <iostream>
#include <iomanip>

/*
Prints out the game pieces on the board.
*/
ostream& printPieces (ostream& o, int spacing, const vector<GamePiece> & pieces, unsigned int width, unsigned int height)
{
	unsigned int index;
	ostringstream board_display;
	board_display << left;
	if (pieces.size() == width*height){   //check for proper GamePiece vector size.
		for (unsigned int i = height; i > 0; --i)	//unsigned int i set up such that it never goes below zero.
		{
			board_display << i-1; //vertical indices
			for (unsigned int j = 0; j < width; ++j)
			{
				index = (width * (i-1)) + j;
				if (!pieces[index].disp_.empty())
				{
					board_display.width(spacing + 2);
					board_display << pieces[index].disp_; //add GamePiece display to output string.
					
				}
				else
				{
					throw GAMEPIECE_MISSING_OR_INVALID;	
				}
			}
			board_display << '\n';
			
		}
		board_display << " ";
		for (unsigned int k = 0; k < width; ++k)
		{
			board_display.width(spacing + 2);
			board_display<< k;
		}
		o << board_display.str() << endl;	//print board.
		return o;
	}
	else
	{
		throw WRONG_SIZE_GAMEPIECE_VECTOR;
	}
}

/*
Prints out the locations of the game pieces and lists their neighboring pieces.
*/
int adjacentPieces (const vector<GamePiece> & pieces, unsigned int width, unsigned int height)
{
	unsigned int index;
	ostringstream neighbors;
	if (pieces.size() == width*height)
	{
		for (unsigned int i = 0; i <height; ++ i)	
		{
			for (unsigned int j = 0; j < width; ++j)
			{
				index = (width *i) + j;
				if (pieces[index].color_ != INVALID)	//ensure valid piece
				{
					if(pieces[index].color_ != NONE)  //only print squares with pieces on them.
					{
						neighbors << j << "," << i << " ";
						neighbors << colorEnumToString(pieces[index].color_) << " " << pieces[index].name_ << ": ";
						unsigned int low_y, up_y, low_x, up_x;

						//determine bounds around square. (check boundary conditions).
						if (i == 0)
						{
							low_y = i;
							up_y = i + 1;
						}
						else if (i == height-1)
						{
							up_y = i;
							low_y = i - 1;
						}
						else{
							up_y = i + 1;
							low_y = i - 1;
						}
						if (j == 0)
						{
							low_x = j;
							up_x = j + 1;
						}
						else if (j == width-1)
						{
							up_x = j;
							low_x = j - 1;
						}
						else{
							up_x = j + 1;
							low_x = j - 1;
						}
						//check neighbors
						for (unsigned int k = low_y; k <= up_y; ++k)
						{
							for(unsigned int l = low_x; l <= up_x; ++ l)
							{
								unsigned int neighbor_index = (width * k) + l;
								if (pieces[neighbor_index].color_ != INVALID)
								{
									if (pieces[neighbor_index].color_ != NONE)
									{
										if (k==i && l==j)
										{} //do not list current square as neighbor.
										else
										{
											neighbors << l << "," << k << " ";
											neighbors << colorEnumToString(pieces[neighbor_index].color_) << " " << pieces[neighbor_index].name_ << "; ";
										}
									}
								}
								else
								{
									return GAMEPIECE_MISSING_OR_INVALID;
								}
							}
						}
						neighbors << '\n';
					}
				}
				else
				{
					return GAMEPIECE_MISSING_OR_INVALID;
				}
			}
		}
		cout << neighbors.str() << endl;
		return SUCCESS;
	}
	else
	{
		return WRONG_SIZE_GAMEPIECE_VECTOR;
	}
}

