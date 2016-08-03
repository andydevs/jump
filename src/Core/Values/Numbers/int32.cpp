/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Values/Numbers/int32.h"

// Libraries being used
#include <sstream>

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
				 * Creates an Int32 with the given store
				 *
				 * @param store the integer value to store
				 */
				Int32::Int32(int store) : Value("Int32"), m_store(store) {}

				/**
				 * Copy constructor for Int32
				 *
				 * @param other the other Int32 to copy
				 */ 
				Int32::Int32(const Int32& other) : Value(other), m_store(other.m_store) {}

				/**
				 * Destroys the Int32
				 */
				Int32::~Int32() {}

				/**
				 * Returns the store of the String
				 *
				 * @return the store of the String
				 */
				int Int32::store() const
				{
					return m_store;
				}

				/**
				 * Returns the string representation of the Value
				 *
				 * @return the string representation of the Value
				 */
				std::string Int32::toString() const
				{
					stringstream s;
					s << m_store;
					return s.str();
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
				Value Int32::operator+(const Value& other) const throw(TypeError)
				{
					if (other.type() == "Int32")
					{
						return Int32(m_store + ((const Int32&)other).store());
					}
					else throw TypeError("Incompatible types for +: Int32 and " + other.type());
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
				Value Int32::operator-(const Value& other) const throw(TypeError)
				{
					if (other.type() == "Int32")
					{
						return Int32(m_store + ((const Int32&)other).store());
					}
					else throw TypeError("Incompatible types for +: Int32 and " + other.type());
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
				Value Int32::operator*(const Value& other) const throw(TypeError)
				{
					if (other.type() == "Int32")
					{
						return Int32(m_store + ((const Int32&)other).store());
					}
					else throw TypeError("Incompatible types for +: Int32 and " + other.type());
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
				Value Int32::operator/(const Value& other) const throw(TypeError)
				{
					if (other.type() == "Int32")
					{
						return Int32(m_store + ((const Int32&)other).store());
					}
					else throw TypeError("Incompatible types for +: Int32 and " + other.type());
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
				Value Int32::operator%(const Value& other) const throw(TypeError)
				{
					if (other.type() == "Int32")
					{
						return Int32(m_store + ((const Int32&)other).store());
					}
					else throw TypeError("Incompatible types for +: Int32 and " + other.type());
				}	
			}
		}
	}
}