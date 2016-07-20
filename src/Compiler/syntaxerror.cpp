//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Compiler/syntaxerror.h"

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
		 * Creates a SyntaxError with the given message
		 *
		 * @param message the message of the SyntaxError
		 */
		SyntaxError::SyntaxError(std::string message) : m_message(message) {}

		/**
		 * Destroys the SyntaxError
		 */
		SyntaxError::~SyntaxError() {}

		/**
		 * Returns the message of the SyntaxError
		 * 
		 * @return the message of the SyntaxError
		 */
		const char* SyntaxError::what() const throw()
		{
			return m_message.c_str();
		}
	}
}