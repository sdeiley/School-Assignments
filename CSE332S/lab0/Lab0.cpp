/*
* Project: Lab0
* Shane Deiley
* CSE 332S
* email: shanedeiley@wustl.edu
* Date Completed: 1/29/14
*/

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Lab0.h"

using namespace std;

int main(int argc, char * argv[])
{
	// This ensures the number of arguments (besides the program name) is precisely one
	if (argc != number_arguments)
	{
		return usage_message(argv[program_name], wrong_number_of_arguments_error);

	}

	// Parse the file, placing strings in the string_holder vector
	vector<string> string_holder;
	file_parser(string_holder, argv[file_name]);

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

int file_parser(vector<string> &v, char * input_file)
{
	ifstream ifs(input_file);

	if (ifs.is_open())
	{
		string file_line, line_word;

		while (getline(ifs, file_line))
		{
			istringstream iss(file_line);

			while (iss >> line_word)
			{
				v.push_back(line_word);
			}

		}

	} 
	
	else
	{
		cout << "Unable to open file" << endl;

		cerr << failure_to_open_file_error << endl;

	}
	return success;

}

// Int parameter allows this function to be used flexibly in the main for various errors,
// despite not being utilized here.
int usage_message(const string &program_name, int error_specified)
{
	cout << "Usage: Lab0 <input_file_name>" << endl;

	cerr << error_specified << endl;

	return error_specified;
}