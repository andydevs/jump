/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_VALUES_NUMBERS_NUMBER_H_
#define _CORE_VALUES_NUMBERS_NUMBER_H_

// Headers being used
#include "Jump/Core/Values/value.h"

// Libraries being used
#include <string>

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
				 * Represents a basic number in Jump
				 *
				 * @author  Anshul Kharbanda
				 * @created 8 - 04 - 2016
				 */
				template <class T>
				class Number : public Value
				{
				protected:
					/**
					 * The value to store
					 */
					T m_store;
				public:
					/**
					 * Creates a number with the given type
					 *
					 * @param type the type of the number
					 */
					Number(std::string type, T store);

					/**
					 * Copy constructor for Number
					 *
					 * @param other the other Number to copy
					 */
					Number(const Number& other);

					/**
					 * Destroys the number
					 */
					~Number();

					/**
					 * Returns the string representation of the Value
					 *
					 * @return the string representation of the Value
					 */
					std::string toString() const;

					/**
					 * Returns the value as an integer
					 *
					 * @return the value as an integer
					 */
					int toInt() const;

					/**
					 * Returns the value as a float
					 *
					 * @return the value as a float
					 */
					double toFloat() const;
				};
			}
		}
	}
}

#endif