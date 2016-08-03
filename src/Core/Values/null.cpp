/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Values/null.h"

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
			 * Creates a null value
			 */
			Null::Null() : Value("NullType") {}

			/**
			 * Destroys the null value
			 */
			Null::~Null() {}

			/**
			 * Returns true if the value is Null
			 *
			 * @return true if the value is Null
			 */
			bool Null::isNull() const
			{
				return true;
			}

			/**
			 * Returns the string representaiton of the Null value
			 *
			 * @return the string representation of the Null value
			 */
			string Null::toString() const 
			{
				return "";
			}
		}
	}
}