/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_ERRORS_VALUEERROR_H_
#define _CORE_ERRORS_VALUEERROR_H_

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
	 * The core program
	 *
	 * @author  Anshul Kharbanda
	 * @created 7 - 16 - 2016
	 */
	namespace Core
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
			 * Thrown upon an error with processing values
			 *
			 * @author  Anshul Kharbanda
			 * @created 7 - 27 - 2016
			 */
			class ValueError: public JumpError
			{
			public:
				/**
				 * Creates a ValueError with the given message
				 * 
				 * @param message the message of the ValueError
				 */
				using JumpError::JumpError;

				/**
				 * Returns the message of the ValueError
				 *
				 * @return the message of the ValueError
				 */
				using JumpError::what;
			};
		}
	}
}

#endif