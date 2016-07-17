//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Core/tostatement.h"

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
		 * Creates a new ToStatement with the given stateRef
		 *
		 * @param stateRef reference to another state (the state's name)
		 */
		ToStatement::ToStatement(string stateRef) : Statement()
		{
			m_stateRef = stateRef;
		}

		/**
		 * Destroys the ToStatement
		 */
		ToStatement::~ToStatement() {}

		/**
		 * Executes the ToStatement if the condition is true
		 *
		 * @param stateRef reference to containing state (pointer)
		 *
		 * @return reference to another state (the state's name)
		 */
		std::string ToStatement::conditionedExecute(State* stateRef)
		{
			return m_stateRef;
		}
	}
}