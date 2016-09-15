/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Streams/stream.h"

// Namespaces being used
using namespace std;
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
			 * Writes the given Value to the Stream
			 *
			 * @param value the value to print to the Stream
			 *
			 * @throw StreamError upon an error when printing to Stream
			 */
			void Stream::print(Values::Value* value) throw(StreamError)
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
			Values::Value* Stream::read() throw(StreamError)
			{
				throw StreamError("Stream cannot be read from.");
			}
		}
	}
}