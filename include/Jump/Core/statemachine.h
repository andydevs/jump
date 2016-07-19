//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

#ifndef _CORE_STATEMACHINE_H_
#define _CORE_STATEMACHINE_H_

// Headers being used
#include "state.h"

// Libraries being used
#include <string>
#include <map>

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
		class StateMachine
		{
		private:
			/**
			 * Holds the states
			 */
			std::map<std::string, State*> m_statetable;
		public:
			/**
			 * Creates an empty StateMachine
			 */
			StateMachine();

			/**
			 * Copy constructor for StateMachine
			 *
			 * @param other the other StateMachine to copy
			 */
			StateMachine(const StateMachine& other);

			/**
			 * Destroys the StateMachine
			 */
			~StateMachine();

			/**
			 * Returns the string representation of the Print
			 *
			 * @return the string representation of the Print
			 */ 
			std::string toString();

			/**
			 * Returns an index of states in the StateMachine
			 *
			 * @return an index of states in the StateMachine
			 */
			std::string index();

			/**
			 * Enters a State into the StateMachine
			 *
			 * @param state the State to enter
			 */
			void stateSet(State* state);

			/**
			 * Gets a State from the StateMachine with the given name
			 *
			 * @param name the name of the state to retrieve
			 *
			 * @return the state represented by the name
			 */
			State* stateGet(std::string name);

			/**
			 * Executes the StateMachine with no flags
			 *
			 * @return exit status of the StateMachine 
			 */
			int execute();

			/**
			 * Executes the StateMachine with the given flags
			 *
			 * @param flags the flags to run the machine with
			 *
			 * @return exit status of the StateMachine 
			 */
			int execute(int flags);
		};
	}
}

#endif