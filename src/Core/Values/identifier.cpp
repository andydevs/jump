/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Values/identifier.h"

// Namespaces being used
using namespace std;
using namespace Jump::Core::Errors;

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
			 * Creates the Identifier with the given name
			 *
			 * @param name the name of the Identifier
			 */
			Identifier::Identifier(string name):
			Value("Identifier"),
			m_name(name)
			{}
			
			/**
			 * Copy constructor for Identifier
			 *
			 * @param other the other Identifier to copy
			 */
			Identifier::Identifier(const Identifier& other):
			Value(other),
			m_name(other.m_name)
			{}
			
			/**
			 * Destroys the Identifier
			 */
			Identifier::~Identifier() {}

			/**
			 * Returns the name of the Identifier
			 *
			 * @return the name of the Identifier
			 */
			string Identifier::name()
			{
				return m_name;
			}

			/**
			 * Returns true if the Identifier is a constant
			 *
			 * @return true if the Identifier is a constant
			 */
			bool Identifier::isConstant(State* stateRef)
			{
				return stateRef->statemachine()->constGet(m_name) != NULL;
			}

			/**
			 * Evaluates the value in the context of the given state
			 *
			 * @param stateRef a reference to the state being evaluated
			 * @param flags    flags to evauate the state with
			 *
			 * @return the evaluated value
			 */
			Value* Identifier::evaluate(State* stateRef, int flags) throw(ValueError)
			{
				// If the no evaluate identifier flag is on just return the identifier
				// Else, return evaluated identifer
				if ((flags & NO_EVALUATE_IDENTIFIER) == NO_EVALUATE_IDENTIFIER)
					return this;
				else if (isConstant(stateRef))
					return stateRef->statemachine()->constGet(m_name)->evaluate(stateRef, flags);
				else
					return stateRef->statemachine()->varGet(m_name)->evaluate(stateRef, flags);
			}

			/**
			 * The assignment operation for Jump values
			 *
			 * @param stateRef a reference to the state being assigned
			 * @param value    the value being assigned to
			 *
			 * @return the value being assigned to
			 */
			Value* Identifier::assign(State* stateRef, Value* value) throw(ValueError)
			{
				// Error if the identifier is a constant or if the variable name is not defined
				if (isConstant(stateRef))
					throw TypeError("Constant " + m_name + " cannot be reassigned.");
				else if (stateRef->statemachine()->varGet(m_name) == NULL)
					throw ValueError("Undefined variable: " + m_name);

				// Set variable
				stateRef->statemachine()->varSet(m_name, value);

				// Return value
				return value;
			}
		}
	}
}