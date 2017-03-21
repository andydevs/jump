/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Streams/arraystream.h"
#include "Jump/Values/boolean.h"
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
		Stream(), m_container() {
			m_behavior = new Boolean(false);
		}

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
		ArrayStream::~ArrayStream()
		{
			delete m_behavior;
		}

		/**
		 * Sets an attribute to the stream
		 *
		 * @param id   the id of the attribute
		 * @param attr the attribute value to set
		 *
		 * @throw StreamError upon an error with setting attributes
		 */
		void ArrayStream::attributeSet(int id, Values::Value* attr) throw(StreamError)
		{
			if (id == 0) {
				delete m_behavior;
				m_behavior = attr;
			} else throw StreamError("Invalid attribute id " + id);
		}

		/**
		 * Writes the given Value to the Stream
		 *
		 * @param stateRef reference to State in which this is being printed
		 * @param value the value to print to the Stream
		 *
		 * @throw StreamError upon an error when writing to Stream
		 */
		void ArrayStream::print(State* stateRef, Value* value) throw(StreamError)
		{
			m_container.push_back(value);
		}

		/**
		 * Reads a value from the Stream
		 *
		 * @param stateRef reference to State in which this is being printed
		 *
		 * @return value read from the Stream
		 *
		 * @throw StreamError upon an error when reading from Stream
		 */
		Value* ArrayStream::read(State* stateRef) throw(StreamError)
		{
			Value* ret;
			if (m_container.empty())
			{
				return new Null();
			}
			else if (m_behavior->evaluate(stateRef, 0)->toBool())
			{
				ret = m_container.back();
				m_container.pop_back();
				return ret;
			}
			else
			{
				ret = m_container.front();
				m_container.pop_front();
				return ret;
			}
		}
	}
}
