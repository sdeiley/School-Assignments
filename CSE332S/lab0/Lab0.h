/*
* Project: Lab0
* Shane Deiley
* CSE 332S
* email: shanedeiley@wustl.edu
* Date Completed: 1/29/14
*/


#include <vector>
#include <string>

using namespace std;


enum index {program_name, file_name, number_arguments}; // relevant indices for argc

enum result{success = 0, failure_to_open_file_error = -1, wrong_number_of_arguments_error = -2}; //various result enumerations for return values of functions

int file_parser(vector<string> &, char *);

// Added an integer parameter so that error enumeration can be specified for this function for particular cases
int usage_message(const string &, int c);