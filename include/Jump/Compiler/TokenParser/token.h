/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _COMPILER_TOKENPARSER_TOKEN_H_
#define _COMPILER_TOKENPARSER_TOKEN_H_

// Libraries being used
#include <string>
#include <iostream>

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
			 * A Jump language token
			 *
			 * @author  Anshul Kharbanda
			 * @created 7 - 17 - 2016
			 */
			struct Token
			{
				/**
				 * The class of the Token
				 */
				std::string m_klass;

				/**
				 * The attribute of the Token
				 */
				std::string m_attribute;

				/**
				 * Creates an empty token
				 */
				Token();

				/**
				 * Creates a token with the given klass and attribute values
				 *
				 * @param klass     the class of the Token
				 * @param attribute the attribute of the Token
				 */
				Token(std::string klass, std::string attribute);

				/**
				 * Copy constructor for Token
				 *
				 * @param other the Token to copy
				 */
				Token(const Token& other);

				/**
				 * Destroys the token
				 */
				~Token();

				/**
				 * Returns the class of the Token
				 *
				 * @return the class of the Token
				 */
				std::string klass() const;

				/**
				 * Returns the attribute of the Token
				 *
				 * @return the attribute of the Token
				 */
				std::string attribute() const;

				/**
				 * Returns the string representation of the Token
				 *
				 * @return the string representation of the Token
				 */
				std::string toString() const;

				/**
				 * Returns true if the given Token equals the other Token
				 *
				 * @return true if the given Token equals the other Token
				 */
				bool operator==(const Token& other) const;

				/**
				 * Returns true if the given Token does not equal the other Token
				 *
				 * @return true if the given Token does not equal the other Token
				 */
				bool operator!=(const Token& other) const;

				/**
				 * Operator for passing token to output stream
				 *
				 * @param out the output stream to write to
				 * @param tk  the token to write
				 *
				 * @return the output stream that was written to
				 */
				friend std::ostream& operator<<(std::ostream& out, const Token& tk);
			};
		}
	}
}

#endif