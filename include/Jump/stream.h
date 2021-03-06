/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_STREAMS_STREAM_H_
#define _CORE_STREAMS_STREAM_H_

// Headers being used
#include "Jump/value.h"
#include "Jump/Errors/streamerror.h"

// Libraries
#include <iostream>
#include <vector>

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
		 * Contains standard stream names
		 *
		 * @author  Anshul Kharbanda
		 * @created 3 - 21 - 2017
		 */
		namespace STDNames {
			/**
			 * Name for standard read
			 */
			const std::string READ = "STDReadStream";

			/**
			 * Name for standard print
			 */
			const std::string PRINT = "STDPrintStream";

			/**
			 * Name for standard error
			 */
			const std::string ERROR = "STDErrorStream";

			/**
			 * Name for standard prompt
			 */
			const std::string PROMPT = "STDPromptStream";
		}

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
			 * Destroys the Stream
			 */
			virtual ~Stream();

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
			 * @param stateRef reference to State in which this is being printed
			 * @param value the value to print to the Stream
			 *
			 * @throw StreamError upon an error when writing to Stream
			 */
			virtual void print(State* stateRef, Values::Value* value) throw(Errors::StreamError);

			/**
			 * Reads a value from the Stream
			 *
			 * @param stateRef reference to State in which this is being printed
			 *
			 * @return value read from the Stream
			 *
			 * @throw StreamError upon an error when reading from Stream
			 */
			virtual Values::Value* read(State* stateRef) throw(Errors::StreamError);
		};
	}
}

#endif
