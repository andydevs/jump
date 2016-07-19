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

#include <iostream>

// Namespaces being used
using namespace std;

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
			 * Parses the given input into tokens which are pushed onto 
			 * the given queue. Returns true if parser errored
			 *
			 * @param tkq   the queue to push tokens to
			 * @param input the input to parse from
			 *
			 * @return true if parser errored
			 */
			bool parse(queue<Token>& tkq, string input)
			{
				// Declare error and Token buffer
				bool error = false;
				Token tk;

				// Parse entire string (stop if error)
				while (!(input.empty() || error))
				{
					// Assume no token class was found (error is true)
					error = true;

					// Search token classes
					for (int i = 0; i < sizeof(TOKEN_CLASSES)/sizeof(TokenClass); ++i)
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
				}

				// Return error status
				return error;
			}
		}
	}
}