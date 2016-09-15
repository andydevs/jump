/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Values/identifier.h"
#include "Jump/Errors/referenceerror.h"

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
			 * Returns the string representation of the Identifier
			 *
			 * @return the string representation of the Identifier
			 */
			string Identifier::toString()
			{
				return m_name;
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
				{
					return this;
				}
				else
				{
					try
					{
						return stateRef->statemachine()->constGet(m_name)->evaluate(stateRef, flags);
					}
					catch(ReferenceError& e)
					{
						return stateRef->statemachine()->varGet(m_name)->evaluate(stateRef, flags);
					}
				}
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
				// Check if variable exists
				stateRef->statemachine()->varGet(m_name);

				// Set variable
				stateRef->statemachine()->varSet(m_name, value);

				// Return value
				return value;
			}
		}
	}
}