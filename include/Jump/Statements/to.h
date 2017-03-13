/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_STATEMENT_TO_H_
#define _CORE_STATEMENT_TO_H_

// Headers being used
#include "Jump/statement.h"
#include "Jump/value.h"

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

			/**
			 * Transition condition
			 */
			Values::Value* m_condition;
		public:
			/**
			 * Creates a new To with the given stateRef
			 *
			 * @param stateRef reference to another state (the state's name)
			 */
			To(std::string stateRef);

			/**
			 * Creates a new To with the given stateRef and condition
			 *
			 * @param stateRef  reference to another state (the state's name)
			 * @param condition transition condition
			 */
			To(std::string stateRef, Values::Value* condition);

			/**
			 * Destroys the To
			 */
			~To();

			/**
			 * Returns an inspection of the To
			 *
			 * @return an inspection of the To
			 */ 
			std::string inspect();

			/**
			 * Executes the To
			 *
			 * @param stateRef reference to containing state (pointer)
			 *
			 * @return reference to another state (the state's name)
			 *
			 * @throw JumpError upon an error when executing a statement
			 */
			std::string execute(State* stateRef) throw(Errors::JumpError);
		};
	}
}

#endif