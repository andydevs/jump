/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/statemachine.h"
#include "Jump/Streams/printstream.h"
#include "Jump/Streams/readstream.h"

// Libraries being used
#include <iostream>

// Namespaces being used
using namespace std;
using namespace Jump::Errors;
using namespace Jump::Values;
using namespace Jump::Streams;

/**
 * Jump is a new programming language that uses the state machine paradigm
 *
 * @author  Anshul Kharbanda
 * @created 7 - 15 - 2016
 */
namespace Jump
{
	/**
	 * Creates an empty StateMachine
	 */
	StateMachine::StateMachine():
	m_statetable(),
	m_vartable(),
	m_consttable(),
	m_streamtable()
	{
		stateSet(new State("end"));
		streamSet("stdout", new PrintStream(cout));
		streamSet("stdin",  new ReadStream(cin));
		streamSet("stderr", new PrintStream(cerr));
		streamSet("prompt", new PrintStream(cout, " "));
	}

	/**
	 * Copy constructor for StateMachine
	 *
	 * @param other the other StateMachine to copy
	 */
	StateMachine::StateMachine(const StateMachine& other):
	m_statetable(other.m_statetable),
	m_vartable(other.m_vartable),
	m_consttable(other.m_consttable),
	m_streamtable(other.m_streamtable)
	{}

	/**
	 * Destroys the StateMachine
	 */
	StateMachine::~StateMachine()
	{
		// Delete all constants
		for (map<string, Value*>::iterator it = m_consttable.begin();
			it != m_consttable.end(); ++it)
			delete it->second;

		// Delete all variables
		for (map<string, Value*>::iterator it = m_vartable.begin();
			it != m_vartable.end(); ++it)
			delete it->second;

		// Delete all streams
		for (map<string, Stream*>::iterator it = m_streamtable.begin();
			it != m_streamtable.end(); ++it)
			delete it->second;

		// Delete all states
		for (map<string, State*>::iterator it = m_statetable.begin();
			it != m_statetable.end(); ++it)
			delete it->second;
	}

	/**
	 * Returns an inspection of the StateMachine
	 *
	 * @return an inspection of the StateMachine
	 */
	string StateMachine::inspect()
	{
		// Put start
		string s = "[STATEMACHINE]\n";

		// Put const table
		s += "\t[CONSTTABLE]\n";
		for (map<string, Value*>::iterator it = m_consttable.begin(); it != m_consttable.end(); ++it)
			s += "\t\t" + it->first + " - " + it->second->inspect() + "\n";

		// Put vartable
		s += "\t[VARTABLE]\n";
		for (map<string, Value*>::iterator it = m_vartable.begin(); it != m_vartable.end(); ++it)
			s += "\t\t" + it->first + " - " + it->second->inspect() + "\n";

		// Put states
		for (map<string, State*>::iterator it = m_statetable.begin(); it != m_statetable.end(); ++it)
			s += "\t" + it->second->inspect();

		// Return string
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
	State* StateMachine::stateGet(std::string name) throw(ReferenceError)
	{
		// Find state with name
		map<string, State*>::iterator it = m_statetable.find(name);

		// Return state if exists
		// Else throw error
		if (it != m_statetable.end())
		{
			return it->second;
		}
		else
		{
			throw ReferenceError("Undefined state " + name + " in statemachine.");
		}
	}

	/**
	 * Enters a stream into the StateMachine
	 *
	 * @param name   the name of the constant to enter
	 * @param stream the stream of the constant to enter
	 */
	void StateMachine::streamSet(std::string name, Stream* stream)
	{
		// Add stream to streamtable
		m_streamtable.insert(pair<string, Stream*>(name, stream));
	}

	/**
	 * Gets a constant from the StateMachine with the given namje
	 *
	 * @param name the name of the constant to retrieve
	 *
	 * @return the constant represented by the name
	 */
	Stream* StateMachine::streamGet(std::string name) throw(ReferenceError)
	{
		// Find stream with name
		map<string, Stream*>::iterator it = m_streamtable.find(name);

		// Return stream if exists
		// Else throw error
		if (it != m_streamtable.end())
			return it->second;
		else
			throw ReferenceError("Undefined stream " + name + " in statemachine.");
	}

	/**
	 * Enters a variable into the StateMachine
	 *
	 * @param name  the name of the variable to enter
	 * @param value the value of the variable to enter
	 */
	void StateMachine::varSet(string name, Value* value)
	{
		// Add variable to vartable
		m_vartable[name] = value;
	}

	/**
	 * Gets a variable from the StateMachine with the given name
	 *
	 * @param name the name of the variable to retrieve
	 *
	 * @return the variable represented by the name
	 */
	Value* StateMachine::varGet(string name) throw(ReferenceError)
	{
		// Find variable with name
		map<string, Value*>::iterator it = m_vartable.find(name);

		// Return var if exists
		// Else throw error
		if (it != m_vartable.end())
			return it->second;
		else
			throw ReferenceError("Undefined var " + name + " in statemachine.");
	}

	/**
	 * Enters a constant into the StateMachine
	 * Constants can only be set once!
	 *
	 * @param name  the name of the constant to enter
	 * @param value the value of the constant to enter
	 */
	void StateMachine::constSet(string name, Values::Value* value)
	{
		// Find variable with name
		map<string, Value*>::iterator it = m_consttable.find(name);

		// Set if not set
		if (it == m_consttable.end())
			m_consttable[name] = value;
	}

	/**
	 * Gets a constant from the StateMachine with the given name
	 *
	 * @param name the name of the constant to retrieve
	 *
	 * @return the constant represented by the name
	 */
	Value* StateMachine::constGet(std::string name) throw(ReferenceError)
	{
		// Find variable with name
		map<string, Value*>::iterator it = m_consttable.find(name);

		// Return const if exists
		// Else throw error
		if (it != m_consttable.end())
			return it->second;
		else
			throw ReferenceError("Undefined const " + name + " in statemachine.");
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

		// Loop until end state is reached
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