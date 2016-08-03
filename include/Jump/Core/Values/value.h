/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_VALUES_VALUE_H_
#define _CORE_VALUES_VALUE_H_

// Headers being used
#include "Jump/Core/Errors/typeerror.h"

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
			 * The base value type in Jump
			 *
			 * @author  Anshul Kharbanda
			 * @created 7 - 27 - 2016
			 */
			class Value
			{
			private:
				/**
				 * The type of the value
				 */
				std::string m_type;
			public:
				/**
				 * Creates a value with the given type
				 * 
				 * @param type the type of the value
				 */
				Value(std::string type);

				/**
				 * Copy constructor for value
				 *
				 * @param other the other Value to copy
				 */ 
				Value(const Value& other);

				/**
				 * Destroys the value
				 */
				virtual ~Value();

				/**
				 * Returns the type of the value
				 * 
				 * @return the type of the value
				 */
				std::string type() const;

				/**
				 * Returns true if the value is Null
				 *
				 * @return true if the value is Null
				 */
				virtual bool isNull() const;

				/**
				 * Returns the string representation of the Value
				 *
				 * @return the string representation of the Value
				 */
				virtual std::string toString() const;

				/**
				 * Operator for passing value to output stream
				 *
				 * @param out the output stream to write to
				 * @param val the value to write
				 *
				 * @return the output stream that was written to
				 */
				friend std::ostream& operator<<(std::ostream& out, const Value& val);

				/**
				 * The boolean and operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the boolean and operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				virtual Value operator&&(const Value& other) const throw(Jump::Core::Errors::TypeError);

				/**
				 * The boolean or operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the boolean or operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				virtual Value operator||(const Value& other) const throw(Jump::Core::Errors::TypeError);

				/**
				 * The boolean not operation for Jump values
				 *
				 * @return the result of the boolean not operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				virtual Value operator!() const throw(Jump::Core::Errors::TypeError);


				/**
				 * The greater ththe operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the greater ththe operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				virtual Value operator>(const Value& other) const throw(Jump::Core::Errors::TypeError);

				/**
				 * The greater equals operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the greater equals operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				virtual Value operator>=(const Value& other) const throw(Jump::Core::Errors::TypeError);

				/**
				 * The equals operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the equals operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				virtual Value operator==(const Value& other) const throw(Jump::Core::Errors::TypeError);

				/**
				 * The not equals operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the not equals operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				virtual Value operator!=(const Value& other) const throw(Jump::Core::Errors::TypeError);

				/**
				 * The less equals operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the less equals operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				virtual Value operator<=(const Value& other) const throw(Jump::Core::Errors::TypeError);

				/**
				 * The less ththe operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the less ththe operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				virtual Value operator<(const Value& other) const throw(Jump::Core::Errors::TypeError);


				/**
				 * The addition operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the addition operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				virtual Value operator+(const Value& other) const throw(Jump::Core::Errors::TypeError);

				/**
				 * The subtraction operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the subtraction operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				virtual Value operator-(const Value& other) const throw(Jump::Core::Errors::TypeError);

				/**
				 * The multiplication operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the multiplication operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				virtual Value operator*(const Value& other) const throw(Jump::Core::Errors::TypeError);

				/**
				 * The division operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the division operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				virtual Value operator/(const Value& other) const throw(Jump::Core::Errors::TypeError);

				/**
				 * The modulus operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the modulus operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				virtual Value operator%(const Value& other) const throw(Jump::Core::Errors::TypeError);
			};
		}
	}
}

#endif