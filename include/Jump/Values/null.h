/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_VALUES_NULL_H_
#define _CORE_VALUES_NULL_H_

// Headers being used
#include "Jump/value.h"

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
		 * Null Jump value type
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 27 - 2016
		 */
		class Null : public Value
		{
		public:
			/**
			 * Creates a null value
			 */
			Null();

			/**
			 * Destroys the null value
			 */
			~Null();

			/**
			 * Returns true if the value is Null
			 *
			 * @return true if the value is Null
			 */
			bool isNull() const;

			/**
			 * Returns the string representaiton of the Null value
			 *
			 * @return the string representation of the Null value
			 */
			std::string toString() const;

			/**
			 * The equals operation for Jump Null values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the equals operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value* equal(const Value* other) const throw(Errors::TypeError);
		};
	}
}

#endif