//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Compiler/TokenParser/tokenclass.h"

// Libraries being used
#include <string>
#include <vector>

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
	// TokenClasses array
	TokenClass klasses[] = {
		TokenClass("keyword", "print"),
		TokenClass("identifier", "[a-zA-Z][a-zA-Z0-9_]*"),
		TokenClass("string", "(\"|').*?\\1"),
		TokenClass("wspace", "\\s+")
	};

	// Length of TokenClass array
	int length = sizeof(klasses)/sizeof(TokenClass);

	// Test Input
	string input = "Hello_World8 \"I will help\" print 'I will help too' \"I will help three\"";
	

	// ----------------------------- Test TokenParser -----------------------------

	int location = 0;
	int error = 0;
	while (location < input.length() && !error)
	{
		error = 1;
		for (int i = 0; i < length; i++)
		{
			if (klasses[i].hasToken(input, location))
			{
				error = 0;
				cout << klasses[i].token(input, location) << endl;
				break;
			}
		}
	}

	// Error handling
	if (error) cout << "There was an error: " << input.substr(location) << endl;

	// ----------------------------------------------------------------------------

	// Return
	return error;
}