/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Compiler/compiler.h"
#include "Jump/Compiler/TokenParser/parser.h"
#include "Jump/Compiler/grammarparser.h"

// Namespaces being used
using namespace std;
using namespace Jump::Core;

/**
 * Jump is a new programming language that uses the state machine paradigm
 *
 * @author  Anshul Kharbanda
 * @created 7 - 15 - 2016
 */
namespace Jump
{
	/**
	 * Compiles a Jump script
	 *
	 * @author  Anshul Kharbanda
	 * @created 7 - 17 - 2016
	 */
	namespace Compiler
	{
		/**
		 * Compiles the input into a StateMachine
		 *
		 * @param input the input to compile
		 *
		 * @return the StateMachine compiled from the input
		 *
		 * @throw SyntaxError if there is an error in the syntax of the input
		 */
		StateMachine compile(string input) throw(SyntaxError)
		{
			// Parse input into Tokens
			queue<TokenParser::Token> tokens = TokenParser::parse(input);

			// Parse Tokens into a StateMachine
			StateMachine machine = GrammarParser::parse(tokens);

			// Return machine
			return machine;
		}
	}
}