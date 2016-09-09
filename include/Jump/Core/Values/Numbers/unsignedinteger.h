/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_VALUES_NUMBERS_UNSIGNEDINTEGER_H_
#define _CORE_VALUES_NUMBERS_UNSIGNEDINTEGER_H_

// Headers being used
#include "number.h"

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
				 * Represents an unsigned integer in Jump
				 *
				 * @author  Anshul Kharbanda
				 * @created 7 - 30 - 2016
				 */
				template <class T>
				class UnsignedInteger : public Number<T>
				{
				public:
					/**
					 * The value to store
					 */
					using Number<T>::m_store;

					/**
					 * Creates an UnsignedInteger with the given store
					 *
					 * @param store the integer value to store
					 */
					UnsignedInteger(T store);

					/**
					 * Copy constructor for UnsignedInteger
					 *
					 * @param other the other UnsignedInteger to copy
					 */ 
					UnsignedInteger(const UnsignedInteger& other);

					/**
					 * Destroys the UnsignedInteger
					 */
					~UnsignedInteger();

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

				// UnsignedInteger types
				typedef UnsignedInteger<unsigned char>  UInt8;
				typedef UnsignedInteger<unsigned short> UInt16;
				typedef UnsignedInteger<unsigned int>   UInt32;
				typedef UnsignedInteger<unsigned long>  UInt64;
			}
		}
	}
}

#endif