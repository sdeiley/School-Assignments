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


int main(int argc, char * argv[])
{
	if (argc != number_arguments)
	{
		return usage_message(argv[program_name],
			"<input file> (only one argument)", wrong_number_of_arguments_error);
	}

	fstream ifs(argv[file_name]);
	if (ifs.is_open())
	{
		unsigned width = 0; unsigned height = 0;

		// We make an int of initial result to ensure that we're testing the appropriate problem
		int result = board_dimensions_read(ifs, width, height);
		if (result == failure_to_get_line_from_file_stream)
		{
			return usage_message(argv[program_name],
				"board_dimensions_read failed to getline an appropriate set of dimensions from the start", failure_to_get_line_from_file_stream);
		}
		while (result != success)
		{
			// This if condition checks to see if we ever stop being able to getlines from file
			if (result == failure_to_get_line_from_file_stream)
			{
				return usage_message(argv[program_name],
					"board_dimensions_read failed to getline an appropriate set of dimensions", failure_to_get_line_from_file_stream);
			}

			// Update result each iteration to check until a success
			result = board_dimensions_read(ifs, width, height);
		}

		vector<game_piece> pieces;
		game_piece blank = game_piece(No_color, "", " ");
		for (unsigned i = 0; i <= width*(height-1) + (width-1); ++i)
		{
			pieces.push_back(blank);
		}

		// This confirms the game_pieces_read was a success, and if not, returns the error that occurred in usage message
		int gpResult = game_pieces_read(ifs, pieces, width, height);
		if (gpResult != success)
		{
			return usage_message(argv[program_name],
				"Failure when reading game pieces. Check number with enums for specific error.", gpResult);
		}

		// Finally, return the value (success or some failure) with the call to print out the board
		return piece_print_out(pieces, width, height);
	}
	else
	{
		return usage_message(argv[program_name],
			"The first argument, the file, did not open", failure_to_open_file_error);
	}
}

// This was the main from Lab0.. It's here for reference
/*
int main(int argc, char * argv[])
{
// This ensures the number of arguments (besides the program name) is precisely one
if (argc != number_arguments)
{
return usage_message(argv[program_name],
"<input file> (only one argument)", wrong_number_of_arguments_error);

}

// Parse the file, placing strings in the string_holder vector
vector<string> string_holder;
file_parser(string_holder, argv[program_name], argv[file_name]);

// Proceed to isolate pure integer strings
vector<int> int_vect;
for (auto string_held = string_holder.begin(); string_held != string_holder.end(); ++string_held)
{
// This boolean will be changed to false for every word in which there exists non digit characters
bool isInts = true;
for (auto character = string_held->begin(); character != string_held->end(); ++character)
{
if (!(isdigit(*character)))
{
isInts = false;
}

}

int number;
// If the boolean is false, there are letters, so it is not added to the vector of integers
if (isInts)
{
istringstream iss(*string_held);
iss >> number;
int_vect.push_back(number);
}
// Print the rest of the strings - all the strings that are not entirely digits
else
{
cout << *string_held << endl;
}
}
// Then print the numbers
for (size_t i = 0; i < int_vect.size(); ++i)
{
cout << int_vect[i] << endl;
}


return success;
}
*/