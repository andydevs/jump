//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Core/Statements/print.h"

// Namespace being used
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
							 m_toPrint(""),
							 m_streamRef(cout) {}

			/**
			 * Creates a print statement with the given value to print
			 *
			 * @param toPrint the value to print
			 */
			Print::Print(string toPrint) : Statement(),  
										   m_toPrint(toPrint),
										   m_streamRef(cout) {}

			/**
			 * Creates a print statement with the given value to print and the stream to print to
			 *
			 * @param toPrint   the value to print
			 * @param streamRef the stream to print to
			 */
			Print::Print(string toPrint, ostream& streamRef) : Statement(),
															   m_toPrint(toPrint),
															   m_streamRef(streamRef) {}

			/**
			 * Creates a print statement with the given condition to check and value to print
			 *
			 * @param condition the condition to ckeck
			 * @param toPrint   the value to print
			 */
			Print::Print(bool condition, string toPrint) : Statement(condition),
														   m_toPrint(toPrint),
														   m_streamRef(cout) {}

			/**
			 * Creates a print statement with the given condition to check and value to print
			 *
			 * @param condition the condition to ckeck
			 * @param toPrint   the value to print
			 * @param streamRef the stream to print to (referenced)
			 */
			Print::Print(bool condition, string toPrint, ostream& streamRef) : Statement(condition),
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
			Print::~Print() {}

			/**
			 * Returns the string representation of the Print
			 *
			 * @return the string representation of the Print
			 */ 
			std::string Print::toString()
			{
				return "[PRINT " + m_toPrint + "]";
			}

			/**
			 * Executes the print statement if the condition is true
			 *
			 * @param stateRef reference to the containing state (pointer)
			 *
			 * @return a reference to the next state (the state's name)
			 */
			string Print::conditionedExecute(State* stateRef)
			{
				m_streamRef << m_toPrint.substr(1, m_toPrint.length() - 2) << endl;
				return "";
			}
		}
	}
}