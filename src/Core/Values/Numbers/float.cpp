/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Values/Numbers/float.h"
#include "Jump/Core/Values/Numbers/integer.h"
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
				 * Creates an Float with the given store
				 *
				 * @param store the float value to store
				 */
				template <class T> Float<T>::Float(T store): Number<T>("Float", store) {}

				/**
				 * Copy constructor for Float
				 *
				 * @param other the other Float to copy
				 */ 
				template <class T> Float<T>::Float(const Float& other): Number<T>(other) {}

				/**
				 * Destroys the Float
				 */
				template <class T> Float<T>::~Float() {}

				/**
				 * The addition operation for Jump values
				 *
				 * @param other the other Value in the operation
				 *
				 * @return the result of the addition operation
				 *
				 * @throw TypeError upon an error during the operation
				 */
				template <class T> Value* Float<T>::plus(const Value* other) const throw(TypeError)
				{
					if (other->type() == "Integer" 
						|| other->type() == "UnsignedInteger" 
						|| other->type() == "Float")
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
				template <class T> Value* Float<T>::minus(const Value* other) const throw(TypeError)
				{
					if (other->type() == "Integer" 
						|| other->type() == "UnsignedInteger" 
						|| other->type() == "Float")
						return new Float64(m_store - other->toFloat());
					else 
						throw Number<T>::minus(other);
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
				template <class T> Value* Float<T>::times(const Value* other) const throw(TypeError)
				{
					if (other->type() == "Integer" 
						|| other->type() == "UnsignedInteger" 
						|| other->type() == "Float")
						return new Float64(m_store * other->toFloat());
					else 
						throw Number<T>::times(other);
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
				template <class T> Value* Float<T>::divides(const Value* other) const throw(TypeError)
				{
					if (other->type() == "Integer" 
						|| other->type() == "UnsignedInteger" 
						|| other->type() == "Float")
						return new Float64(m_store / other->toFloat());
					else 
						throw Number<T>::divides(other);
				}

				// Types
				template class Float<float>;
				template class Float<double>;
			}
		}
	}
}