/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/statemachine.h"

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
		 * Creates an empty StateMachine
		 */
		StateMachine::StateMachine() : m_statetable(map<string, State*>())
		{
			stateSet(new State("end"));
		}

		/**
		 * Copy constructor for StateMachine
		 *
		 * @param other the other StateMachine to copy
		 */
		StateMachine::StateMachine(const StateMachine& other) : m_statetable(other.m_statetable) {}

		/**
		 * Destroys the StateMachine
		 */
		StateMachine::~StateMachine()
		{
			// Delete all states
			for (map<string, State*>::iterator it = m_statetable.begin(); it != m_statetable.end(); ++it)
				delete it->second;
		}

		/**
		 * Returns an inspection of the StateMachine
		 *
		 * @return an inspection of the StateMachine
		 */
		string StateMachine::inspect()
		{
			string s = "[STATEMACHINE]\n";
			for (map<string, State*>::iterator it = m_statetable.begin(); it != m_statetable.end(); ++it)
				s += "\t" + it->second->inspect();
			return s;
		}

		/**
		 * Enters a State into the StateMachine
		 *
		 * @param state the State to enter
		 */
		void StateMachine::stateSet(State* state)
		{
			// Add state to statetable
			m_statetable.insert(pair<string, State*>(state->getName(), state));

			// Set this statemachine in state
			state->statemachineSet(this);
		}

		/**
		 * Gets a State from the StateMachine with the given name
		 *
		 * @param name the name of the state to retrieve
		 *
		 * @return the state represented by the name
		 */
		State* StateMachine::stateGet(std::string name)
		{
			// Find state with name
			map<string, State*>::iterator it = m_statetable.find(name);

			// Return state if found, else NULL
			return it == m_statetable.end() ? NULL : m_statetable.find(name)->second;
		}

		/**
		 * Executes the StateMachine with no flags
		 *
		 * @return exit status of the StateMachine 
		 */
		int StateMachine::execute()
		{
			return execute(0);
		}

		/**
		 * Executes the StateMachine with the given flags
		 *
		 * @param flags the flags to run the machine with
		 *
		 * @return exit status of the StateMachine 
		 */
		int StateMachine::execute(int flags)
		{
			// Get start state
			State* next = stateGet("start");

			// Return error if null found
			if (next == NULL) return 1;

			// Loop untill end state is reached
			while (next->getName() != "end")
			{
				// Get next state from execution
				next = stateGet(next->execute());

				// Return error if none found
				if (next == NULL) return 1;
			}

			// Return OK
			return 0;
		}
	}
}