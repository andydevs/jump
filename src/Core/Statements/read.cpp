/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Values/null.h"
#include "Jump/Core/Statements/read.h"
#include "Jump/Core/Streams/readstream.h"

// Libraries being used
#include <iostream>

// Namespaces being used
using namespace std;
using namespace Jump::Core::Values;
using namespace Jump::Core::Errors;
using namespace Jump::Core::Streams;

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
			 * Creates a Read statement with the given value to Read
			 *
			 * @param toStore the value to store
			 */
			Read::Read(Identifier* toStore):
			Statement(),
			m_toStore(toStore),
			m_streamRef(new ReadStream(cin))
			{}

			/**
			 * Creates a Read statement with the given identifier to store and the stream to Read from
			 *
			 * @param toStore   the value to store
			 * @param streamRef the stream to read from
			 */
			Read::Read(Identifier* toStore, Stream* streamRef):
			Statement(),
			m_toStore(toStore),
			m_streamRef(streamRef)
			{}

			/**
			 * Copy constructor for Read statement
			 *
			 * @param other the Read to copy
			 */
			Read::Read(const Read& other):
			Statement(other),
			m_toStore(other.m_toStore),
			m_streamRef(other.m_streamRef)
			{}

			/**
			 * Destructor for Read statement
			 */
			Read::~Read() {}

			/**
			 * Returns an inspection of the Read
			 *
			 * @return an inspection of the Read
			 */ 
			string Read::inspect()
			{
				return "[READ " + m_toStore->name() + "]";
			}

			/**
			 * Executes the Read statement
			 *
			 * @param stateRef reference to the containing state (pointer)
			 *
			 * @return a reference to the next state (the state's name)
			 *
			 * @throw JumpError upon an error when executing a statement
			 */
			string Read::execute(State* stateRef) throw(JumpError)
			{
				Value* red = m_streamRef->read();
				if (red == NULL) red = new Null();
				m_toStore->assign(stateRef, red);
				return "";
			}
		}
	}
}