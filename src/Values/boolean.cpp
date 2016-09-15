/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Values/boolean.h"

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
		 * Creates a boolean with the given store value
		 *
		 * @param store the value to store
		 */
		Boolean::Boolean(bool store): Value("Boolean"), m_store(store) {}

		/**
		 * Copy constructor for Boolean
		 *
		 * @param other the other value to copy
		 */
		Boolean::Boolean(const Boolean& other): Value(other), m_store(other.m_store) {}

		/**
		 * Destroys the Boolean
		 */
		Boolean::~Boolean() {}

		/**
		 * Returns the string representation of the Value
		 *
		 * @return the string representation of the Value
		 */
		string Boolean::toString() const
		{
			return m_store ? "True" : "False";
		}

		/**
		 * Returns the value as an unsigned integer
		 *
		 * @return the value as an unsigned integer
		 */
		unsigned Boolean::toUnsigned() const
		{
			return (unsigned)m_store;
		}

		/**
		 * Returns the value as an integer
		 *
		 * @return the value as an integer
		 */
		int Boolean::toInt() const
		{
			return (int)m_store;
		}

		/**
		 * Returns the value as a float
		 *
		 * @return the value as a float
		 */
		double Boolean::toFloat() const
		{
			return (double)m_store;
		}

		/**
		 * Returns the bool representation of the Value
		 *
		 * @return the bool representation of the Value
		 */
		bool Boolean::toBool() const
		{
			return m_store;
		}

		/**
		 * The boolean and operation for Jump values
		 *
		 * @param other the other Value in the operation
		 *
		 * @return the result of the boolean and operation
		 *
		 * @throw TypeError upon an error during the operation
		 */
		Value* Boolean::andd(const Value* other) const throw(TypeError)
		{
			return new Boolean(m_store && other->toBool());
		}

		/**
		 * The boolean or operation for Jump values
		 *
		 * @param other the other Value in the operation
		 *
		 * @return the result of the boolean or operation
		 *
		 * @throw TypeError upon an error during the operation
		 */
		Value* Boolean::orr(const Value* other) const throw(TypeError)
		{
			return new Boolean(m_store || other->toBool());
		}

		/**
		 * The boolean not operation for Jump values
		 *
		 * @return the result of the boolean not operation
		 *
		 * @throw TypeError upon an error during the operation
		 */
		Value* Boolean::nott() const throw(TypeError)
		{
			return new Boolean(!m_store);
		}
	}
}