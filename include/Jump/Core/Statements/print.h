//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

#ifndef _CORE_STATEMENT_PRINT_H_
#define _CORE_STATEMENT_PRINT_H_

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
		 * Contains all of the Jump statements
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 17 - 2016
		 */
		namespace Statements
		{
			/**
			 * Prints the given value to the given output stream
			 *
			 * @author  Anshul Kharbanda
			 * @created 7 - 16 - 2016
			 */
			class Print : public Statement
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
				Print(std::string toPrint);

				/**
				 * Creates a print statement with the given value to print and the stream to print to
				 *
				 * @param toPrint   the value to print
				 * @param streamRef the stream to print to
				 */
				Print(std::string toPrint, std::ostream& streamRef);

				/**
				 * Creates a print statement with the given condition to check and value to print
				 *
				 * @param condition the condition to ckeck
				 * @param toPrint   the value to print
				 */
				Print(bool condition, std::string toPrint);

				/**
				 * Creates a print statement with the given condition to check and value to print
				 *
				 * @param condition the condition to ckeck
				 * @param toPrint   the value to print
				 * @param streamRef the stream to print to (referenced)
				 */
				Print(bool condition, std::string toPrint, std::ostream& streamRef);

				/**
				 * Copy constructor for print statement
				 *
				 * @param other the Print to copy
				 */
				Print(const Print& other);

				/**
				 * Destructor for print statement
				 */
				~Print();

				/**
				 * Executes the print statement if the condition is true
				 *
				 * @param stateRef reference to the containing state (pointer)
				 *
				 * @return a reference to the next state (the state's name)
				 */
				std::string conditionedExecute(State* stateRef);
			};
		}
	}
}

#endif