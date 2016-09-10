/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_STREAMS_STREAM_H_
#define _CORE_STREAMS_STREAM_H_

// Headers being used
#include "Jump/Core/Values/value.h"
#include "Jump/Core/Errors/stream.h"

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
			 * Basic stream object
			 *
			 * @author  Anshul Kharbanda
			 * @created 9 - 9 - 2016
			 */
			class Stream
			{
			public:
				/**
				 * Creates a stream
				 */
				Stream();

				/**
				 * Copy constructor for Stream
				 *
				 * @param other the other Stream to copy
				 */
				Stream(const Stream& other);

				/**
				 * Destroys the string
				 */
				~Stream();

				/**
				 * Writes the given Value to the Stream
				 *
				 * @param value the value to write to the Stream
				 *
				 * @throw StreamError upon an error when writing to Stream
				 */
				virtual void write(Values::Value* value) throw(Errors::StreamError);

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
}

#endif