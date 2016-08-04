/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Values/Numbers/float64.h"
#include "Jump/Core/Values/Numbers/int32.h"
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
				 * Creates an Float64 with the given store
				 *
				 * @param store the float value to store
				 */
				Float64::Float64(double store) : Number("Float64"), m_store(store) {}

				/**
				 * Copy constructor for Float64
				 *
				 * @param other the other Float64 to copy
				 */ 
				Float64::Float64(const Float64& other) : Number(other), m_store(other.m_store) {}

				/**
				 * Destroys the Float64
				 */
				Float64::~Float64() {}

				/**
				 * Returns the value as an integer
				 *
				 * @return the value as an integer
				 */
				int Float64::toInt() const
				{
					return (int)m_store;
				}

				/**
				 * Returns the value as a float
				 *
				 * @return the value as a float
				 */
				double Float64::toFloat() const
				{
					return (double)m_store;
				}

				/**
				 * Returns the string representation of the Value
				 *
				 * @return the string representation of the Value
				 */
				std::string Float64::toString() const
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
				Value* Float64::plus(const Value* other) const throw(TypeError)
				{
					if (other->type() == "Number")
						return new Float64(m_store + ((const Number*)other)->toFloat());
					else if (other->type() == "String")
						return new String(to_string(m_store) + other->toString());
					else throw TypeError("Incompatible types for +: Float64 and " + other->type());
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
				Value* Float64::minus(const Value* other) const throw(TypeError)
				{
					if (other->type() == "Number")
						return new Float64(m_store - ((const Number*)other)->toFloat());
					else throw TypeError("Incompatible types for -: Float64 and " + other->type());
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
				Value* Float64::times(const Value* other) const throw(TypeError)
				{
					if (other->type() == "Number")
						return new Float64(m_store * ((const Number*)other)->toFloat());
					else throw TypeError("Incompatible types for -: Float64 and " + other->type());
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
				Value* Float64::divides(const Value* other) const throw(TypeError)
				{
					if (other->type() == "Number")
						return new Float64(m_store / ((const Number*)other)->toFloat());
					else throw TypeError("Incompatible types for -: Float64 and " + other->type());
				}
			}
		}
	}
}