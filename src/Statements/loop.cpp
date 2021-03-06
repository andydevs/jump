/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/state.h"
#include "Jump/Statements/loop.h"
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
		 * Creates a new Loop with the given stateRef and condition
		 *
		 * @param condition transition condition
		 */
		Loop::Loop(Value* condition):
		Statement(),
		m_condition(condition)
		{}

		/**
		 * Destroys the Loop
		 */
		Loop::~Loop() {}

		/**
		 * Returns an inspection of the Loop
		 *
		 * @return an inspection of the Loop
		 */ 
		string Loop::inspect()
		{
			return "[LOOP if " + m_condition->toString() + "]";
		}

		/**
		 * Executes the Loop
		 *
		 * @param stateRef reference to containing state (pointer)
		 *
		 * @return reference to another state (the state's name)
		 *
		 * @throw JumpError upon an error when executing a statement
		 */
		string Loop::execute(State* stateRef) throw(JumpError)
		{
			return m_condition->evaluate(stateRef, 0)->toBool() ? stateRef->getName() : "";
		}
	}
}