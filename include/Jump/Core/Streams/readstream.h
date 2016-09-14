/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_STREAMS_READSTREAM_H_
#define _CORE_STREAMS_READSTREAM_H_

// Headers being used
#include "stream.h"

// Libraries being used
#include <iostream>

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
			 * Print stream object
			 *
			 * @author  Anshul Kharbanda
			 * @created 9 - 9 - 2016
			 */
			class ReadStream: public Stream
			{
			private:
				/**
				 * The stream to read from
				 */
				std::istream& m_readstream;
			public:
				/**
				 * Creates a stream
				 */
				ReadStream(std::istream& readstream);

				/**
				 * Copy constructor for Stream
				 *
				 * @param other the other Stream to copy
				 */
				ReadStream(const ReadStream& other);

				/**
				 * Destroys the ReadStream
				 */
				~ReadStream();

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