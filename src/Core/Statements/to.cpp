/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Statements/to.h"
#include "Jump/Core/Values/boolean.h"

// Namespaces being used
using namespace std;
using namespace Jump::Core::Values;
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
				return "[TO " + m_stateRef + "]";
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
}