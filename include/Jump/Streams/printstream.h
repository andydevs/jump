/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_STREAMS_STDOUT_H_
#define _CORE_STREAMS_STDOUT_H_

// Headers being used
#include "Jump/stream.h"

// Libraries being used
#include <string>
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
			 * The stream to print to
			 */
			std::ostream& m_printstream;

			/**
			 * The delimeter to print at the end
			 */
			std::string m_delimeter;
		public:
			/**
			 * Creates a PrintStream with the given printstream
			 *
			 * @param printstream the print stream
			 */
			PrintStream(std::ostream& printstream);

			/**
			 * Creates a PrintStream with the given printstream and
			 * delimeter
			 *
			 * @param printstream the print stream
			 * @param delimeter   the delimeter to print at the end
			 */
			PrintStream(std::ostream& printstream, std::string delimeter);

			/**
			 * Copy constructor for Stream
			 *
			 * @param other the other Stream to copy
			 */
			PrintStream(const PrintStream& other);

			/**
			 * Destroys the PrintStream
			 */
			~PrintStream();

			/**
			 * Writes the given Value to the Stream
			 *
			 * @param stateRef reference to State in which this is being printed
			 * @param value the value to print to the Stream
			 *
			 * @throw StreamError upon an error when writing to Stream
			 */
			virtual void print(State* stateRef, Values::Value* value) throw(Errors::StreamError);
		};
	}
}

#endif
