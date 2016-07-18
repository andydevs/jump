//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Compiler/TokenParser/tokenclass.h"

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
			 * Returns true if the TokenClass matches a token in the given 
			 * input at the given location
			 * 
			 * @param input    the input string to check
			 * @param location the location to check
			 *
			 * @return true if the TokenClass matches a token in the given 
			 *		   input at the given location
			 */
			bool TokenClass::hasToken(string& input, int location)
			{
				string sub = input.substr(location);
				return regex_search(sub, m_regex, REGEX_MATCH_CONSTANTS);
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
			Token TokenClass::token(string& input, int& location)
			{
				string sub = input.substr(location);
				regex_search(sub, m_match, m_regex, REGEX_MATCH_CONSTANTS);
				location += m_match.length(0);
				return Token(m_name, m_match.str());
			}
		}
	}
}