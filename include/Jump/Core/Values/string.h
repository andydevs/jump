/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_VALUES_STRING_H_
#define _CORE_VALUES_STRING_H_

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
			 * A jump string
			 *
			 * @author  Anshul Kharbanda
		 	 * @created 7 - 27 - 2016
			 */
			class String : public Value
			{
			private:
				/**
				 * The stored data of the string value
				 */
				std::string m_store;
			public:
				/**
				 * Creates a String
				 */
				String();

				/**
				 * Creates a String type with the given string value
				 *
				 * @param store the stored data of the string value
				 */
				String(std::string store);

				/**
				 * Copy constructor for value
				 *
				 * @param other the other Value to copy
				 */ 
				String(const String& other);

				/**
				 * Destroys the string
				 */
				~String();

				/**
				 * Returns the store of the String
				 *
				 * @return the store of the String
				 */
				std::string store() const;

				/**
				 * Returns the string representation of the String
				 * 
				 * @return the string representation of the String
				 */
				std::string toString() const override;

				/**
				 * The concatenation operator
				 *
				 * @param other the other value to concatenate
				 *
				 * @return the result of the concatenation operator
				 */
				String operator+(Value other) const;
			};
		}
	}
}

#endif