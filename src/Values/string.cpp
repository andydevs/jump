/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Values/boolean.h"
#include "Jump/Values/string.h"

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
		 * Creates a String
		 */
		String::String() : Value("String"), m_store("") {}

		/**
		 * Creates the String type with the given string value
		 *
		 * @param store the stored data of the string value
		 */
		String::String(std::string store) : Value("String"), m_store(store) {}

		/**
		 * Copy constructor for value
		 *
		 * @param other the other Value to copy
		 */ 
		String::String(const String& other) : Value(other), m_store(other.m_store) {}

		/**
		 * Destroys the string
		 */
		String::~String() {}

		/**
		 * Returns the store of the String
		 *
		 * @return the store of the String
		 */
		string String::store() const
		{
			return m_store;
		}

		/**
		 * Returns the string representation of the String
		 * 
		 * @return the string representation of the String
		 */
		string String::toString() const
		{
			return m_store;
		}

		/**
		 * The concatenation operator
		 *
		 * @param other the other value to concatenate
		 *
		 * @return the result of the concatenation operator
		 */
		Value* String::plus(const Value* other) const throw(TypeError)
		{
			return new String(toString() + other->toString());
		}

		/**
		 * The equals operation for Jump values
		 *
		 * @param other the other Value in the operation
		 *
		 * @return the result of the equals operation
		 *
		 * @throw TypeError upon an error during the operation
		 */
		Value* String::equal(const Value* other) const throw(TypeError)
		{
			return new Boolean(other->type() == "String" && toString() == other->toString());
		}
	}
}