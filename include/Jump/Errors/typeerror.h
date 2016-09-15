/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_ERRORS_TYPEERROR_H_
#define _CORE_ERRORS_TYPEERROR_H_

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
		 * Thrown upon an error with invalid types
		 * in an operation
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 27 - 2016
		 */
		class TypeError: public ValueError
		{
		public:
			/**
			 * Creates a TypeError with the given message
			 * 
			 * @param message the message of the TypeError
			 */
			using ValueError::ValueError;

			/**
			 * Returns the message of the TypeError
			 *
			 * @return the message of the TypeError
			 */
			using ValueError::what;
		};
	}
}

#endif