/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Values/expression.h"
#include "Jump/Core/Values/null.h"

// Libraries being used
#include <iostream>

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
			 * Adds the value to the Expression
			 *
			 * @param value the value to add
			 */
			void Expression::add(Value* value, int type)
			{
				m_values.push_back(value);
				m_types.push_back(type);
			}

			/**
			 * Returns the string representation of the Value
			 *
			 * @return the string representation of the Value
			 */
			string Expression::toString() const
			{
				string str = "";
				switch(m_layer)
				{
					case ADDSUB: str += "addsub"; break;
					case MULDIVMOD: str += "muldivmod"; break;
					default: str += "noop"; break;
				}
				str += "(" + m_values[0]->toString();
				for (unsigned i = 1; i < m_values.size(); ++i)
				{
					str += ", " + m_values[i]->toString();
				}
				return str + ")";
			}

			/**
			 * Evaluates the value
			 *
			 * @return the evaluated value
			 */
			Value* Expression::evaluate()
			{
				switch(m_layer)
				{
					case ADDSUB: return addsub();
					case MULDIVMOD: return muldivmod();
					default: return new Null();
				}
			}

			/**
			 * Returns the addsub operation of the values
			 *
			 * @return the addsub operation of the values
			 */
			Value* Expression::addsub()
			{
				Value* toret = m_values[0]->evaluate();
				for (unsigned i = 1; i < m_values.size(); ++i)
				{
					switch(m_types[i])
					{
						case 1: toret = toret->minus(m_values[i]->evaluate()); break;
						default: toret = toret->plus(m_values[i]->evaluate()); break;
					}
				}
				return toret;
			}

			/**
			 * Returns the muldivmod operation of the values
			 *
			 * @return the muldivmod operation of the values
			 */
			Value* Expression::muldivmod()
			{
				Value* toret = m_values[0]->evaluate();
				for (unsigned i = 1; i < m_values.size(); ++i)
				{
					switch(m_types[i])
					{
						case 1: toret = toret->divides(m_values[i]->evaluate()); break;
						case 2: toret = toret->modulus(m_values[i]->evaluate()); break;
						default: toret = toret->times(m_values[i]->evaluate()); break;
					}
				}
				return toret;
			}
		}
	}
}