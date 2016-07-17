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
	PrintStatement statement1("Good afternoon world");
	PrintStatement statement2("I am Chef Gordon Ramsay");
	PrintStatement statement3("And I like cat food");

	statement1.execute();
	statement2.execute();
	statement3.execute();

	return 0;
}