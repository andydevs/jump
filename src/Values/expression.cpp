/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Values/expression.h"
#include "Jump/Values/identifier.h"
#include "Jump/Values/null.h"
#include "Jump/state.h"
#include "Jump/statemachine.h"

// Libraries being used
#include <iostream>

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
		 * Creates an Expression with the given operation
		 *
		 * @param oper the operation order layer of the expression
		 */
		Expression::Expression(OperLayer oper): 
		Value("Expression"),
		m_layer(oper),
		m_values(),
		m_types()
		{}

		/**
		 * Copy constructor for the Expression
		 *
		 * @param other the other Expression to copy
		 */
		Expression::Expression(const Expression& other):
		Value(other),
		m_layer(other.m_layer),
		m_values(other.m_values),
		m_types(other.m_types)
		{}

		/**
		 * Destroys the Expression
		 */
		Expression::~Expression() {}

		/**
		 * Returns the string representation of the Expression
		 *
		 * @return the string representation of the Expression
		 */
		string Expression::toString() const
		{
			string str;
			switch(m_layer)
			{
				case ASSIGN:    str = "="; break;
				case OR:        str = "or"; break;
				case AND:       str = "and"; break;
				case NOT:       str = "not"; break;
				case COMPARE:   str = "<=>"; break;
				case ADDSUB:    str = "+-"; break;
				case MULDIVMOD: str = "*/%"; break;
				default:        str = "noop"; break; 
			}
			str += "(" + m_values[0]->toString();
			for (unsigned i = 1; i < m_values.size(); ++i)
				str += ", " + m_values[i]->toString();
			return str += ")";
		}

		/**
		 * Adds the value to the Expression
		 *
		 * @param value the value to add
		 */
		void Expression::add(Value* value, int type)
		{
			// Pushes the value to the array
			m_values.push_back(value);
			m_types.push_back(type);
		}

		/**
		 * Evaluates the value in the context of the given state
		 *
		 * @param stateRef a reference to the state being evaluated
		 * @param flags    flags to evauate the state with
		 *
		 * @return the evaluated value
		 */
		Value* Expression::evaluate(State* stateRef, int flags) throw(ValueError)
		{
			// Perform the operation based on the given layer
			switch(m_layer)
			{
				case ASSIGN:    return assign(stateRef, flags);
				case OR:        return orr(stateRef, flags);
				case AND:       return andd(stateRef, flags);
				case NOT:       return nott(stateRef, flags);
				case COMPARE:   return compare(stateRef, flags);
				case ADDSUB:    return addsub(stateRef, flags);
				case MULDIVMOD: return muldivmod(stateRef, flags);
				default:        return new Null();
			}
		}

		/**
		 * Assigns the left hand side to the right hand side
		 *
		 * @param stateRef reference to the state that contains the Expression
		 * @param flags    the flags that the Expression is being evaluated under
		 *
		 * @return the value to be assigned
		 */ 
		Value* Expression::assign(State* stateRef, int flags) throw(ValueError)
		{
			// If only one value in assign
			if (m_values.size() == 1)
			{
				// Evaluate value and return
				return m_values[0]->evaluate(stateRef, flags);
			}
			else
			{
				// Evaluate assigner and value
				Value* assigner = m_values[0]->evaluate(stateRef, flags | NO_EVALUATE_IDENTIFIER);
				Value* assignee = m_values[1]->evaluate(stateRef, flags);

				// Return assignment operation
				return assigner->assign(stateRef, assignee);
			}
		}

		/**
		 * Returns the orr operation of the values
		 *
		 * @param stateRef reference to the state that contains the Expression
		 *
		 * @return the orr operation of the values
		 */
		Value* Expression::orr(State* stateRef, int flags) throw(ValueError)
		{
			// Set buffer to first value
			Value* toret = m_values[0]->evaluate(stateRef, flags);

			// For each value
			for (unsigned i = 1; i < m_values.size(); ++i)
			{
				// Perform the operation
				toret = toret->orr(m_values[i]->evaluate(stateRef, flags));
			}

			// Return buffer
			return toret;
		}

		/**
		 * Returns the andd operation of the values
		 *
		 * @param stateRef reference to the state that contains the Expression
		 *
		 * @return the andd operation of the values
		 */
		Value* Expression::andd(State* stateRef, int flags) throw(ValueError)
		{
			// Set buffer to first value
			Value* toret = m_values[0]->evaluate(stateRef, flags);

			// For each value
			for (unsigned i = 1; i < m_values.size(); ++i)
			{
				// Perform the operation
				toret = toret->andd(m_values[i]->evaluate(stateRef, flags));
			}

			// Return buffer
			return toret;
		}

		/**
		 * Returns the nott operation of the values
		 *
		 * @param stateRef reference to the state that contains the Expression
		 *
		 * @return the nott operation of the values
		 */
		Value* Expression::nott(State* stateRef, int flags) throw(ValueError)
		{
			return m_values[0]->evaluate(stateRef, flags)->nott();
		}

		/**
		 * Returns the compare operation of the values
		 *
		 * @param stateRef reference to the state that contains the Expression
		 *
		 * @return the compare operation of the values
		 */
		Value* Expression::compare(State* stateRef, int flags) throw(ValueError)
		{
			// If two values are given
			if (m_values.size() == 2)
			{
				// Evaluate left and right values
				Value* left  = m_values[0]->evaluate(stateRef, flags);
				Value* right = m_values[1]->evaluate(stateRef, flags);

				// Return compare operation
				switch (m_types[1])
				{
					case 5:  return left->less(right);
					case 4:  return left->lessEqual(right);
					case 3:  return left->notEqual(right);
					case 2:  return left->equal(right);
					case 1:  return left->greaterEqual(right);
					default: return left->greater(right);
				}
			}
			else
			{
				// Return left values
				return m_values[0]->evaluate(stateRef, flags);
			}
		}

		/**
		 * Returns the addsub operation of the values
		 *
		 * @param stateRef reference to the state that contains the Expression
		 * @param flags    the flags that the Expression is being evaluated under
		 *
		 * @return the addsub operation of the values
		 */
		Value* Expression::addsub(State* stateRef, int flags) throw(ValueError)
		{
			// Set buffer to first value
			Value* toret = m_values[0]->evaluate(stateRef, flags);

			// For each value
			for (unsigned i = 1; i < m_values.size(); ++i)
			{
				// Perform the operation represented by the given type
				switch(m_types[i])
				{
					case 1: toret = toret->minus(m_values[i]->evaluate(stateRef, flags)); break;
					default: toret = toret->plus(m_values[i]->evaluate(stateRef, flags)); break;
				}
			}

			// Return buffer
			return toret;
		}

		/**
		 * Returns the muldivmod operation of the values
		 *
		 * @param stateRef reference to the state that contains the Expression
		 * @param flags    the flags that the Expression is being evaluated under
		 *
		 * @return the muldivmod operation of the values
		 */
		Value* Expression::muldivmod(State* stateRef, int flags) throw(ValueError)
		{
			// Set buffer to first value
			Value* toret = m_values[0]->evaluate(stateRef, flags);

			// For each value
			for (unsigned i = 1; i < m_values.size(); ++i)
			{
				// Perform the operation represented by the given type
				switch(m_types[i])
				{
					case 1: toret  = toret->divides(m_values[i]->evaluate(stateRef, flags)); break;
					case 2: toret  = toret->modulus(m_values[i]->evaluate(stateRef, flags)); break;
					default: toret = toret->times( m_values[i]->evaluate(stateRef, flags) ); break;
				}
			}

			// Return buffer
			return toret;
		}
	}
}