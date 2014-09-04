/*
* Project: Lab2
* Shane Deiley
* CSE 332S
* email: shanedeiley@wustl.edu
* Date Completed: 2/26/14
*/

#ifndef OOSDLSTANDARD_H
#define OOSDLSTANDARD_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;


enum index { program_name, file_name, number_arguments }; // relevant indices for argc

enum result {
	success = 0,
	failure_to_open_file_error = -1,
	wrong_number_of_arguments_error = -2,
	failure_to_get_line_from_file_stream = -3,
	failure_to_extract_from_line = -4,
	failure_to_find_any_pieces = -5,
	too_many_pieces_error = -6,
	quit_command = -7,
	turn_over = -8,
	stalemate_failure = -9,
	not_NineAlmonds_error = -10
}; //various result enumerations for return values of functions

int file_parser(vector<string> &, char *);

// Added an integer parameter so that error enumeration can be specified for this function for particular cases
int usage_message(const string &, const string &, int c);

void make_lowercase(string &);

#endif