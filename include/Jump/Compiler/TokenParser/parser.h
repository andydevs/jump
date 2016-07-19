//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

#ifndef _COMPILER_TOKENPARSER_PARSER_H_
#define _COMPILER_TOKENPARSER_PARSER_H_

// Headers being used
#include "token.h"
#include "tokenclass.h"

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

				// Endline
				TokenClass("endline", "(#.*?)?\r?\n"),

				// Ignore whitespaces
				TokenClass("wspace", "[ \t]+", true)
			};

			/**
			 * Parses the given input into tokens which are pushed onto 
			 * the given queue. Returns true if parser errored
			 *
			 * @param tkq   the queue to push tokens to
			 * @param input the input to parse from
			 *
			 * @return true if parser errored
			 */
			bool parse(std::queue<Token>& tkq, std::string input);
		}
	}
}

#endif