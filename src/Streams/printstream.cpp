/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Streams/printstream.h"

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
			 * Creates a PrintStream with the given printstream
			 *
			 * @param printstream the print stream
			 */
			PrintStream::PrintStream(ostream& printstream):
			Stream(),
			m_printstream(printstream),
			m_delimeter("\n")
			{}

			/**
			 * Creates a PrintStream with the given printstream and
			 * delimeter
			 *
			 * @param printstream the print stream
			 * @param delimeter   the delimeter to print at the end
			 */
			PrintStream::PrintStream(ostream& printstream, string delimeter):
			Stream(),
			m_printstream(printstream),
			m_delimeter(delimeter)
			{}

			/**
			 * Copy constructor for Stream
			 *
			 * @param other the other Stream to copy
			 */
			PrintStream::PrintStream(const PrintStream& other):
			Stream(other),
			m_printstream(other.m_printstream),
			m_delimeter(other.m_delimeter)
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
				m_printstream << *value << m_delimeter;
			}
		}
	}
}