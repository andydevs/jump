//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Core/statement.h"
#include "Jump/Core/printstatement.h"
#include "Jump/Core/tostatement.h"
#include "Jump/Core/state.h"

// Libraries being used
#include <iostream>

// Namespaces being used
using namespace std;
using namespace Jump::Core;

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
	State start("start");

	start.add(new PrintStatement("Good afternoon world"));
	start.add(new PrintStatement("I am Chef Gordon Ramsay"));
	start.add(new PrintStatement("And I like cat food"));
	start.add(new ToStatement("next"));
	start.add(new PrintStatement("I am Dog"));
	start.add(new PrintStatement("And I also like cat food"));

	cout << start.getName() << endl;
	cout << start.execute() << endl;

	return 0;
}