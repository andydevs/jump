/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Errors/typeerror.h"

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
			 * Creates a TypeError with the given message
			 * 
			 * @param message the message of the TypeError
			 */
			TypeError::TypeError(string message) : m_message(message) {}

			/**
			 * Destroys the TypeError
			 */
			TypeError::~TypeError() {}

			/**
			 * Returns the message of the TypeError
			 *
			 * @return the message of the TypeError
			 */
			const char* TypeError::what() const throw()
			{
				return m_message.c_str();
			}	
		}
	}
}