/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_VALUES_NUMBERS_FLOAT64_H_
#define _CORE_VALUES_NUMBERS_FLOAT64_H_

// Headres being used
#include "Jump/Core/Values/value.h"

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
				 * Represents a standard 64 bit float in Jump
				 *
				 * @author  Anshul Kharbanda
				 * @created 7 - 30 - 2016
				 */
				class Float64 : public Value
				{
				private:
					/**
					 * The stored float value
					 */
					double m_store;
				public:
					/**
					 * Creates an Float64 with the given store
					 *
					 * @param store the float value to store
					 */
					Float64(double store);

					/**
					 * Copy constructor for Float64
					 *
					 * @param other the other Float64 to copy
					 */ 
					Float64(const Float64& other);

					/**
					 * Destroys the Float64
					 */
					~Float64();

					/**
					 * Returns the store of the String
					 *
					 * @return the store of the String
					 */
					double store() const;

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
					Value operator+(const Value& other) const throw(Jump::Core::Errors::TypeError);

					/**
					 * The subtraction operation for Jump values
					 *
					 * @param other the other Value in the operation
					 *
					 * @return the result of the subtraction operation
					 *
					 * @throw TypeError upon an error during the operation
					 */
					Value operator-(const Value& other) const throw(Jump::Core::Errors::TypeError);

					/**
					 * The multiplication operation for Jump values
					 *
					 * @param other the other Value in the operation
					 *
					 * @return the result of the multiplication operation
					 *
					 * @throw TypeError upon an error during the operation
					 */
					Value operator*(const Value& other) const throw(Jump::Core::Errors::TypeError);

					/**
					 * The division operation for Jump values
					 *
					 * @param other the other Value in the operation
					 *
					 * @return the result of the division operation
					 *
					 * @throw TypeError upon an error during the operation
					 */
					Value operator/(const Value& other) const throw(Jump::Core::Errors::TypeError);
				};
			}
		}
	}
}

#endif