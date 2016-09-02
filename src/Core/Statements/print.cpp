/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Statements/print.h"
#include "Jump/Core/Values/null.h"

// Namespace being used
using namespace std;
using namespace Jump::Core::Values;

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
							 m_streamRef(cout) {}

			/**
			 * Creates a print statement with the given value to print
			 *
			 * @param toPrint the value to print
			 */
			Print::Print(Value* toPrint) : Statement(),  
										   m_toPrint(toPrint),
										   m_streamRef(cout) {}

			/**
			 * Creates a print statement with the given value to print and the stream to print to
			 *
			 * @param toPrint   the value to print
			 * @param streamRef the stream to print to
			 */
			Print::Print(Value* toPrint, ostream& streamRef) : Statement(),
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
				return "[PRINT" + (m_toPrint->isNull() ? "" : " " + m_toPrint->toString()) + "]";
			}

			/**
			 * Executes the print statement
			 *
			 * @param stateRef reference to the containing state (pointer)
			 *
			 * @return a reference to the next state (the state's name)
			 */
			string Print::execute(State* stateRef)
			{
				Value* evaluated = m_toPrint->evaluate();
				m_streamRef << evaluated->toString() << endl;
				return "";
			}
		}
	}
}