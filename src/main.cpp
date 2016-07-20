//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Compiler/compiler.h"

// Libraries being used
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

// Namespaces being used
using namespace std;
using namespace Jump;

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
	// Read program from file
	ifstream file("example.jump");
	string input = ""; char c;
	while (file.get(c)) input += c;
	file.close();

	// Compile inout into StateMachine
	Core::StateMachine machine = Compiler::compile(input);

	// Execute the machine and return status code
	return machine.execute();
}