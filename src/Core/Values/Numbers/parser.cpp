/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Core/Values/Numbers/parser.h"
#include "Jump/Core/Values/Numbers/integer.h"
#include "Jump/Core/Values/Numbers/float.h"

// Libraries being used
#include <cstdlib>

// Namespaces being used
using namespace std;
using namespace Jump::Core::Errors;

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
				 * Returns the suffix for a given integer match
				 *
				 * @param match the match results from a successful regex match on an integer
				 *
				 * @return the suffix for a given integer match
				 */
				static string suffix(smatch match)
				{
					if (!match[2].str().empty())
						if (match[2].str() == "i")
							return DEFAULT_INTEGER_SUFFIX;
						else if (match[2].str() == "f")
							return DEFAULT_FLOAT_SUFFIX;
						else
							return match[2].str();
					else
						if (!match[1].str().empty() || DEFAULT_IS_FLOAT)
							return DEFAULT_FLOAT_SUFFIX;
						else
							return DEFAULT_INTEGER_SUFFIX;
				}

				/**
				 * Parses the given text into a number
				 *
				 * @param text the text to parse
				 *
				 * @return the number parsed from the text
				 */
				Value* parse(string text) throw(TypeError)
				{
					// Get match
					smatch match;
					regex_match(text, match, NUMBER_REGEX);

					if (suffix(match) == "i8")
						return new Integer<char>((char)atoi(text.c_str()));
					else if (suffix(match) == "i16")
						return new Integer<short>((short)atoi(text.c_str()));
					else if (suffix(match) == "i32")
						return new Integer<int>((int)atoi(text.c_str()));
					else if (suffix(match) == "i64")
						return new Integer<long>((long)atoi(text.c_str()));
					else if (suffix(match) == "f32")
						return new Float<float>((float)atof(text.c_str()));
					else if (suffix(match) == "f64")
						return new Float<double>((double)atof(text.c_str()));
					else
						throw TypeError("Undefined numerical type: " + suffix(match));
				}
			}
		}
	}
}