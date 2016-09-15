/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/state.h"
#include "Jump/Statements/end.h"
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
		 * Creates a new End with the given stateRef and condition
		 *
		 * @param condition transition condition
		 */
		End::End(Value* condition):
		Statement(),
		m_condition(condition)
		{}

		/**
		 * Destroys the End
		 */
		End::~End() {}

		/**
		 * Returns an inspection of the End
		 *
		 * @return an inspection of the End
		 */ 
		string End::inspect()
		{
			return "[END if " + m_condition->toString() + "]";
		}

		/**
		 * Executes the End
		 *
		 * @param stateRef reference to containing state (pointer)
		 *
		 * @return reference to another state (the state's name)
		 *
		 * @throw JumpError upon an error when executing a statement
		 */
		string End::execute(State* stateRef) throw(JumpError)
		{
			return m_condition->evaluate(stateRef, 0)->toBool() ? "end" : "";
		}
	}
}