/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_VALUES_NUMBERS_FLOAT_H_
#define _CORE_VALUES_NUMBERS_FLOAT_H_

// Headres being used
#include "number.h"

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
				 * Represents a float in Jump
				 *
				 * @author  Anshul Kharbanda
				 * @created 7 - 30 - 2016
				 */
				template <class T>
				class Float : public Number<T>
				{
				public:
					/**
					 * The value to store
					 */
					using Number<T>::m_store;

					/**
					 * Creates an Float with the given store
					 *
					 * @param store the float value to store
					 */
					Float(T store);

					/**
					 * Copy constructor for Float
					 *
					 * @param other the other Float to copy
					 */ 
					Float(const Float& other);

					/**
					 * Destroys the Float
					 */
					~Float();

					/**
					 * The addition operation for Jump values
					 *
					 * @param other the other Value in the operation
					 *
					 * @return the result of the addition operation
					 *
					 * @throw TypeError upon an error during the operation
					 */
					Value* plus(const Value* other) const throw(Jump::Core::Errors::TypeError);

					/**
					 * The subtraction operation for Jump values
					 *
					 * @param other the other Value in the operation
					 *
					 * @return the result of the subtraction operation
					 *
					 * @throw TypeError upon an error during the operation
					 */
					Value* minus(const Value* other) const throw(Jump::Core::Errors::TypeError);

					/**
					 * The multiplication operation for Jump values
					 *
					 * @param other the other Value in the operation
					 *
					 * @return the result of the multiplication operation
					 *
					 * @throw TypeError upon an error during the operation
					 */
					Value* times(const Value* other) const throw(Jump::Core::Errors::TypeError);

					/**
					 * The division operation for Jump values
					 *
					 * @param other the other Value in the operation
					 *
					 * @return the result of the division operation
					 *
					 * @throw TypeError upon an error during the operation
					 */
					Value* divides(const Value* other) const throw(Jump::Core::Errors::TypeError);
				};

				// Float types
				typedef Float<float> Float32;
				typedef Float<double> Float64;
			}
		}
	}
}

#endif