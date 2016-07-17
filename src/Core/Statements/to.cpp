//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Core/Statements/to.h"

// Namespaces being used
using namespace std;

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
			To::To(string stateRef) : Statement(), m_stateRef(stateRef) {}

			/**
			 * Destroys the To
			 */
			To::~To() {}

			/**
			 * Executes the To if the condition is true
			 *
			 * @param stateRef reference to containing state (pointer)
			 *
			 * @return reference to another state (the state's name)
			 */
			std::string To::conditionedExecute(State* stateRef)
			{
				return m_stateRef;
			}
		}
	}
}