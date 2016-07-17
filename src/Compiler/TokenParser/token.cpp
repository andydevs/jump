//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Compiler/TokenParser/token.h"

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
	 * Compiles a Jump script
	 *
	 * @author  Anshul Kharbanda
	 * @created 7 - 17 - 2016
	 */
	namespace Compiler
	{
		/**
		 * Parses tokens
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 17 - 2016
		 */
		namespace TokenParser
		{
			/**
			 * Creates a token with the given klass and attribute values
			 *
			 * @param klass     the class of the Token
			 * @param attribute the attribute of the Token
			 */
			Token::Token(string klass, string attribute) : m_klass(klass), m_attribute(attribute) {}

			/**
			 * Copy constructor for Token
			 *
			 * @param other the Token to copy
			 */
			Token::Token(const Token& other) : m_klass(other.m_klass), m_attribute(other.m_attribute) {}

			/**
			 * Destroys the token
			 */
			Token::~Token() {}

			/**
			 * Returns the string representation of the token
			 */
			string Token::toString() const
			{
				string s = "<" + m_klass + "-\"";
				for (int i = 0; i < m_attribute.length(); ++i)
				{
					switch (m_attribute[i])
					{
						case '\n':
							s += "\\n";
							break;
						case '\r':
							s += "\\r";
							break;
						case '\t':
							s += "\\t";
							break;
						case '\f':
							s += "\\f";
							break;
						default:
							s += m_attribute[i];
							break;
					}
				}
				return s + "\">";
			}

			/**
			 * Operator for passing token to output stream
			 *
			 * @param out the output stream to write to
			 * @param tk  the token to write
			 *
			 * @return the output stream that was written to
			 */
			ostream& operator<<(ostream& out, const Token& other)
			{
				return out << other.toString();
			}
		}
	}
}