//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

#ifndef _COMPILER_TOKENPARSER_TOKENCLASS_H_
#define _COMPILER_TOKENPARSER_TOKENCLASS_H_

// Headers being used
#include "token.h"

// Libraries being used
#include <string>
#include <regex>

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
			 * Regex match constants
			 */
			const std::regex_constants::match_flag_type REGEX_MATCH_CONSTANTS 
				= std::regex_constants::match_continuous;

			/**
			 * Represents a class of tokens
			 *
			 * @author  Anshul Kharbanda
			 * @created 7 - 18 - 2016
			 */
			class TokenClass
			{
			private:
				/**
				 * The name of the class
				 */
				std::string m_name;

				/**
				 * The regex that matches tokens of this class
				 */
				std::regex m_regex;

				/**
				 * Holds the match made by the token method
				 */
				std::smatch m_match;
			public:
				/**
				 * Creates a TokenClass with the given name and regex
				 *
				 * @param name the name of the TokenClass
				 * @param regx the regex that matches tokens of this class
				 *			   (as a string to be compiled)
				 */
				TokenClass(std::string name, std::string regx);

				/**
				 * Copy constructor for TokenClass
				 *
				 * @param other the TokenClass to copy
				 */
				TokenClass(const TokenClass& other);

				/**
				 * Destroys the TokenClass
				 */
				~TokenClass();

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
				bool hasToken(std::string& input, int location);

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
				Token token(std::string& input, int& location);
			};
		}
	}
}

#endif