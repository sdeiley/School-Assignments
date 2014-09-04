/*
* Project: Lab1
* Shane Deiley
* CSE 332S
* email: shanedeiley@wustl.edu
* Date Completed: 2/12/14
*/

#include "stdafx.h"
#include "GamePieces.h"
#include "GameBoard.h"
#include "oosdlStandard.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Definition of the function that reads in board game dimensions
int board_dimensions_read(fstream & input, unsigned & width, unsigned & height)
{
	// This counter is utilized in the understanding of precisely how many extractions from
	// the string stream were successful
	unsigned extractionSuccess = 0;

	if (input.is_open())
	{
		string line;
		
		if (getline(input, line))
		{
			istringstream iss(line);
			if (iss >> width)
				++extractionSuccess;
			if (iss >> height)
				++extractionSuccess;
		}
		else
		{
			cout << "Failure to read line from input file stream" << endl;
			cerr << failure_to_get_line_from_file_stream << endl;
			return failure_to_get_line_from_file_stream;
		}
	}
	else 
	{
		cout << "Failure to open file" << endl;
		cerr << failure_to_open_file_error << endl;
		return failure_to_open_file_error;
	}

	if (extractionSuccess == 2)
		return success;
	else if (extractionSuccess == 1)
	{
		cout << "Read from lines but failed to extract board dimensions once" << endl;
		cerr << failure_to_extract_from_line << endl;
		return failure_to_extract_from_line;
	}
	else
	{
		cout << "Read from lines but failed to extract board dimensions both times" << endl;
		cerr << failure_to_extract_from_line << endl;
		return failure_to_extract_from_line;
	}
}

// Definition of the function that reads in the game pieces
int game_pieces_read(fstream & input, vector<game_piece> & positions, unsigned width, unsigned height)
{
	// This is the counter that will ascertain if any well-formed pieces were found
	unsigned successfulPieceCounter = 0;

	if (input.is_open())
	{
		string line;
		while (getline(input, line))
		{
			string color; string name;
			string representation;
			unsigned horiz = 0; unsigned vert = 0;
			istringstream iss(line);
			if (iss >> color){
				if (iss >> name){
					if (iss >> representation){
						if (iss >> horiz){
							if (iss >> vert){
								piece_color pc = string_to_piece_color(color);
								if (pc != Invalid_color){
									if (horiz < width){
										if (vert < height){
											int index = width * vert + horiz;
											game_piece gp = game_piece(pc, name, representation);
											positions[index] = gp;
											++successfulPieceCounter;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
		cout << "Unable to open input file" << endl;
		cerr << failure_to_open_file_error << endl;
		return failure_to_open_file_error;
	}

	if (successfulPieceCounter >= 1)
		return success;
	else
	{
		cout << "Failed to find any well-formed pieces" << endl;
		cerr << failure_to_find_any_pieces << endl;
		return failure_to_find_any_pieces;
	}
}

	// Prints out the game board
	int piece_print_out(const vector<game_piece> & pieces, unsigned width, unsigned height)
	{
		int size = sizeof(pieces);
		if (sizeof(pieces) > (width) * (height - 1) + (width-1))
		{
			cout << "Too many pieces for given game board dimensions" << endl;
			cerr << too_many_pieces_error << endl;
			return too_many_pieces_error;
		}
		else
		{
			for (int rowPrinting = (height-1); rowPrinting >= 0; --rowPrinting)
			{
				for (int columnPrinting = 0; columnPrinting <= (width-1); ++columnPrinting)
				{
					if (columnPrinting == (width-1))
					{
						cout << pieces[((width) * rowPrinting + columnPrinting)].representation << endl;
					}
					else
					{
						cout << pieces[((width)* rowPrinting + columnPrinting)].representation;
					}
				}
			}
			return success;
		}
	}
