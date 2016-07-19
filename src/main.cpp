//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Compiler/grammarparser.h"

// Libraries being used
#include <string>
#include <queue>

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
	// Test input to parse
	std::string input = "state start\n\tprint \"Hello World\"";

	// Declare Token queue and StateMachine
	std::queue<Jump::Compiler::TokenParser::Token> tokens;
	Jump::Core::StateMachine machine;

	// Parse Tokens and StateMachine
	Jump::Compiler::TokenParser::parse(tokens, input);
	Jump::Compiler::GrammarParser::parse(machine, tokens);

	// Execute the machine and return status code
	return machine.execute();
}