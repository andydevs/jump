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
#include <deque>

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
			 * The behavior of the ArrayStream
			 *
			 * True if the ArrayStream behaves like a stack
			 * False if the ArrayStream behaves like a queue
			 */
			Values::Value* m_behavior;

			/**
			 * Contains values in the arraystream
			 */
			std::deque<Values::Value*> m_container;
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
			 * Sets an attribute to the stream
			 *
			 * @param id   the id of the attribute
			 * @param attr the attribute value to set
			 *
			 * @throw StreamError upon an error with setting attributes
			 */
			virtual void attributeSet(int id, Values::Value* attr) throw(Errors::StreamError);

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
