//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Statement headers being used
#include "Jump/Core/statement.h"
#include "Jump/Core/printstatement.h"
#include "Jump/Core/tostatement.h"

// State headers being used
#include "Jump/Core/state.h"
#include "Jump/Core/statemachine.h"

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
	// Sample start state
	State* start = new State("start");
		start->add(new PrintStatement("Good afternoon world"));
		start->add(new PrintStatement("I am Chef Gordon Ramsay"));
		start->add(new PrintStatement("And I like cat food"));
		start->add(new ToStatement("next"));

	// Sample state
	State* next = new State("next");
		next->add(new PrintStatement("I am Dog"));
		next->add(new PrintStatement("And I also like cat food"));
		next->add(new ToStatement("final"));

	// Sample state
	State* final = new State("final");
		final->add(new PrintStatement("I am Pig"));
		final->add(new PrintStatement("I do pig stuff"));

	// Sample stateMachine
	StateMachine statemachine;
	statemachine.stateSet(start);
	statemachine.stateSet(next);
	statemachine.stateSet(final);

	// Execute
	return statemachine.execute();
}