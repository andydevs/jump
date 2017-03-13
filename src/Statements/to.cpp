/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Statements/to.h"
#include "Jump/Values/boolean.h"

// Namespaces being used
using namespace std;
using namespace Jump::Values;
using namespace Jump::Errors;

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
		 * Creates a new To with the given stateRef
		 *
		 * @param stateRef reference to another state (the state's name)
		 */
		To::To(string stateRef):
		Statement(),
		m_stateRef(stateRef),
		m_condition(new Boolean(true))
		{}

		/**
		 * Creates a new To with the given stateRef and condition
		 *
		 * @param stateRef  reference to another state (the state's name)
		 * @param condition transition condition
		 */
		To::To(std::string stateRef, Value* condition):
		Statement(),
		m_stateRef(stateRef),
		m_condition(condition)
		{}

		/**
		 * Destroys the To
		 */
		To::~To() {}

		/**
		 * Returns an inspection of the To
		 *
		 * @return an inspection of the To
		 */ 
		string To::inspect()
		{
			return "[TO " + m_stateRef + " if " + m_condition->toString() + "]";
		}

		/**
		 * Executes the To
		 *
		 * @param stateRef reference to containing state (pointer)
		 *
		 * @return reference to another state (the state's name)
		 *
		 * @throw JumpError upon an error when executing a statement
		 */
		std::string To::execute(State* stateRef) throw(JumpError)
		{
			return m_condition->evaluate(stateRef, 0)->toBool() ? m_stateRef : "";
		}
	}
}