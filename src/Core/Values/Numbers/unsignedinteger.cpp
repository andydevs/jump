/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Values/Numbers/unsignedinteger.h"
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
				 * Creates an UnsignedInteger with the given store
				 *
				 * @param store the integer value to store
				 */
				template <class T> UnsignedInteger<T>::UnsignedInteger(T store): Number<T>("UnsignedInteger", store) {}

				/**
				 * Copy constructor for UnsignedInteger
				 *
				 * @param other the other UnsignedInteger to copy
				 */ 
				template <class T> UnsignedInteger<T>::UnsignedInteger(const UnsignedInteger& other): Number<T>(other) {}

				/**
				 * Destroys the UnsignedInteger
				 */
				template <class T> UnsignedInteger<T>::~UnsignedInteger() {}

				/**
				 * The addition operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the addition operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				template <class T> Value* UnsignedInteger<T>::plus(const Value* other) const throw(TypeError)
				{
					if (other->type() == "UnsignedInteger")
						return new UInt32(m_store + other->toUnsigned());
					else if (other->type() == "Integer")
						return new Int32(m_store + other->toInt());
					else if (other->type() == "Float")
						return new Float64(m_store + other->toFloat());
					else if (other->type() == "String")
						return new String(to_string(m_store) + other->toString());
					else 
						throw Number<T>::plus(other);
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
				template <class T> Value* UnsignedInteger<T>::minus(const Value* other) const throw(TypeError)
				{
					if (other->type() == "UnsignedInteger")
						return new UInt32(m_store - other->toUnsigned());
					else if (other->type() == "Integer")
						return new Int32(m_store - other->toInt());
					else if (other->type() == "Float")
						return new Float64(m_store - other->toFloat());
					else
						throw Number<T>::plus(other);
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
				template <class T> Value* UnsignedInteger<T>::times(const Value* other) const throw(TypeError)
				{
					if (other->type() == "UnsignedInteger")
						return new UInt32(m_store * other->toUnsigned());
					else if (other->type() == "Integer")
						return new Int32(m_store * other->toInt());
					else if (other->type() == "Float")
						return new Float64(m_store * other->toFloat());
					else
						throw Number<T>::plus(other);
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
				template <class T> Value* UnsignedInteger<T>::divides(const Value* other) const throw(TypeError)
				{
					if (other->type() == "UnsignedInteger")
						return new UInt32(m_store / other->toUnsigned());
					else if (other->type() == "Integer")
						return new Int32(m_store / other->toInt());
					else if (other->type() == "Float")
						return new Float64(m_store / other->toFloat());
					else 
						throw Number<T>::divides(other);
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
				template <class T> Value* UnsignedInteger<T>::modulus(const Value* other) const throw(TypeError)
				{
					if (other->type() == "UnsignedInteger")
						return new UInt32(m_store % other->toUnsigned());
					else if (other->type() == "Integer")
						return new Int32(m_store % other->toInt());
					else
						throw Number<T>::modulus(other);
				}

				// Types
				template class UnsignedInteger<unsigned char>;
				template class UnsignedInteger<unsigned short>;
				template class UnsignedInteger<unsigned int>;
				template class UnsignedInteger<unsigned long>;
			}
		}
	}
}