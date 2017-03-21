/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Streams/readstream.h"
#include "Jump/Values/evaluate.h"

// Namespaces being used
using namespace std;
using namespace Jump::Values;
using namespace Jump::Errors;

/**
 * Jump is a new programming language that uses the state machine paradigm
 *
 * @author  Anshul Kharbanda
 * @created 7 - 15 - 2016
 */
namespace Jump
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
		ReadStream::ReadStream(istream& readstream):
		Stream(),
		m_readstream(readstream)
		{}

		/**
		 * Copy constructor for Stream
		 *
		 * @param other the other Stream to copy
		 */
		ReadStream::ReadStream(const ReadStream& other):
		Stream(other),
		m_readstream(other.m_readstream)
		{}

		/**
		 * Destroys the string
		 */
		ReadStream::~ReadStream() {}

		/**
		 * Reads a value from the Stream
		 *
		 * @param stateRef reference to State in which this is being printed
		 *
		 * @return value read from the Stream
		 *
		 * @throw StreamError upon an error when reading from Stream
		 */
		Value* ReadStream::read(State* stateRef) throw(StreamError)
		{
			string input;
			getline(m_readstream, input);
			return evaluate(input);
		}
	}
}
