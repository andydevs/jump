/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Values/Numbers/integer.h"
#include "Jump/Core/Values/Numbers/float.h"
#include "Jump/Core/Values/string.h"

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
				 * Creates an Integer with the given store
				 *
				 * @param store the integer value to store
				 */
				template <class T> Integer<T>::Integer(T store): Number("Integer"), m_store(store) {}

				/**
				 * Copy constructor for Integer
				 *
				 * @param other the other Integer to copy
				 */ 
				template <class T> Integer<T>::Integer(const Integer& other): Number(other), m_store(other.m_store) {}

				/**
				 * Destroys the Integer
				 */
				template <class T> Integer<T>::~Integer() {}

				/**
				 * Returns the value as an integer
				 *
				 * @return the value as an integer
				 */
				template <class T> int Integer<T>::toInt() const
				{
					return (int)m_store;
				}

				/**
				 * Returns the value as a float
				 *
				 * @return the value as a float
				 */
				template <class T> double Integer<T>::toFloat() const
				{
					return (double)m_store;
				}

				/**
				 * Returns the string representation of the Value
				 *
				 * @return the string representation of the Value
				 */
				template <class T> std::string Integer<T>::toString() const
				{
					return to_string(m_store);
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
				template <class T> Value* Integer<T>::plus(const Value* other) const throw(TypeError)
				{
					if (other->type() == "Number")
					{
						const Number* number = (const Number*)other;
						if (number->numericType() == "Integer")
							return new Integer<int>(m_store + number->toInt());
						else if (number->numericType() == "Float")
							return new Float<double>(m_store + number->toFloat());
						else
							throw TypeError("Incompatible numeric types for +: Integer and " + number->numericType());
					}
					else if (other->type() == "String")
						return new String(to_string(m_store) + other->toString());
					else throw TypeError("Incompatible types for +: Integer and " + other->type());
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
				template <class T> Value* Integer<T>::minus(const Value* other) const throw(TypeError)
				{
					if (other->type() == "Number")
					{
						const Number* number = (const Number*)other;
						if (number->numericType() == "Integer")
							return new Integer<int>(m_store - number->toInt());
						else if (number->numericType() == "Float")
							return new Float<double>(m_store - number->toFloat());
						else
							throw TypeError("Incompatible numeric types for -: Integer and " + number->numericType());
					}
					else throw TypeError("Incompatible types for -: Integer and " + other->type());
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
				template <class T> Value* Integer<T>::times(const Value* other) const throw(TypeError)
				{
					if (other->type() == "Number")
					{
						const Number* number = (const Number*)other;
						if (number->numericType() == "Integer")
							return new Integer<int>(m_store * number->toInt());
						else if (number->numericType() == "Float")
							return new Float<double>(m_store * number->toFloat());
						else
							throw TypeError("Incompatible numeric types for *: Integer and " + number->numericType());
					}
					else throw TypeError("Incompatible types for *: Integer and " + other->type());
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
				template <class T> Value* Integer<T>::divides(const Value* other) const throw(TypeError)
				{
					if (other->type() == "Number")
					{
						const Number* number = (const Number*)other;
						if (number->numericType() == "Integer")
							return new Integer<int>(m_store / number->toInt());
						else if (number->numericType() == "Float")
							return new Float<double>(m_store / number->toFloat());
						else
							throw TypeError("Incompatible numeric types for /: Integer and " + number->numericType());
					}
					else throw TypeError("Incompatible types for /: Integer and " + other->type());
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
				template <class T> Value* Integer<T>::modulus(const Value* other) const throw(TypeError)
				{
					if (other->type() == "Number")
					{
						const Number* number = (const Number*)other;
						if (number->numericType() == "Integer")
							return new Integer<int>(m_store / number->toInt());
						else
							throw TypeError("Incompatible numeric types for %: Integer and " + number->numericType());
					}
					else throw TypeError("Incompatible types for /: Integer and " + other->type());
				}

				// Types
				template class Integer<char>;
				template class Integer<short>;
				template class Integer<int>;
				template class Integer<long>;
			}
		}
	}
}