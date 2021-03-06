/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Values/expression.h"
#include "Jump/Streams/printstream.h"
#include "Jump/Streams/readstream.h"
#include "Jump/jumperror.h"
#include "Jump/interpreter.h"

// Libraries being used
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

// Namespaces being used
using namespace std;
using namespace Jump;

/**
 * Returns the text read from the file of the given filename
 *
 * @param filename the name of the file to read
 *
 * @return text read from the file of the given filename
 */
string readfile(string filename);

/**
 * The main function of the program
 *
 * @param argc the number of command line arguments
 * @param argv the command line arguments
 *
 * @return exit code
 */
int main(int argc, char const *argv[])
{
	// Get filename (Return error if filename not given)
	string filename;
	if (argc > 1) filename = argv[1];
	else
	{
		cout << "ERROR: No Filename specified!" << endl;
		return 1;
	}

	// Interpret and run state machine
	int status; StateMachine* machine;
	try {
		machine = Interpreter::interpret(readfile(filename), 0);
		status = machine->execute();
	} catch (Errors::JumpError e) {
		cout << "JumpError: " << e.what() << endl;
		status = 1;
	}

	// Do afterwards
	delete machine;
	return status;
}

/**
 * Returns the text read from the file of the given filename
 *
 * @param filename the name of the file to read
 *
 * @return text read from the file of the given filename
 */
string readfile(string filename)
{
	// Read file into input
	ifstream file(filename);
	string input = ""; char c;
	while (file.get(c)) input += c;
	file.close();

	// Return input
	return input;
}
