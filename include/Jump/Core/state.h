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

// Headers being used
#include "Statements/statement.h"

// Libaries being used
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
		 * Represents a Jump StateMachine
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 17 - 2016
		 */
		class StateMachine;

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
			 * The statemachine of the state
			 */
			StateMachine* m_machine;

			/**
			 * Holds the statements to be executed
			 */
			std::vector<Statements::Statement*> m_statements;
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
			 * Returns the string representation of the Print
			 *
			 * @return the string representation of the Print
			 */ 
			std::string toString();

			/**
			 * Returns an index of the statements in the State
			 *
			 * @return an index of the statements in the State
			 */
			std::string index();

			/**
			 * Sets the StateMachine of the state
			 *
			 * @param machine the StateMachine to set
			 */
			void statemachineSet(StateMachine* machine);

			/**
			 * Adds the given statement to the State
			 *
			 * @param statement the statement to add
			 */
			void add(Statements::Statement* statement);

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