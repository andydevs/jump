//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

#ifndef _CORE_PRINTSTATEMENT_H_
#define _CORE_PRINTSTATEMENT_H_

// Headers being used
#include "statement.h"

// Libaries being used
#include <iostream>
#include <string>

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
		 * Prints the given value to the given output stream
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 16 - 2016
		 */
		class PrintStatement : public Statement
		{
		public:
			/**
			 * The value to print
			 */
			std::string m_toPrint;

			/**
			 * The stream to print to (pointer)
			 */
			std::ostream& m_streamRef;
	
			/**
			 * Creates a print statement with the given value to print
			 *
			 * @param toPrint the value to print
			 */
			PrintStatement(std::string toPrint);

			/**
			 * Creates a print statement with the given value to print and the stream to print to
			 *
			 * @param toPrint   the value to print
			 * @param streamRef the stream to print to
			 */
			PrintStatement(std::string toPrint, std::ostream& streamRef);

			/**
			 * Creates a print statement with the given condition to check and value to print
			 *
			 * @param condition the condition to ckeck
			 * @param toPrint   the value to print
			 */
			PrintStatement(bool condition, std::string toPrint);

			/**
			 * Creates a print statement with the given condition to check and value to print
			 *
			 * @param condition the condition to ckeck
			 * @param toPrint   the value to print
			 * @param streamRef the stream to print to (referenced)
			 */
			PrintStatement(bool condition, std::string toPrint, std::ostream& streamRef);

			/**
			 * Copy constructor for print statement
			 *
			 * @param other the PrintStatement to copy
			 */
			PrintStatement(const PrintStatement& other);

			/**
			 * Destructor for print statement
			 */
			~PrintStatement();

			/**
			 * Executes the print statement if the condition is true
			 *
			 * @return a reference to the next state (the state's name)
			 */
			std::string conditionedExecute();
		};
	}
}

#endif