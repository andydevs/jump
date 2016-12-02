/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Streams/arraystream.h"
#include "Jump/Values/null.h"

// Namespaces being used
using namespace std;
using namespace Jump::Values;
using namespace Jump::Errors;

// Code
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
		 * Creates an ArrayStream
		 */
		ArrayStream::ArrayStream():
		Stream(), m_container(queue<Value*>()) {}

		/**
		 * Copy constructor for ArrayStream
		 *
		 * @param other the other ArrayStream to copy
		 */
		ArrayStream::ArrayStream(const ArrayStream& other):
		Stream(other), m_container(other.m_container) {}

		/**
		 * Destroys the ArrayStream
		 */
		ArrayStream::~ArrayStream() {}

		/**
		 * Writes the given Value to the Stream
		 *
		 * @param value the value to print to the Stream
		 *
		 * @throw StreamError upon an error when writing to Stream
		 */
		void ArrayStream::print(Value* value) throw(StreamError)
		{
			m_container.push(value);
		}

		/**
		 * Reads a value from the Stream
		 *
		 * @return value read from the Stream
		 *
		 * @throw StreamError upon an error when reading from Stream
		 */
		Value* ArrayStream::read() throw(StreamError)
		{
			if (m_container.empty())
			{
				return new Null();
			}
			else
			{
				Value* ret = m_container.front();
				m_container.pop();
				return ret;
			}
		}
	}
}