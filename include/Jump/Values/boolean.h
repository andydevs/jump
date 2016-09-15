/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_VALUES_BOOLEAN_H_
#define _CORE_VALUES_BOOLEAN_H_

// Headers being used
#include "Jump/value.h"

// Libraries being used
#include <string>

/**
 * Jump is a new programming language that uses the state machine paradigm
 *
 * @author  Anshul Kharbanda
 * @created 7 - 15 - 2016
 */
namespace Jump
{
	/**
	 * Contains the value types for Jump
	 *
	 * @author  Anshul Kharbanda
	 * @created 7 - 27 - 2016
	 */
	namespace Values
	{
		/**
		 * Represents a Boolean in Jump
		 *
		 * @author  Anshul Kharbanda
		 * @created 9 - 8 - 2016
		 */
		class Boolean: public Value
		{
		private:
			/**
			 * The boolean value to store
			 */
			bool m_store;
		public:
			/**
			 * Creates a boolean with the given store value
			 *
			 * @param store the value to store
			 */
			Boolean(bool store);

			/**
			 * Copy constructor for Boolean
			 *
			 * @param other the other value to copy
			 */
			Boolean(const Boolean& other);

			/**
			 * Destroys the Boolean
			 */
			~Boolean();

			/**
			 * Returns the string representation of the Value
			 *
			 * @return the string representation of the Value
			 */
			std::string toString() const;

			/**
			 * Returns the value as an unsigned integer
			 *
			 * @return the value as an unsigned integer
			 */
			unsigned toUnsigned() const;

			/**
			 * Returns the value as an integer
			 *
			 * @return the value as an integer
			 */
			int toInt() const;

			/**
			 * Returns the value as a float
			 *
			 * @return the value as a float
			 */
			double toFloat() const;

			/**
			 * Returns the value as a boolean
			 *
			 * @return the value as a boolean
			 */
			bool toBool() const;

			/**
			 * The boolean and operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the boolean and operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value* andd(const Value* other) const throw(Errors::TypeError);

			/**
			 * The boolean or operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the boolean or operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value* orr(const Value* other) const throw(Errors::TypeError);

			/**
			 * The boolean not operation for Jump values
			 *
			 * @return the result of the boolean not operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value* nott() const throw(Errors::TypeError);
		};
	}
}

#endif