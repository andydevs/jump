//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Core/printstatement.h"

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
		 * Creates a print statement with the given value to print
		 *
		 * @param toPrint the value to print
		 */
		PrintStatement::PrintStatement(string toPrint) : Statement(), m_streamRef(cout)
		{
			m_toPrint = toPrint;
		}

		/**
		 * Creates a print statement with the given value to print and the stream to print to
		 *
		 * @param toPrint   the value to print
		 * @param streamRef the stream to print to
		 */
		PrintStatement::PrintStatement(string toPrint, ostream& streamRef) : Statement(), m_streamRef(m_streamRef)
		{
			m_toPrint = toPrint;
		}

		/**
		 * Creates a print statement with the given condition to check and value to print
		 *
		 * @param condition the condition to ckeck
		 * @param toPrint   the value to print
		 */
		PrintStatement::PrintStatement(bool condition, string toPrint) : Statement(condition), m_streamRef(cout)
		{
			m_toPrint = toPrint;
		}

		/**
		 * Creates a print statement with the given condition to check and value to print
		 *
		 * @param condition the condition to ckeck
		 * @param toPrint   the value to print
		 * @param streamRef the stream to print to (referenced)
		 */
		PrintStatement::PrintStatement(bool condition, string toPrint, ostream& streamRef) : Statement(condition), m_streamRef(m_streamRef)
		{
			m_toPrint = toPrint;
		}

		/**
		 * Copy constructor for print statement
		 *
		 * @param other the PrintStatement to copy
		 */
		PrintStatement::PrintStatement(const PrintStatement& other) : Statement(other), m_streamRef(other.m_streamRef)
		{
			m_toPrint = other.m_toPrint;
		}

		/**
		 * Destructor for print statement
		 */
		PrintStatement::~PrintStatement() {}

		/**
		 * Executes the print statement if the condition is true
		 *
		 * @param stateRef reference to the containing state (pointer)
		 *
		 * @return a reference to the next state (the state's name)
		 */
		string PrintStatement::conditionedExecute(State* stateRef)
		{
			m_streamRef << m_toPrint << endl;
			return "";
		}
	}
}