/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/statemachine.h"
#include "Jump/state.h"
#include "Jump/Statements/print.h"
#include "Jump/Values/null.h"
#include "Jump/stream.h"

// Namespace being used
using namespace std;
using namespace Jump::Values;
using namespace Jump::Errors;
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
	 * Contains all of the Jump statements
	 *
	 * @author  Anshul Kharbanda
	 * @created 7 - 17 - 2016
	 */
	namespace Statements
	{
		/**
		 * Creates an empty print statement
		 */
		Print::Print() : Statement(),
						 m_toPrint(new Null()),
						 m_streamRef(STDNames::PRINT) {}

		/**
		 * Creates a print statement with the given value to print
		 *
		 * @param toPrint the value to print
		 */
		Print::Print(Value* toPrint) : Statement(),
									   m_toPrint(toPrint),
									   m_streamRef(STDNames::PRINT) {}

		/**
		 * Creates a print statement with the given value to print and the stream to print to
		 *
		 * @param toPrint   the value to print
		 * @param streamRef the stream to print to
		 */
		Print::Print(Value* toPrint, string streamRef) : Statement(),
														  m_toPrint(toPrint),
														  m_streamRef(streamRef) {}

		/**
		 * Copy constructor for print statement
		 *
		 * @param other the Print to copy
		 */
		Print::Print(const Print& other) : Statement(other),
										   m_toPrint(other.m_toPrint),
										   m_streamRef(other.m_streamRef) {}

		/**
		 * Destructor for print statement
		 */
		Print::~Print()
		{
			delete m_toPrint;
		}

		/**
		 * Returns an inspection of the Print
		 *
		 * @return an inspection of the Print
		 */
		string Print::inspect()
		{
			return "[PRINT " + (m_toPrint->isNull() ? "" : " " + m_toPrint->toString()) + " -> " + m_streamRef + "]";
		}

		/**
		 * Executes the print statement
		 *
		 * @param stateRef reference to the containing state (pointer)
		 *
		 * @return a reference to the next state (the state's name)
		 *
		 * @throw JumpError upon an error when executing a statement
		 */
		string Print::execute(State* stateRef) throw(JumpError)
		{
			Value* evaluated = m_toPrint->evaluate(stateRef, 0);
			Stream* stream = stateRef->statemachine()->streamGet(m_streamRef);
			stream->print(stateRef, evaluated);
			return "";
		}
	}
}
