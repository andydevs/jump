/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Errors/jumperror.h"

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
			 * Creates a JumpError with the given message
			 * 
			 * @param message the message of the JumpError
			 */
			JumpError::JumpError(string message): m_message(message) {}

			/**
			 * Destroys the JumpError
			 */
			JumpError::~JumpError() {}

			/**
			 * Returns the message of the JumpError
			 *
			 * @return the message of the JumpError
			 */
			const char* JumpError::what() const throw()
			{
				return m_message.c_str();
			}	
		}
	}
}