/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_STATEMENT_PRINT_H_
#define _CORE_STATEMENT_PRINT_H_

// Headers being used
#include "statement.h"
#include "Jump/Values/value.h"

// Libaries being used
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
				Values::Value* m_toPrint;

				/**
				 * The stream to print to (referenced by name)
				 */
				std::string m_streamRef;

				/**
				 * Creates an empty print statement
				 */
				Print();
		
				/**
				 * Creates a print statement with the given value to print
				 *
				 * @param toPrint the value to print
				 */
				Print(Values::Value* toPrint);

				/**
				 * Creates a print statement with the given value to print and the stream to print to
				 *
				 * @param toPrint   the value to print
				 * @param streamRef the stream to print to (referenced by name)
				 */
				Print(Values::Value* toPrint, std::string streamRef);

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
				 * Returns an inspection of the Print
				 *
				 * @return an inspection of the Print
				 */ 
				std::string inspect();

				/**
				 * Executes the print statement
				 *
				 * @param stateRef reference to the containing state (pointer)
				 *
				 * @return a reference to the next state (the state's name)
				 *
				 * @throw JumpError upon an error when executing a statement
				 */
				std::string execute(State* stateRef) throw(Errors::JumpError);
			};
		}
	}
}

#endif