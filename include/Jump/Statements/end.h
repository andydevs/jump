/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_STATEMENTS_END_H_
#define _CORE_STATEMENTS_END_H_

// Headers being used
#include "statement.h"
#include "Jump/Values/value.h"

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
			 * Transitions to the end state
			 *
			 * @author  Anshul Kharbanda
			 * @created 7 - 17 - 2016
			 */
			class End : public Statement
			{
			private:
				/**
				 * Transition condition
				 */
				Values::Value* m_condition;
			public:
				/**
				 * Creates a new End with the given condition
				 *
				 * @param condition transition condition
				 */
				End(Values::Value* condition);

				/**
				 * Destroys the End
				 */
				~End();

				/**
				 * Returns an inspection of the End
				 *
				 * @return an inspection of the End
				 */ 
				std::string inspect();

				/**
				 * Executes the End
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
}

#endif