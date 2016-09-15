/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_ERRORS_SYNTAXERROR_H_
#define _CORE_ERRORS_SYNTAXERROR_H_

// Libraries being used
#include "jumperror.h"

/**
 * Jump is a new programming language that uses the state machine paradigm
 *
 * @author  Anshul Kharbanda
 * @created 7 - 15 - 2016
 */
namespace Jump
{
	/**
	 * Contains core errors
	 *
	 * @author  Anshul Kharbanda
	 * @created 7 - 27 - 2016
	 */
	namespace Errors
	{
		/**
		 * Thrown upon an error with syntax.
		 *
		 * @author  Anshul Kharbanda
		 * @created 9 - 12 - 2016
		 */
		class SyntaxError: public JumpError
		{
		public:
			/**
			 * Creates a SyntaxError with the given message
			 * 
			 * @param message the message of the SyntaxError
			 */
			using JumpError::JumpError;

			/**
			 * Returns the message of the SyntaxError
			 *
			 * @return the message of the SyntaxError
			 */
			using JumpError::what;
		};
	}
}

#endif