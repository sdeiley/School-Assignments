/*============================================================================
Project: Lab4
File: Utilities.cpp
Author: Steven Bosch, Shane Deiley
Email: s.bosch@wustl.edu, shanedeiley@wustl.edu
Last Edit: 4-23-14
============================================================================*/

#include "stdafx.h"
#include "Utilities.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

/*
Attempts to open the file designated by file_name, parse all the strings in the file
and store them in the vector<string> designated by text.
*/
int parser(vector<string> & text, char * file_name)
{
	ifstream ifs (file_name);
	if (ifs.is_open())				//return error if file cannot be found or opened.
	{
		string word;
		while(ifs >> word)
		{
			if (!word.empty())
			{
				text.push_back(word);	//add string to vector if not empty.
			}
		}
		ifs.close();
		return SUCCESS;
	}
	else
	{
		cerr << "File is missing or invalid." << endl;
		return CANNOT_OPEN_FILE;
	}
}

/*
Prints useful message about encountered errors.
*/
int usefulMsg (const string &file_name, const string &error_msg, int ERROR_NUM)
{
	cerr << file_name << ": " << error_msg << endl;
	return ERROR_NUM;
}

/*
Modifies a string so that all letters are lowercase.
*/
void makeLower(string &input)
{
	for (char letter: input)
	{
		if (isupper(letter))
		{
			letter = tolower(letter);
		}
	}
}