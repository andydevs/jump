/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Values/value.h"

// Libraries being used
#include <string>
#include <regex>

#ifndef _CORE_VALUES_NUMBERS_PARSER_H_
#define _CORE_VALUES_NUMBERS_PARSER_H_

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
			 * Contains the number types for Jump
			 *
			 * @author  Anshul Kharbanda
			 * @created 7 - 30 - 2016
			 */
			namespace Numbers
			{
				/**
				 * The regex for matching numbers
				 */
				const std::regex NUMBER_REGEX("[0-9]+((?:\\.[0-9]+)?(?:(?:e|E)(?:\\+|\\-)?[0-9]+)?)([if][0-9]*)?");

				/**
				 * Default number type
				 */
				const char DEFAULT_NUMBER_TYPE = 'i';

				/**
				 * Default suffix for Integers
				 */
				const std::string DEFAULT_INTEGER_SUFFIX = "i32";

				/**
				 * Default suffix for Floats
				 */
				const std::string DEFAULT_FLOAT_SUFFIX = "f64";

				/**
				 * Parses the given text into a number
				 *
				 * @param text the text to parse
				 *
				 * @return the number parsed from the text
				 */
				Value* parse(std::string text) throw(Jump::Core::Errors::TypeError);
			}
		}
	}
}

#endif