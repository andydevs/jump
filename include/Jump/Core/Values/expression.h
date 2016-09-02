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
			 * The operation order layer of the expression
			 *
			 * @author  Anshul Kharbanda
			 * @created 9 - 1 - 2016
			 */
			 enum OperLayer
			 {
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
				 * Returns the addsub operation of the values
				 *
				 * @return the addsub operation of the values
				 */
				Value* addsub();

				/**
				 * Returns the muldivmod operation of the values
				 *
				 * @return the muldivmod operation of the values
				 */
				Value* muldivmod();
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
				 * Adds the value to the Expression
				 *
				 * @param value the value to add
				 */
				void add(Value* value, int type);

				/**
				 * Evaluates the value
				 *
				 * @return the evaluated value
				 */
				Value* evaluate();

				/**
				 * Returns the string representation of the Value
				 *
				 * @return the string representation of the Value
				 */
				std::string toString() const;
			};
		}
	}
}

#endif