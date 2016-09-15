/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_STATEMENT_STATEMENT_H_
#define _CORE_STATEMENT_STATEMENT_H_

// Headers being used
#include "Jump/Errors/jumperror.h"

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
		 * Represents a state in the Jump program that can be jumped to
		 *
		 * @author  Anshul Kharbanda
	 	 * @created 7 - 17 - 2016
		 */
		class State;

		/**
		 * Contains all of the Jump statements
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 17 - 2016
		 */
		namespace Statements
		{
			/**
			 * A single statement in the Jump program
			 *
			 * @author  Anshul Kharbanda
			 * @created 7 - 16 - 2016
			 */
			class Statement
			{
			public:
				/**
				 * Creates an empty Statement
				 */
				Statement();

				/**
				 * Copy constructor
				 *
				 * @param other the Statement to copy
				 */
				Statement(const Statement& other);

				/**
				 * Destroys the Statement
				 */
				virtual ~Statement();

				/**
				 * Returns an inspection of the Statement
				 *
				 * @return an inspection of the Statement
				 */ 
				virtual std::string inspect() = 0;

				/**
				 * Executes the statement
				 *
				 * @param stateRef reference to the containing state (pointer)
				 * 
				 * @return a reference to the next state (the state's name)
				 *
				 * @throw JumpError upon an error when executing a statement
				 */
				virtual std::string execute(State* stateRef) throw(Errors::JumpError) = 0;
			};
		}
	}
}

#endif