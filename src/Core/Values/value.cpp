/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Values/value.h"

// Namespaces being used
using namespace std;
using namespace Jump::Core::Errors;

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
			 * Creates a value with the given type
			 *
			 * @param type the type of the value
			 */
			Value::Value(string type): m_type(type) {}

			/**
			 * Copy constructor for value
			 *
			 * @param other the other Value to copy
			 */ 
			Value::Value(const Value& other) : m_type(other.m_type) {}

			/**
			 * Destroys the value
			 */
			Value::~Value() {}

			/**
			 * Return the type of the value
			 * 
			 * @return the type of the value
			 */
			string Value::type() const
			{
				return m_type;
			}

			/**
			 * Returns true if the value is Null
			 *
			 * @return true if the value is Null
			 */
			bool Value::isNull() const
			{
				return false;
			}

			/**
			 * Returns the string representation of the Value
			 *
			 * @return the string representation of the Value
			 */
			string Value::toString() const
			{
				char buff[50];
				sprintf(buff, "<%s@%lx>", m_type.c_str(), (unsigned long)this);
				return string(buff);
			}

			/**
			 * Operator for passing value to output stream
			 *
			 * @param out the output stream to write to
			 * @param val the value to write
			 *
			 * @return the output stream that was written to
			 */
			std::ostream& operator<<(std::ostream& out, const Value& val)
			{
				return out << val.toString();
			}

			/**
			 * The boolean and operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the boolean and operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value Value::operator&&(const Value& other) const throw(TypeError)
			{
				throw TypeError("ValueType " + type() + " does not support operation &&");
			}

			/**
			 * The boolean or operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the boolean or operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value Value::operator||(const Value& other) const throw(TypeError)
			{
				throw TypeError("ValueType " + type() + " does not support operation ||");
			}

			/**
			 * The boolean not operation for Jump values
			 *
			 * @return the result of the boolean not operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value Value::operator!() const throw(TypeError)
			{
				throw TypeError("ValueType " + type() + " does not support operation !");
			}


			/**
			 * The greater than operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the greater than operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value Value::operator>(const Value& other) const throw(TypeError)
			{
				throw TypeError("ValueType " + type() + " does not support operation >");
			}

			/**
			 * The greater equals operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the greater equals operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value Value::operator>=(const Value& other) const throw(TypeError)
			{
				throw TypeError("ValueType " + type() + " does not support operation >=");
			}

			/**
			 * The equals operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the equals operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value Value::operator==(const Value& other) const throw(TypeError)
			{
				throw TypeError("ValueType " + type() + " does not support operation ==");
			}

			/**
			 * The not equals operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the not equals operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value Value::operator!=(const Value& other) const throw(TypeError)
			{
				throw TypeError("ValueType " + type() + " does not support operation !=");
			}

			/**
			 * The less equals operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the less equals operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value Value::operator<=(const Value& other) const throw(TypeError)
			{
				throw TypeError("ValueType " + type() + " does not support operation <=");
			}

			/**
			 * The less than operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the less than operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value Value::operator<(const Value& other) const throw(TypeError)
			{
				throw TypeError("ValueType " + type() + " does not support operation <");
			}


			/**
			 * The addition operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the addition operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value Value::operator+(const Value& other) const throw(TypeError)
			{
				throw TypeError("ValueType " + type() + " does not support operation +");
			}

			/**
			 * The subtraction operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the subtraction operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value Value::operator-(const Value& other) const throw(TypeError)
			{
				throw TypeError("ValueType " + type() + " does not support operation -");
			}

			/**
			 * The multiplication operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the multiplication operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value Value::operator*(const Value& other) const throw(TypeError)
			{
				throw TypeError("ValueType " + type() + " does not support operation *");
			}

			/**
			 * The division operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the division operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value Value::operator/(const Value& other) const throw(TypeError)
			{
				throw TypeError("ValueType " + type() + " does not support operation /");
			}

			/**
			 * The modulus operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the modulus operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			Value Value::operator%(const Value& other) const throw(TypeError)
			{
				throw TypeError("ValueType " + type() + " does not support operation %");
			}
		}
	}
}