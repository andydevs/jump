//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Geaders being used
#include "Jump/Core/Statements/statement.h"
#include "Jump/Core/statemachine.h"
#include "Jump/Core/state.h"

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
		start->add(new Statements::Print("Good afternoon world"));
		start->add(new Statements::Print("I am Chef Gordon Ramsay"));
		start->add(new Statements::Print("And I like cat food"));
		start->add(new Statements::To("next"));

	// Sample state
	State* next = new State("next");
		next->add(new Statements::Print("I am Dog"));
		next->add(new Statements::Print("And I also like cat food"));
		next->add(new Statements::To("final"));

	// Sample state
	State* final = new State("final");
		final->add(new Statements::Print("I am Pig"));
		final->add(new Statements::Print("I do pig stuff"));

	// Sample stateMachine
	StateMachine statemachine;
	statemachine.stateSet(start);
	statemachine.stateSet(next);
	statemachine.stateSet(final);

	// Execute
	return statemachine.execute();
}