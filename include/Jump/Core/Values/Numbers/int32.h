/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_VALUES_NUMBERS_INT32_H_
#define _CORE_VALUES_NUMBERS_INT32_H_
 
// Headers being used
#include "Jump/Core/Values/value.h"

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
	 * The core program
	 *
	 * @author  Anshul Kharbanda
	 * @created 7 - 16 - 2016
	 */
	namespace Core
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
			 * Contains the number types for Jump
			 *
			 * @author  Anshul Kharbanda
			 * @created 7 - 30 - 2016
			 */
			namespace Numbers
			{
				/**
				 * Represents a standard 32 bit integer in Jump
				 *
				 * @author  Anshul Kharbanda
				 * @created 7 - 30 - 2016
				 */
				class Int32 : public Value
				{
				private:
					/**
					 * The stored integer value
					 */
					int m_store;
				public:
					/**
					 * Creates an Int32 with the given store
					 *
					 * @param store the integer value to store
					 */
					Int32(int store);

					/**
					 * Copy constructor for Int32
					 *
					 * @param other the other Int32 to copy
					 */ 
					Int32(const Int32& other);

					/**
					 * Destroys the Int32
					 */
					~Int32();

					/**
					 * Returns the store of the String
					 *
					 * @return the store of the String
					 */
					int store() const;

					/**
					 * Returns the string representation of the Value
					 *
					 * @return the string representation of the Value
					 */
					std::string toString() const override;

					/**
					 * The addition operation for Jump values
					 *
					 * @param other the other Value in the operation
					 *
					 * @return the result of the addition operation
					 *
					 * @throw TypeError upon an error during the operation
					 */
					Value* plus(const Value* other) const throw(Jump::Core::Errors::TypeError);

					/**
					 * The subtraction operation for Jump values
					 *
					 * @param other the other Value in the operation
					 *
					 * @return the result of the subtraction operation
					 *
					 * @throw TypeError upon an error during the operation
					 */
					Value* minus(const Value* other) const throw(Jump::Core::Errors::TypeError);

					/**
					 * The multiplication operation for Jump values
					 *
					 * @param other the other Value in the operation
					 *
					 * @return the result of the multiplication operation
					 *
					 * @throw TypeError upon an error during the operation
					 */
					Value* times(const Value* other) const throw(Jump::Core::Errors::TypeError);

					/**
					 * The division operation for Jump values
					 *
					 * @param other the other Value in the operation
					 *
					 * @return the result of the division operation
					 *
					 * @throw TypeError upon an error during the operation
					 */
					Value* divides(const Value* other) const throw(Jump::Core::Errors::TypeError);

					/**
					 * The modulus operation for Jump values
					 *
					 * @param other the other Value in the operation
					 *
					 * @return the result of the modulus operation
					 *
					 * @throw TypeError upon an error during the operation
					 */
					Value* modulus(const Value* other) const throw(Jump::Core::Errors::TypeError);
				};
			}
		}
	}
}

#endif