/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_ERRORS_REFERENCEERROR_H_
#define _CORE_ERRORS_REFERENCEERROR_H_

// Libraries being used
#include "valueerror.h"

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
		 * Thrown upon an unavailable or invalid reference
		 *
		 * @author  Anshul Kharbanda
		 * @created 9 - 13 - 2016
		 */
		class ReferenceError: public ValueError
		{
		public:
			/**
			 * Creates a ReferenceError with the given message
			 * 
			 * @param message the message of the ReferenceError
			 */
			using ValueError::ValueError;

			/**
			 * Returns the message of the ReferenceError
			 *
			 * @return the message of the ReferenceError
			 */
			using ValueError::what;
		};
	}
}

#endif