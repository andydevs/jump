//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Compiler/TokenParser/parser.h"
#include "Jump/Compiler/syntaxerror.h"

// Libraries being used
#include <exception>

// Namespaces being used
using namespace std;
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
					for (int i = 0; i < sizeof(TOKEN_CLASSES) / sizeof(TokenClass); ++i)
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
					if (error) throw SyntaxError("Unexpected character " + input[0]);
				}

				// Return queue
				return tkq;
			}
		}
	}
}