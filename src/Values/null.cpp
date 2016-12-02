/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Values/null.h"
#include "Jump/Values/boolean.h"
#include "Jump/Errors/typeerror.h"

// Namespaces being used
using namespace std;
using namespace Jump::Errors;

/**
 * Jump is a new programming language that uses the state machine paradigm
 *
 * @author  Anshul Kharbanda
 * @created 7 - 15 - 2016
 */
namespace Jump
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

		/**
		 * The equals operation for Jump Null values
		 *
		 * @param other the other Value in the operation
		 *
		 * @return the result of the equals operation
		 *
		 * @throw TypeError upon an error during the operation
		 */
		Value* Null::equal(const Value* other) const throw(TypeError)
		{
			return new Boolean(other->isNull());
		}
	}
}