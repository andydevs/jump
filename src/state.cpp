/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/state.h"

// Libraries being used
#include <iostream>

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
	 * Returns an inspection of the State
	 *
	 * @return an inspection of the State
	 */
	string State::inspect()
	{
		string s = "[STATE " + m_name + "]\n";
		for (unsigned i = 0; i < m_statements.size(); ++i)
			s += "\t\t" + m_statements[i]->inspect() + "\n";
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
	 * Returns the StateMachine of the state
	 *
	 * @return the StateMachine of the state
	 */
	StateMachine* State::statemachine()
	{
		return m_machine;
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