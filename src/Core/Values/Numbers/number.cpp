/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Values/Numbers/number.h"
#include "Jump/Core/Values/boolean.h"

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
			 * Contains the number types for Jump
			 *
			 * @author  Anshul Kharbanda
			 * @created 7 - 30 - 2016
			 */
			namespace Numbers
			{
				/**
				 * Creates a number with the given type
				 *
				 * @param type the numeric type of the number
				 */
				template <class T> Number<T>::Number(string type, T store):
				Value(type),
				m_store(store)
				{}

				/**
				 * Copy constructor for Number
				 *
				 * @param other the other Number to copy
				 */
				template <class T> Number<T>::Number(const Number& other):
				Value(other),
				m_store(other.m_store)
				{}

				/**
				 * Destroys the number
				 */
				template <class T> Number<T>::~Number() {}

				/**
				 * The size of the numerical type
				 *
				 * @return the size of the numerical type
				 */
				template <class T> int Number<T>::size() const
				{
					return (int)sizeof(m_store)*8;
				}

				/**
				 * Returns the value as an unsigned integer
				 *
				 * @return the value as an unsigned integer
				 */
				template <class T> unsigned Number<T>::toUnsigned() const
				{
					return (unsigned)m_store;
				}

				/**
				 * Returns the value as an integer
				 *
				 * @return the value as an integer
				 */
				template <class T> int Number<T>::toInt() const
				{
					return (int)m_store;
				}

				/**
				 * Returns the value as a float
				 *
				 * @return the value as a float
				 */
				template <class T> double Number<T>::toFloat() const
				{
					return (double)m_store;
				}

				/**
				 * Returns the string representation of the Value
				 *
				 * @return the string representation of the Value
				 */
				template <class T> std::string Number<T>::toString() const
				{
					return to_string(m_store);
				}

				/**
				 * Returns the value as a boolean
				 *
				 * @return the value as a boolean
				 */
				template <class T> bool Number<T>::toBool() const
				{
					return m_store > 0;
				}

				/**
				 * The greater ththe operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the greater ththe operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				template <class T> Value* Number<T>::greater(const Value* other) const throw(TypeError)
				{
					if (other->type() == "UnsignedInteger")
						return new Boolean((unsigned)m_store > other->toUnsigned());
					else if (other->type() == "Integer")
						return new Boolean((int)m_store > other->toInt());
					else if (other->type() == "Float")
						return new Boolean((double)m_store > other->toFloat());
					else
						return Value::greater(other);
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
				template <class T> Value* Number<T>::greaterEqual(const Value* other) const throw(TypeError)
				{
					if (other->type() == "UnsignedInteger")
						return new Boolean((unsigned)m_store >= other->toUnsigned());
					else if (other->type() == "Integer")
						return new Boolean((int)m_store >= other->toInt());
					else if (other->type() == "Float")
						return new Boolean((double)m_store >= other->toFloat());
					else
						return Value::greaterEqual(other);
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
				template <class T> Value* Number<T>::equal(const Value* other) const throw(TypeError)
				{
					if (other->type() == "UnsignedInteger")
						return new Boolean((unsigned)m_store == other->toUnsigned());
					else if (other->type() == "Integer")
						return new Boolean((int)m_store == other->toInt());
					else if (other->type() == "Float")
						return new Boolean((double)m_store == other->toFloat());
					else
						return Value::equal(other);
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
				template <class T> Value* Number<T>::notEqual(const Value* other) const throw(TypeError)
				{
					if (other->type() == "UnsignedInteger")
						return new Boolean((unsigned)m_store != other->toUnsigned());
					else if (other->type() == "Integer")
						return new Boolean((int)m_store != other->toInt());
					else if (other->type() == "Float")
						return new Boolean((double)m_store != other->toFloat());
					else
						return Value::notEqual(other);
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
				template <class T> Value* Number<T>::lessEqual(const Value* other) const throw(TypeError)
				{
					if (other->type() == "UnsignedInteger")
						return new Boolean((unsigned)m_store <= other->toUnsigned());
					else if (other->type() == "Integer")
						return new Boolean((int)m_store <= other->toInt());
					else if (other->type() == "Float")
						return new Boolean((double)m_store <= other->toFloat());
					else
						return Value::lessEqual(other);
				}

				/**
				 * The less ththe operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the less ththe operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				template <class T> Value* Number<T>::less(const Value* other) const throw(TypeError)
				{
					if (other->type() == "UnsignedInteger")
						return new Boolean((unsigned)m_store < other->toUnsigned());
					else if (other->type() == "Integer")
						return new Boolean((int)m_store < other->toInt());
					else if (other->type() == "Float")
						return new Boolean((double)m_store < other->toFloat());
					else
						return Value::less(other);
				}

				// Types
				template class Number<unsigned char>;
				template class Number<unsigned short>;
				template class Number<unsigned int>;
				template class Number<unsigned long>;
				template class Number<char>;
				template class Number<short>;
				template class Number<int>;
				template class Number<long>;
				template class Number<float>;
				template class Number<double>;
			}
		}
	}
}