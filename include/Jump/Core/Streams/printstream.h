/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_STREAMS_STDOUT_H_
#define _CORE_STREAMS_STDOUT_H_

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
			class PrintStream: public Stream
			{
			private:
				/**
				 * Standard out stream
				 */
				std::ostream& m_printstream;
			public:
				/**
				 * Creates a stream
				 */
				PrintStream(std::ostream& printstream);

				/**
				 * Copy constructor for Stream
				 *
				 * @param other the other Stream to copy
				 */
				PrintStream(const PrintStream& other);

				/**
				 * Destroys the string
				 */
				~PrintStream();

				/**
				 * Writes the given Value to the Stream
				 *
				 * @param value the value to print to the Stream
				 *
				 * @throw StreamError upon an error when writing to Stream
				 */
				void print(Values::Value* value) throw(Errors::StreamError);
			};
		}
	}
}

#endif