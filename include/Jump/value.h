/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_VALUES_VALUE_H_
#define _CORE_VALUES_VALUE_H_

// Headers being used
#include "Jump/statement.h"
#include "Jump/Errors/valueerror.h"
#include "Jump/Errors/typeerror.h"

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
	 * Contains the value types for Jump
	 *
	 * @author  Anshul Kharbanda
	 * @created 7 - 27 - 2016
	 */
	namespace Values
	{
		/**
		 * Do not evaluate the value in the identifier
		 */
		const int NO_EVALUATE_IDENTIFIER = 1;

		/**
		 * The base value type in Jump
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 27 - 2016
		 */
		class Value: public Statements::Statement
		{
		protected:
			/**
			 * The type of the value
			 */
			std::string m_type;
		public:
			/**
			 * Creates a value with the given type
			 * 
			 * @param type the type of the value
			 */
			Value(std::string type);

			/**
			 * Copy constructor for value
			 *
			 * @param other the other Value to copy
			 */ 
			Value(const Value& other);

			/**
			 * Destroys the value
			 */
			virtual ~Value();

			/**
			 * Returns the type of the value
			 * 
			 * @return the type of the value
			 */
			std::string type() const;

			/**
			 * Returns true if the value is Null
			 *
			 * @return true if the value is Null
			 */
			virtual bool isNull() const;

			/**
			 * The bit size of the stored value
			 *
			 * @return the size of the stored value
			 */
			virtual int size() const;

			/**
			 * Returns the string representation of the Value
			 *
			 * @return the string representation of the Value
			 */
			virtual std::string toString() const;

			/**
			 * Returns the value as an unsigned integer
			 *
			 * @return the value as an unsigned integer
			 */
			virtual unsigned toUnsigned() const;

			/**
			 * Returns the value as an integer
			 *
			 * @return the value as an integer
			 */
			virtual int toInt() const;

			/**
			 * Returns the value as a float
			 *
			 * @return the value as a float
			 */
			virtual double toFloat() const;

			/**
			 * Returns the value as a boolean
			 *
			 * @return the value as a boolean
			 */
			virtual bool toBool() const;

			/**
			 * Returns an inspection of the Statement
			 *
			 * @return an inspection of the Statement
			 */ 
			std::string inspect();

			/**
			 * Evaluates the value in the context of the given state
			 *
			 * @param stateRef a reference to the state being evaluated
			 * @param flags    flags to evauate the state with
			 *
			 * @return the evaluated value
			 *
			 * @throw ValueError upon an error when evaluating
			 */
			virtual Value* evaluate(State* stateRef, int flags) throw(Errors::ValueError);

			/**
			 * The assignment operation for Jump values
			 *
			 * @param stateRef a reference to the state being assigned
			 * @param value    the value being assigned to
			 *
			 * @return the value being assigned to
			 */
			virtual Value* assign(State* stateRef, Value* value) throw(Errors::ValueError);

			/**
			 * Executes the statement
			 *
			 * @param stateRef reference to the containing state (pointer)
			 * 
			 * @return a reference to the next state (the state's name)
			 *
			 * @throw JumpError upon an error when executing a statement
			 */
			std::string execute(State* stateRef) throw(Errors::JumpError);

			/**
			 * Operator for passing value to output stream
			 *
			 * @param out the output stream to write to
			 * @param val the value to write
			 *
			 * @return the output stream that was written to
			 */
			friend std::ostream& operator<<(std::ostream& out, const Value& val);

			/**
			 * The boolean and operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the boolean and operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			virtual Value* andd(const Value* other) const throw(Errors::TypeError);

			/**
			 * The boolean or operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the boolean or operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			virtual Value* orr(const Value* other) const throw(Errors::TypeError);

			/**
			 * The boolean not operation for Jump values
			 *
			 * @return the result of the boolean not operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			virtual Value* nott() const throw(Errors::TypeError);

			/**
			 * The greater ththe operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the greater ththe operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			virtual Value* greater(const Value* other) const throw(Errors::TypeError);

			/**
			 * The greater equals operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the greater equals operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			virtual Value* greaterEqual(const Value* other) const throw(Errors::TypeError);

			/**
			 * The equals operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the equals operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			virtual Value* equal(const Value* other) const throw(Errors::TypeError);

			/**
			 * The not equals operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the not equals operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			virtual Value* notEqual(const Value* other) const throw(Errors::TypeError);

			/**
			 * The less equals operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the less equals operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			virtual Value* lessEqual(const Value* other) const throw(Errors::TypeError);

			/**
			 * The less ththe operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the less ththe operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			virtual Value* less(const Value* other) const throw(Errors::TypeError);


			/**
			 * The addition operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the addition operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			virtual Value* plus(const Value* other) const throw(Errors::TypeError);

			/**
			 * The subtraction operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the subtraction operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			virtual Value* minus(const Value* other) const throw(Errors::TypeError);

			/**
			 * The multiplication operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the multiplication operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			virtual Value* times(const Value* other) const throw(Errors::TypeError);

			/**
			 * The division operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the division operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			virtual Value* divides(const Value* other) const throw(Errors::TypeError);

			/**
			 * The modulus operation for Jump values
			 *
			 * @param other the other Value in the operation
			 *
			 * @return the result of the modulus operation
			 *
			 * @throw TypeError upon an error during the operation
			 */
			virtual Value* modulus(const Value* other) const throw(Errors::TypeError);
		};
	}
}

#endif