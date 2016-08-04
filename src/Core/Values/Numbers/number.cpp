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
				 * Creates a number with the given numericType
				 *
				 * @param numericType the numeric type of the number
				 */
				Number::Number(string numericType) : Value("Number"), m_numericType(numericType) {}

				/**
				 * Copy constructor for Number
				 *
				 * @param other the other Number to copy
				 */
				Number::Number(const Number& other) : Value(other), m_numericType(other.m_numericType) {}

				/**
				 * Destroys the number
				 */
				Number::~Number() {}

				/**
				 * Returns the numeric type of the number
				 *
				 * @return the numeric type of the number
				 */
				string Number::numericType() const
				{
					return m_numericType;
				}
			}
		}
	}
}