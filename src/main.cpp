//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Compiler/TokenParser/parser.h"

// Libraries being used
#include <string>
#include <queue>

// Namespaces being used
using namespace std;
using namespace Jump::Compiler::TokenParser;

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
	// Test Input
	string input = "state start\n\tprint \"Hello World\"";

	// Parse input
	queue<Token> tks;
	bool error = parse(tks, input);

	// Print tokens
	while (!tks.empty())
	{
		cout << tks.front() << endl;
		tks.pop();
	}

	// Return
	return error;
}