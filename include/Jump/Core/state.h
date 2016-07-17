//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

#ifndef _CORE_STATE_H_
#define _CORE_STATE_H_

#include "statement.h"

#include <string>
#include <vector>

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
		 * Represents a state in the Jump program that can be jumped to
		 *
		 * @author  Anshul Kharbanda
	 	 * @created 7 - 17 - 2016
		 */
		class State
		{
		private:
			/**
			 * The name of the state
			 */
			std::string m_name;

			/**
			 * Holds the statements to be executed
			 */
			std::vector<Statement*> m_statements;
		public:
			/**
			 * Creates a new State with the given name
			 *
			 * @param name the name of the state
			 */
			State(std::string name);

			/**
			 * Copy constructor for State
			 *
			 * @param other the State to copy
			 */
			State(const State& other);

			/**
			 * Destroys the State
			 */
			~State();

			/**
			 * Returns the name of the state
			 *
			 * @return the name of the state
			 */
			std::string getName();

			/**
			 * Adds the given statement to the State
			 *
			 * @param statement the statement to add
			 */
			void add(Statement* statement);

			/**
			 * Executes the State
			 * 
			 * @return reference to the next state (name of the state)
			 */
			std::string execute();
		};
	}
}

#endif