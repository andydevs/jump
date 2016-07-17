//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Core/statement.h"

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
		 * Creates an empty Statement
		 */
		Statement::Statement()
		{
			m_condition = true;
		}

		/**
		 * Creates a Statement with the given condition
		 *
		 * @param condition the condition being checked
		 */
		Statement::Statement(bool condition)
		{
			m_condition = condition;
		}

		/**
		 * Copy constructor
		 *
		 * @param other the Statement to copy
		 */
		Statement::Statement(const Statement& other)
		{
			m_condition = other.m_condition;
		}

		/**
		 * Destroys the Statement
		 */
		Statement::~Statement() {}

		/**
		 * Executes the Statement
		 *
		 * @return a reference to the next state (the state's name)
		 */
		 std::string Statement::execute()
		 {
		 	return m_condition ? conditionedExecute() : "";
		 }
	}
}