/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_ERRORS_STREAMERROR_H_
#define _CORE_ERRORS_STREAMERROR_H_

// Libraries being used
#include "Jump/jumperror.h"

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
		 * Thrown upon an error when writing to or reading from streams.
		 *
		 * @author  Anshul Kharbanda
		 * @created 9 - 9 - 2016
		 */
		class StreamError: public JumpError
		{
		public:
			/**
			 * Creates a StreamError with the given message
			 * 
			 * @param message the message of the StreamError
			 */
			using JumpError::JumpError;

			/**
			 * Returns the message of the StreamError
			 *
			 * @return the message of the StreamError
			 */
			using JumpError::what;
		};
	}
}

#endif