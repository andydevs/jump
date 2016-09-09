/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Values/Numbers/number.h"

// Namespaces being used
using namespace std;

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

				// Types
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