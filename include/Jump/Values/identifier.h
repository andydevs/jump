/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_VALUES_IDENTIFIER_H_
#define _CORE_VALUES_IDENTIFIER_H_

// Headers being used
#include "Jump/Errors/valueerror.h"
#include "Jump/statemachine.h"
#include "Jump/state.h"
#include "value.h"

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
		 * Contains the value types for Jump
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 27 - 2016
		 */
		namespace Values
		{
			/**
			 * Represents a reference to a value stored with a given name
			 *
			 * @author  Anshul Kharbanda
			 * @created 9 - 6 - 2016
			 */
			class Identifier : public Value
			{
			private:
				/**
				 * The name of the Identifier
				 */
				std::string m_name;
			public:
				/**
				 * Creates the Identifier with the given name
				 *
				 * @param name the name of the Identifier
				 */
				Identifier(std::string name);

				/**
				 * Copy constructor for Identifier
				 *
				 * @param other the other Identifier to copy
				 */
				Identifier(const Identifier& other);

				/**
				 * Destroys the Identifier
				 */
				~Identifier();

				/**
				 * Returns the string representation of the Identifier
				 *
				 * @return the string representation of the Identifier
				 */
				std::string toString();

				/**
				 * Returns the name of the Identifier
				 *
				 * @return the name of the Identifier
				 */
				std::string name();

				/**
				 * Evaluates the value in the context of the given state
				 *
				 * @param stateRef a reference to the state being executed
				 * @param flags    flags to evauate the state with
				 *
				 * @return the evaluated value
				 */
				Value* evaluate(State* stateRef, int flags) throw(Errors::ValueError);

				/**
				 * The assignment operation for Jump values
				 *
				 * @param stateRef a reference to the state being assigned
				 * @param value    the value being assigned to
				 *
				 * @return the value being assigned to
				 */
				Value* assign(State* stateRef, Value* value) throw(Errors::ValueError);
			};
		}
	}
}

#endif