/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Values/Numbers/integer.h"
#include "Jump/Values/Numbers/float.h"
#include "Jump/Values/string.h"

// Namespaces being used
using namespace std;
using namespace Jump::Errors;

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
			template <class T> Integer<T>::Integer(T store): Number<T>("Integer", store) {}

			/**
			 * Copy constructor for Integer
			 *
			 * @param other the other Integer to copy
			 */ 
			template <class T> Integer<T>::Integer(const Integer& other): Number<T>(other) {}

			/**
			 * Destroys the Integer
			 */
			template <class T> Integer<T>::~Integer() {}

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
				if (other->type() == "Integer" || other->type() == "UnsignedInteger")
				{
					switch(this->size() >= other->size() ? this->size() : other->size())
					{
						case 64: return new Int64(m_store + other->toInt());
						case 32: return new Int32(m_store + other->toInt());
						case 16: return new Int16(m_store + other->toInt());
						default: return new Int8(m_store + other->toInt());
					}
				}
				else if (other->type() == "Float")
				{
					switch(this->size() >= other->size() ? this->size() : other->size())
					{
						case 64: return new Float64(m_store + other->toFloat());
						default: return new Float32(m_store + other->toFloat());
					}
				}
				else if (other->type() == "String")
				{
					return new String(to_string(m_store) + other->toString());
				}
				else
				{
					throw Number<T>::plus(other);
				}
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
				if (other->type() == "Integer" || other->type() == "UnsignedInteger")
				{
					switch(this->size() >= other->size() ? this->size() : other->size())
					{
						case 64: return new Int64(m_store - other->toInt());
						case 32: return new Int32(m_store - other->toInt());
						case 16: return new Int16(m_store - other->toInt());
						default: return new Int8(m_store - other->toInt());
					}
				}
				else if (other->type() == "Float")
				{
					switch(this->size() >= other->size() ? this->size() : other->size())
					{
						case 64: return new Float64(m_store - other->toFloat());
						default: return new Float32(m_store - other->toFloat());
					}
				}
				else
				{
					throw Number<T>::minus(other);
				}
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
				if (other->type() == "Integer" || other->type() == "UnsignedInteger")
				{
					switch(this->size() >= other->size() ? this->size() : other->size())
					{
						case 64: return new Int64(m_store * other->toInt());
						case 32: return new Int32(m_store * other->toInt());
						case 16: return new Int16(m_store * other->toInt());
						default: return new Int8(m_store * other->toInt());
					}
				}
				else if (other->type() == "Float")
				{
					switch(this->size() >= other->size() ? this->size() : other->size())
					{
						case 64: return new Float64(m_store * other->toFloat());
						default: return new Float32(m_store * other->toFloat());
					}
				}
				else
				{
					throw Number<T>::times(other);
				}
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
				if (other->type() == "Integer" || other->type() == "UnsignedInteger")
				{
					switch(this->size() >= other->size() ? this->size() : other->size())
					{
						case 64: return new Int64(m_store / other->toInt());
						case 32: return new Int32(m_store / other->toInt());
						case 16: return new Int16(m_store / other->toInt());
						default: return new Int8(m_store / other->toInt());
					}
				}
				else if (other->type() == "Float")
				{
					switch(this->size() >= other->size() ? this->size() : other->size())
					{
						case 64: return new Float64(m_store / other->toFloat());
						default: return new Float32(m_store / other->toFloat());
					}
				}
				else
				{
					throw Number<T>::divides(other);
				}
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
				if (other->type() == "Integer" || other->type() == "UnsignedInteger")
				{
					switch(this->size() >= other->size() ? this->size() : other->size())
					{
						case 64: return new Int64(m_store % other->toInt());
						case 32: return new Int32(m_store % other->toInt());
						case 16: return new Int16(m_store % other->toInt());
						default: return new Int8(m_store % other->toInt());
					}
				}
				else
				{
					throw Number<T>::modulus(other);
				}
			}

			// Types
			template class Integer<char>;
			template class Integer<short>;
			template class Integer<int>;
			template class Integer<long>;
		}
	}
}