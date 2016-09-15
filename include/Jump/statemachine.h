/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_STATEMACHINE_H_
#define _CORE_STATEMACHINE_H_

// Headers being used
#include "Values/value.h"
#include "Errors/valueerror.h"
#include "Errors/referenceerror.h"
#include "Streams/stream.h"
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

		/**
		 * Holds the variable values
		 */
		std::map<std::string, Values::Value*> m_vartable;

		/**
		 * Holds the constant values
		 */
		std::map<std::string, Values::Value*> m_consttable;

		/**
		 * Holds the streams
		 */
		std::map<std::string, Streams::Stream*> m_streamtable;
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
		 * Returns an inspection of the StateMachine
		 *
		 * @return an inspection of the StateMachine
		 */
		std::string inspect();

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
		State* stateGet(std::string name) throw(Errors::ReferenceError);

		/**
		 * Enters a variable into the StateMachine
		 *
		 * @param name  the name of the variable to enter
		 * @param value the value of the variable to enter
		 */
		void varSet(std::string name, Values::Value* value);

		/**
		 * Gets a variable from the StateMachine with the given name
		 *
		 * @param name the name of the variable to retrieve
		 *
		 * @return the variable represented by the name
		 */
		Values::Value* varGet(std::string name) throw(Errors::ReferenceError);

		/**
		 * Enters a constant into the StateMachine
		 * Constants can only be set once!
		 *
		 * @param name  the name of the constant to enter
		 * @param value the value of the constant to enter
		 */
		void constSet(std::string name, Values::Value* value);

		/**
		 * Gets a constant from the StateMachine with the given name
		 *
		 * @param name the name of the constant to retrieve
		 *
		 * @return the constant represented by the name
		 */
		Values::Value* constGet(std::string name) throw(Errors::ReferenceError);

		/**
		 * Enters a stream into the StateMachine
		 *
		 * @param name   the name of the constant to enter
		 * @param stream the stream of the constant to enter
		 */
		void streamSet(std::string name, Streams::Stream* stream);

		/**
		 * Gets a constant from the StateMachine with the given name
		 *
		 * @param name the name of the constant to retrieve
		 *
		 * @return the constant represented by the name
		 */
		Streams::Stream* streamGet(std::string name) throw(Errors::ReferenceError);

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

#endif