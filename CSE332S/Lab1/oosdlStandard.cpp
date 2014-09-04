/*
* Project: Lab1
* Shane Deiley
* CSE 332S
* email: shanedeiley@wustl.edu
* Date Completed: 2/12/14
*/

#include "stdafx.h"
#include "oosdlStandard.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;

int file_parser(vector<string> &v, char * program_name, char * input_file)
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
		return usage_message(program_name, "Unable to Open File", failure_to_open_file_error);
	}
	return success;

}

// Int parameter allows this function to be used flexibly in the main for various errors,
// despite not being utilized here.
int usage_message(const string &program_name, const string &error_message, int error_specified)
{
	cout << "Usage: " << program_name;
	cout << " " << error_message << endl;

	cerr << error_specified << endl;

	return error_specified;
}

// Takes in a C++ style string and returns the lowercase form of the string
void make_lowercase(string &toLower)
{
	for (auto character = toLower.begin(); character != toLower.end(); ++character)
	{
		if (*character > 64 && *character < 91)
		{
			*character = *character + 32;
		}
	}

}