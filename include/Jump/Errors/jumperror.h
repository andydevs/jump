/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_ERRORS_JUMPERROR_H_
#define _CORE_ERRORS_JUMPERROR_H_

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
		class JumpError: public std::exception
		{
		protected:
			/**
			 * The message of the JumpError
			 */
			std::string m_message;
		public:
			/**
			 * Creates a JumpError with the given message
			 * 
			 * @param message the message of the JumpError
			 */
			JumpError(std::string message);

			/**
			 * Destroys the JumpError
			 */
			~JumpError();

			/**
			 * Returns the message of the JumpError
			 *
			 * @return the message of the JumpError
			 */
			const char* what() const throw();
		};
	}
}
#endif