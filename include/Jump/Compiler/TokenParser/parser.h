/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _COMPILER_TOKENPARSER_PARSER_H_
#define _COMPILER_TOKENPARSER_PARSER_H_

// Headers being used
#include "token.h"
#include "tokenclass.h"
#include "Jump/Errors/syntaxerror.h"

// Libraries being used
#include <queue>
#include <string>

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
		 * Parses tokens
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 17 - 2016
		 */
		namespace TokenParser
		{
			/**
			 * Parses the given input into a queue of tokens tokens.
			 *
			 * @param input the input to parse from
			 *
			 * @return the Tokens parsed from the input
			 * 
			 * @throw SyntaxError if parser could not parse a particular character
			 */
			std::queue<Token> parse(std::string input) throw(Errors::SyntaxError);
		}
	}
}

#endif