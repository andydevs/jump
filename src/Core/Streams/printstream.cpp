/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Streams/printstream.h"

// Namespaces being used
using namespace std;
using namespace Jump::Core::Values;
using namespace Jump::Core::Errors;

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
		 * Contains the streams
		 *
		 * @author  Anshul Kharbanda
		 * @created 9 - 9 - 2016
		 */
		namespace Streams
		{
			/**
			 * Creates a stream
			 */
			PrintStream::PrintStream(ostream& printstream):
			Stream(),
			m_printstream(printstream)
			{}

			/**
			 * Copy constructor for Stream
			 *
			 * @param other the other Stream to copy
			 */
			PrintStream::PrintStream(const PrintStream& other):
			Stream(other),
			m_printstream(other.m_printstream)
			{}

			/**
			 * Destroys the string
			 */
			PrintStream::~PrintStream() {}

			/**
			 * Writes the given Value to the Stream
			 *
			 * @param value the value to print to the Stream
			 *
			 * @throw StreamError upon an error when writing to Stream
			 */
			void PrintStream::print(Value* value) throw(StreamError)
			{
				m_printstream << *value << endl;
			}
		}
	}
}