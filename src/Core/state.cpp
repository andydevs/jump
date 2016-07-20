//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

#include "Jump/Core/state.h"

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
		 * Creates a new State with the given name
		 *
		 * @param name the name of the state
		 */
		State::State(string name) : m_name(name), m_statements(vector<Statements::Statement*>()) {}

		/**
		 * Copy constructor for State
		 *
		 * @param other the State to copy
		 */
		State::State(const State& other) : m_name(other.m_name), m_statements(other.m_statements) {}

		/**
		 * Destroys the State
		 */
		State::~State() 
		{
			// Delete all statements
			for (unsigned i = 0; i < m_statements.size(); ++i)
				delete m_statements[i];
		}

		/**
		 * Returns the name of the state
		 *
		 * @return the name of the state
		 */
		string State::getName()
		{
			return m_name;
		}

		/**
		 * Returns the string representation of the Print
		 *
		 * @return the string representation of the Print
		 */ 
		string State::toString()
		{
			return "[STATE " + m_name + "]";
		}

		/**
		 * Returns an index of the statements in the State
		 *
		 * @return an index of the statements in the State
		 */
		string State::index()
		{
			string s = toString() + "\n";
			for (unsigned i = 0; i < m_statements.size(); ++i)
				s += "\t\t" + m_statements[i]->toString() + "\n";
			return s;
		}

		/**
		 * Sets the StateMachine of the state
		 *
		 * @param machine the StateMachine to set
		 */
		void State::statemachineSet(StateMachine* machine)
		{
			m_machine = machine;
		}

		/**
		 * Adds the given statement to the State
		 *
		 * @param statement the statement to add
		 */
		void State::add(Statements::Statement* statement)
		{
			m_statements.push_back(statement);
		}

		/**
		 * Executes the State
		 * 
		 * @return reference to the next state (name of the state)
		 */
		string State::execute()
		{
			// Output of statements
			string out;

			// Each statement
			for (unsigned i = 0; i < m_statements.size(); ++i)
			{
				// Execute next statement
				out = m_statements[i]->execute(this);

				// If output is given, return output
				if (!out.empty()) return out;
			}

			// Return end output by default
			return "end";
		}
	}
}