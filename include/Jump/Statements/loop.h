/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_STATEMENTS_LOOP_H_
#define _CORE_STATEMENTS_LOOP_H_

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
		 * Transitions to back to the beginning of the state
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 17 - 2016
		 */
		class Loop : public Statement
		{
		private:
			/**
			 * Transition condition
			 */
			Values::Value* m_condition;
		public:
			/**
			 * Creates a new Loop with the given condition
			 *
			 * @param condition transition condition
			 */
			Loop(Values::Value* condition);

			/**
			 * Destroys the Loop
			 */
			~Loop();

			/**
			 * Returns an inspection of the Loop
			 *
			 * @return an inspection of the Loop
			 */ 
			std::string inspect();

			/**
			 * Executes the Loop
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