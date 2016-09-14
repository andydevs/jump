/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_STATEMENTS_READ_H_
#define _CORE_STATEMENTS_READ_H_

// Headers being used
#include "statement.h"
#include "Jump/Core/Values/identifier.h"
#include "Jump/Core/Streams/readstream.h"

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
			 * Reads a value from the given input stream
			 * 
			 * @author  Anshul Kharbanda
			 * @created 7 - 16 - 2016
			 */
			class Read : public Statement
			{
			public:
				/**
				 * The identifier to store
				 */
				Values::Identifier* m_toStore;

				/**
				 * The stream to read from (pointer)
				 */
				Streams::Stream* m_streamRef;
		
				/**
				 * Creates a Read statement with the given value to Read
				 *
				 * @param toStore the value to store
				 */
				Read(Values::Identifier* toStore);

				/**
				 * Creates a Read statement with the given identifier to store and the stream to Read from
				 *
				 * @param toStore   the value to store
				 * @param streamRef the stream to read from
				 */
				Read(Values::Identifier* toStore, Streams::Stream* streamRef);

				/**
				 * Copy constructor for Read statement
				 *
				 * @param other the Read to copy
				 */
				Read(const Read& other);

				/**
				 * Destructor for Read statement
				 */
				~Read();

				/**
				 * Returns an inspection of the Read
				 *
				 * @return an inspection of the Read
				 */ 
				std::string inspect();

				/**
				 * Executes the Read statement
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