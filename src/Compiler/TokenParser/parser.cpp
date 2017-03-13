/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Compiler/TokenParser/parser.h"
#include "Jump/Values/evaluate.h"

// Libraries being used
#include <iostream>

// Namespaces being used
using namespace std;
using namespace Jump::Values;
using namespace Jump::Errors;
using namespace Jump::Compiler;

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
				TokenClass("keyword", "\\b(const|var|state|print|read|to|loop|end|if|otherwise|and|or|not|True|False)\\b"),
				TokenClass("identifier", "[a-zA-Z][a-zA-Z0-9_]*"),

				// Values
				TokenClass("string", STRING_REGEX),
				TokenClass("number", NUMBER_REGEX),

				// Operations
				TokenClass("operation", "[\\*\\+-/%=!><]+"),
				TokenClass("lparen",    "\\("),
				TokenClass("rparen",    "\\)"),

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
			queue<Token> parse(string input) throw(SyntaxError)
			{
				// Declare token queue and buffer
				queue<Token> tkq;
				Token tk;

				// Initialize error
				bool error = false;

				// Parse entire string (stop if error)
				while (!(input.empty() || error))
				{
					// Assume token is not found (error is true)
					error = true;

					// Search token classes
					for (unsigned i = 0; i < sizeof(TOKEN_CLASSES) / sizeof(TokenClass); ++i)
					{
						// If one matches input
						if (TOKEN_CLASSES[i].hasToken(input))
						{
							// Error is false (token is found)
							error = false;

							// Add token unless ignore
							tk = TOKEN_CLASSES[i].token(input);
							if (!TOKEN_CLASSES[i].ignore()) tkq.push(tk);

							// Break search
							break;
						}
					}

					// Throw SyntaxError if error
					if (error) throw SyntaxError("Unexpected character: \"" + input.substr(0, 1) + "\"");
				}

				// Add EOF Token
				tkq.push(Token("EOF", "EOF"));

				// Return queue
				return tkq;
			}
		}
	}
}