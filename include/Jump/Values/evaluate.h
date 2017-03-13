/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _CORE_VALUES_EVALUATE_H_
#define _CORE_VALUES_EVALUATE_H_

// Headers being used
#include "Jump/value.h"
#include "Jump/Errors/syntaxerror.h"

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
	 * Contains the value types for Jump
	 *
	 * @author  Anshul Kharbanda
	 * @created 7 - 27 - 2016
	 */
	namespace Values
	{
		/**
		 * The number regex
		 */
		const std::regex NUMBER_REGEX("[0-9]+((?:\\.[0-9]+)?(?:(?:e|E)(?:\\+|\\-)?[0-9]+)?)([uif][0-9]*)?");

		/**
		 * The boolean regex
		 */
		const std::regex BOOLEAN_REGEX("True|False");

		/**
		 * Null regex
		 */
		const std::regex NULL_REGEX("Null");

		/**
		 * The string regex
		 */
		const std::regex STRING_REGEX("(\"|').*?\\1");

		/**
		 * Basic text regex
		 */
		const std::regex TEXT_REGEX(".*?");

		/**
		 * Default number type
		 */
		const char DEFAULT_NUMBER_TYPE = 'i';

		/**
		 * Default suffix for Integers
		 */
		const std::string DEFAULT_INTEGER_SUFFIX  = "i32";

		/**
		 * Default suffix for Unsigned Integers
		 */
		const std::string DEFAULT_UNSIGNED_SUFFIX = "u32";

		/**
		 * Default suffix for Floats
		 */
		const std::string DEFAULT_FLOAT_SUFFIX    = "f64";

		/**
		 * Evaluates the given input string as a value
		 *
		 * @param input the input string
		 *
		 * @return the input string evaluates as a value
		 */
		Value* evaluate(std::string input) throw(Errors::SyntaxError);
	}
}

#endif