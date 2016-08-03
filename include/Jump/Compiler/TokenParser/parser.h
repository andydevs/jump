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
#include "Jump/Compiler/syntaxerror.h"

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
			 * The token classes to parse input with
			 */
			static TokenClass TOKEN_CLASSES[] = {
				// Words
				TokenClass("keyword", "state|print|to"),
				TokenClass("identifier", "[a-zA-Z][a-zA-Z0-9_]*"),

				// Values
				TokenClass("string", "(\"|').*?\\1"),
				TokenClass("number", "[0-9]+"),

				// Endline
				TokenClass("endline", "(#.*?)?\r?\n"),

				// Ignore whitespaces
				TokenClass("wspace", "[ \t]+", true)
			};

			/**
			 * Parses the given input into a queue of tokens tokens.
			 *
			 * @param input the input to parse from
			 *
			 * @return the Tokens parsed from the input
			 * 
			 * @throw SyntaxError if parser could not parse a particular character
			 */
			std::queue<Token> parse(std::string input) throw(Jump::Compiler::SyntaxError);
		}
	}
}

#endif