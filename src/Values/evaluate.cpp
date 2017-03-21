/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Values/evaluate.h"
#include "Jump/Values/null.h"
#include "Jump/Values/string.h"
#include "Jump/Values/boolean.h"
#include "Jump/Values/Numbers/unsignedinteger.h"
#include "Jump/Values/Numbers/integer.h"
#include "Jump/Values/Numbers/float.h"

// Namespaces being used
using namespace std;
using namespace Jump::Errors;
using namespace Jump::Values::Numbers;

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
		 * Returns the suffix for a given integer match
		 *
		 * @param match the match results from a successful regex match on an integer
		 *
		 * @return the suffix for a given integer match
		 */
		static string getSuffix(string text)
		{
			smatch match;
			regex_match(text, match, NUMBER_REGEX);
			if (!match[2].str().empty())
			{
				if (match[2].str() == "i")
					return DEFAULT_INTEGER_SUFFIX;
				else if (match[2].str() == "f")
					return DEFAULT_FLOAT_SUFFIX;
				else if (match[2].str() == "u")
					return DEFAULT_UNSIGNED_SUFFIX;
				else
					return match[2].str();
			}
			else if (!match[1].str().empty())
			{
				return DEFAULT_FLOAT_SUFFIX;
			}
			else
			{
				switch (DEFAULT_NUMBER_TYPE)
				{
					case 'f': return DEFAULT_FLOAT_SUFFIX;
					case 'u': return DEFAULT_UNSIGNED_SUFFIX;
					default:  return DEFAULT_INTEGER_SUFFIX;
				}
			}
		}

		/**
		 * Parses the given text into a number
		 *
		 * @param text the text to parse
		 *
		 * @return the number parsed from the text
		 */
		Value* number(string text) throw(SyntaxError)
		{
			// Determine numerical info based on suffix
			string suffix  = getSuffix(text);
			char type      = suffix[0];
			char bitLength = (char)stoi(suffix.substr(1, 2));
			string invalid = "Invalid numerical suffix: " + suffix;

			// Switch type
			switch(type)
			{
				// Integer suffix
				case 'i':
					switch(bitLength)
					{
						// Integer types
						case 8:  return new Int8((char)stoi(text));
						case 16: return new Int16((short)stoi(text));
						case 32: return new Int32(stoi(text));
						case 64: return new Int64(stol(text));

						// Undefined Integer length
						default: throw SyntaxError(invalid);
					}
					// Undefined Integer length
					throw SyntaxError(invalid);

				// Unsigned Integer suffix
				case 'u':
					switch(bitLength)
					{
						// Unsigned Integer types
						case 8:  return new UInt8((char)stoi(text));
						case 16: return new UInt16((short)stoi(text));
						case 32: return new UInt32(stoi(text));
						case 64: return new UInt64(stol(text));

						// Undefined Unsigned Integer length
						default: throw SyntaxError(invalid);
					}
					// Undefined Unsigned Integer length
					throw SyntaxError(invalid);

				// Float suffix
				case 'f':
					switch(bitLength)
					{
						// Float types
						case 32: return new Float32(stof(text));
						case 64: return new Float64(stod(text));

						// Undefined Float length
						default: throw SyntaxError(invalid);
					}
					// Undefined Float length
					throw SyntaxError(invalid);

				// Undefined suffix
				default: throw SyntaxError(invalid);
			}
		}

		/**
		 * Evaluates the given input string as a value
		 *
		 * @param input the input string
		 *
		 * @return the input string evaluates as a value
		 */
		Value* evaluate(string input) throw(SyntaxError)
		{
			if (regex_match(input, BOOLEAN_REGEX))
				return new Boolean(input == "True");
			else if (regex_match(input, NULL_REGEX))
				return new Null();
			else if (regex_match(input, NUMBER_REGEX))
				return number(input);
			else if (regex_match(input, STRING_REGEX))
				return new String(input.substr(1, input.length() - 2));
			else if (regex_match(input, TEXT_REGEX))
				return new String(input);
			else
				throw SyntaxError("Invalid value syntax: " + input);
		}
	}
}
