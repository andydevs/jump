//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

#ifndef _CORE_STATEMENT_TO_H_
#define _CORE_STATEMENT_TO_H_

// Headers being used
#include "statement.h"

// Libraries being used
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
	 * The core program
	 *
	 * @author  Anshul Kharbanda
	 * @created 7 - 16 - 2016
	 */
	namespace Core
	{
		/**
		 * Contains all of the Jump statements
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 17 - 2016
		 */
		namespace Statements
		{
			/**
			 * Transitions to another state
			 *
			 * @author  Anshul Kharbanda
			 * @created 7 - 17 - 2016
			 */
			class To : public Statement
			{
			private:
				/**
				 * Reference to another state (the state's name)
				 */
				std::string m_stateRef;
			public:
				/**
				 * Creates a new To with the given stateRef
				 *
				 * @param stateRef reference to another state (the state's name)
				 */
				To(std::string stateRef);

				/**
				 * Destroys the To
				 */
				~To();

				/**
				 * Returns the string representation of the Print
				 *
				 * @return the string representation of the Print
				 */ 
				std::string toString();

				/**
				 * Executes the To if the condition is true
				 *
				 * @param stateRef reference to containing state (pointer)
				 *
				 * @return reference to another state (the state's name)
				 */
				std::string conditionedExecute(State* stateRef);
			};
		}
	}
}

#endif