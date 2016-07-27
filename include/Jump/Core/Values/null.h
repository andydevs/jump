/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_VALUES_NULL_H_
#define _CORE_VALUES_NULL_H_

// Headers being used
#include "value.h"

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
			 * Null Jump value type
			 *
			 * @author  Anshul Kharbanda
			 * @created 7 - 27 - 2016
			 */
			class Null : public Value
			{
			public:
				/**
				 * Creates a null value
				 */
				Null();

				/**
				 * Destroys the null value
				 */
				~Null();

				/**
				 * Returns the string representaiton of the Null value
				 *
				 * @return the string representation of the Null value
				 */
				std::string toString() const;
			};
		}
	}
}

#endif