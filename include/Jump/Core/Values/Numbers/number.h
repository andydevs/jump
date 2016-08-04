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
				class Number : public Value
				{
				private:
					/**
					 * The numeric type of the number
					 */
					std::string m_numericType;
				public:
					/**
					 * Creates a number with the given numericType
					 *
					 * @param numericType the numeric type of the number
					 */
					Number(std::string numericType);

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
					 * Returns the numeric type of the number
					 *
					 * @return the numeric type of the number
					 */
					std::string numericType() const;

					/**
					 * Returns the value as an integer
					 *
					 * @return the value as an integer
					 */
					virtual int toInt() const = 0;

					/**
					 * Returns the value as a float
					 *
					 * @return the value as a float
					 */
					virtual double toFloat() const = 0;
				};
			}
		}
	}
}

#endif