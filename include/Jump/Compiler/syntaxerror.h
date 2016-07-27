/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _COMPILER_SYNTAXERROR_H_
#define _COMPILER_SYNTAXERROR_H_

// Libraries being used
#include <exception>
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
		 * Thrown when the TokenParser or GrammarParser fails
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 19 - 2016
		 */
		class SyntaxError
		{
		private:
			/**
			 * The message of the SyntaxError
			 */
			std::string m_message;
		public:
			/**
			 * Creates a SyntaxError with the given message
			 *
			 * @param message the message of the SyntaxError
			 */
			SyntaxError(std::string message);

			/**
			 * Destroys the SyntaxError
			 */
			~SyntaxError();

			/**
			 * Returns the message of the SyntaxError
			 * 
			 * @return the message of the SyntaxError
			 */
			const char* what() const throw();
		};
	}
}

#endif