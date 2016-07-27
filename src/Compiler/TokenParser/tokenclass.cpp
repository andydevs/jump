/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Compiler/TokenParser/tokenclass.h"

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
			 * Creates a TokenClass with the given name and regex
			 *
			 * @param name the name of the TokenClass
			 * @param regx the regex that matches tokens of this class
			 *			   (as a string to be compiled)
			 */
			TokenClass::TokenClass(string name, string regx) : m_name(name)
			{
				m_regex = regex(regx);
			}

			/**
			 * Creates a TokenClass with the given name and regex and ignore boolean
			 *
			 * @param name the name of the TokenClass
			 * @param regx the regex that matches tokens of this class
			 *			   (as a string to be compiled)
			 * @param ignore true if tokens of this class should be ignored
			 */
			TokenClass::TokenClass(string name, string regx, bool ignore) : m_name(name), m_ignore(ignore)
			{
				m_regex = regex(regx);
			}

			/**
			 * Copy constructor for TokenClass
			 *
			 * @param other the TokenClass to copy
			 */
			TokenClass::TokenClass(const TokenClass& other) : m_name(other.m_name), m_regex(other.m_regex) {}

			/**
			 * Destroys the TokenClass
			 */
			TokenClass::~TokenClass() {}

			/**
			 * Returns true if tokens of this class should be ignored
			 *
			 * @return true if tokens of this class should be ignored
			 */
			bool TokenClass::ignore()
			{
				return m_ignore;
			}

			/**
			 * Returns the name of the TokenClass
			 *
			 * @return the name of the TokenClass
			 */
			std::string TokenClass::name()
			{
				return m_name;
			}

			/**
			 * Returns true if the TokenClass matches a token in the given 
			 * input at the given location
			 * 
			 * @param input    the input string to check
			 * @param location the location to check
			 *
			 * @return true if the TokenClass matches a token in the given 
			 *		   input at the given location
			 */
			bool TokenClass::hasToken(string& input)
			{
				return regex_search(input, m_regex, REGEX_MATCH_CONSTANTS);
			}

			/**
			 * Returns the TokenClass matched at in the given input at the
			 * given location
			 *
			 * @param input    the input string to check
			 * @param location the location to check
			 *
			 * @return true if the TokenClass matches a token in the given 
			 *		   input at the given location
			 */
			Token TokenClass::token(string& input)
			{
				regex_search(input, m_match, m_regex, REGEX_MATCH_CONSTANTS);
				string attribute = m_match.str();
				input.erase(0, m_match.length());
				return Token(m_name, attribute);
			}
		}
	}
}