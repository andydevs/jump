/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_VALUES_EXPRESSION_H_
#define _CORE_VALUES_EXPRESSION_H_

// Headers being used
#include "value.h"

// Libraries being used
#include <string>
#include <vector>

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
		 * The operation order layer of the expression
		 *
		 * @author  Anshul Kharbanda
		 * @created 9 - 1 - 2016
		 */
		 enum OperLayer
		 {
		 	ASSIGN,
		 	OR,
		 	AND,
		 	NOT,
		 	COMPARE,
		 	ADDSUB,
		 	MULDIVMOD
		 };

		/**
		 * Represents an expression in Jump
		 *
		 * @author  Anshul Kharbanda
		 * @created 9 - 1 - 2016
		 */
		class Expression : public Value
		{
		private:
			/**
			 * The operation order layer of the expression
			 */
			OperLayer m_layer;

			/**
			 * The values to operate on
			 */
			std::vector<Value*> m_values;

			/**
			 * The operation types
			 */
			std::vector<int> m_types;

			/**
			 * Assigns the left hand side to the right hand side
			 *
			 * @param stateRef reference to the state that contains the Expression
			 *
			 * @return the value to be assigned
			 */ 
			Value* assign(State* stateRef, int flags) throw(Errors::ValueError);

			/**
			 * Returns the orr operation of the values
			 *
			 * @param stateRef reference to the state that contains the Expression
			 *
			 * @return the orr operation of the values
			 */
			Value* orr(State* stateRef, int flags) throw(Errors::ValueError);

			/**
			 * Returns the andd operation of the values
			 *
			 * @param stateRef reference to the state that contains the Expression
			 *
			 * @return the andd operation of the values
			 */
			Value* andd(State* stateRef, int flags) throw(Errors::ValueError);

			/**
			 * Returns the nott operation of the values
			 *
			 * @param stateRef reference to the state that contains the Expression
			 *
			 * @return the nott operation of the values
			 */
			Value* nott(State* stateRef, int flags) throw(Errors::ValueError);

			/**
			 * Returns the compare operation of the values
			 *
			 * @param stateRef reference to the state that contains the Expression
			 *
			 * @return the compare operation of the values
			 */
			Value* compare(State* stateRef, int flags) throw(Errors::ValueError);

			/**
			 * Returns the addsub operation of the values
			 *
			 * @param stateRef reference to the state that contains the Expression
			 *
			 * @return the addsub operation of the values
			 */
			Value* addsub(State* stateRef, int flags) throw(Errors::ValueError);

			/**
			 * Returns the muldivmod operation of the values
			 *
			 * @param stateRef reference to the state that contains the Expression 
			 *
			 * @return the muldivmod operation of the values
			 */
			Value* muldivmod(State* stateRef, int flags) throw(Errors::ValueError);
		public:
			/**
			 * Creates an Expression with the given operation
			 *
			 * @param oper the operation order layer of the expression
			 */
			Expression(OperLayer oper);

			/**
			 * Copy constructor for the Expression
			 *
			 * @param other the other Expression to copy
			 */
			Expression(const Expression& other);

			/**
			 * Destroys the Expression
			 */
			~Expression();

			/**
			 * Returns the string representation of the Expression
			 *
			 * @return the string representation of the Expression
			 */
			std::string toString() const;

			/**
			 * Adds the value to the Expression
			 *
			 * @param value the value to add
			 */
			void add(Value* value, int type);

			/**
			 * Evaluates the value in the context of the given state
			 *
			 * @param stateRef a reference to the state being evaluated
			 * @param flags    flags to evauate the state with
			 *
			 * @return the evaluated value
			 */
			Value* evaluate(State* stateRef, int flags) throw(Errors::ValueError);
		};
	}
}

#endif