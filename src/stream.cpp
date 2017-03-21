/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/stream.h"

// Namespaces being used
using namespace std;
using namespace Jump::Errors;
using namespace Jump::Values;

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
		Stream::Stream() {}

		/**
		 * Copy constructor for Stream
		 *
		 * @param other the other Stream to copy
		 */
		Stream::Stream(const Stream& other) {}

		/**
		 * Destroys the string
		 */
		Stream::~Stream() {}

		/**
		 * Adds an attribute to the stream
		 *
		 * @param id   the id of the attribute
		 * @param attr the attribute to add
		 *
		 * @throw StreamError upon an error with setting attributes
		 */
		void Stream::attributeSet(int id, Value* attr) throw(StreamError)
		{
			throw StreamError("Stream cannot have attributes set");
		}

		/**
		 * Writes the given Value to the Stream
		 *
		 * @param value the value to print to the Stream
		 *
		 * @throw StreamError upon an error when printing to Stream
		 */
		void Stream::print(Value* value) throw(StreamError)
		{
			throw StreamError("Stream cannot be written to.");
		}

		/**
		 * Reads a value from the Stream
		 *
		 * @return value read from the Stream
		 *
		 * @throw StreamError upon an error when reading from Stream
		 */
		Value* Stream::read() throw(StreamError)
		{
			throw StreamError("Stream cannot be read from.");
		}
	}
}
