/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _STREAMS_ARRAYSTREAM_H_
#define _STREAMS_ARRAYSTREAM_H_

// Headers being used
#include "Jump/stream.h"

// Libraries being used
#include <queue>

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
		 * Accesses and modifies a varying array of values
		 *
		 * @author  Anshul Kharbanda
		 * @created 12 - 2 - 2016
		 */
		class ArrayStream : public Stream
		{
		private:
			/**
			 * Contains values
			 */
			std::queue<Values::Value*> m_container;
		public:
			/**
			 * Creates an ArrayStream
			 */
			ArrayStream();

			/**
			 * Copy constructor for ArrayStream
			 *
			 * @param other the other ArrayStream to copy
			 */
			ArrayStream(const ArrayStream& other);

			/**
			 * Destroys the ArrayStream
			 */
			~ArrayStream();

			/**
			 * Writes the given Value to the Stream
			 *
			 * @param value the value to print to the Stream
			 *
			 * @throw StreamError upon an error when writing to Stream
			 */
			virtual void print(Values::Value* value) throw(Errors::StreamError);

			/**
			 * Reads a value from the Stream
			 *
			 * @return value read from the Stream
			 *
			 * @throw StreamError upon an error when reading from Stream
			 */
			virtual Values::Value* read() throw(Errors::StreamError);
		};
	}
}

#endif