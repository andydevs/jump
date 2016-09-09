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
#include <string>

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
							default:  return DEFAULT_INTEGER_SUFFIX;
						}
					}
				}

				/** 
				 * Returns the type represented by the given suffix
				 *
				 * @param suffix the suffix being processed
				 *
				 * @return the type represented by the given suffix
				 */
				static char type(string suffix)
				{
					return suffix[0];
				}

				/** 
				 * Returns the bit length represented by the given suffix
				 *
				 * @param suffix the suffix being processed
				 *
				 * @return the bit length represented by the given suffix
				 */
				static char bitLength(string suffix)
				{
					return stoi(suffix.substr(1, 2));
				}

				/** 
				 * Throws a type error with the undefined suffix
				 *
				 * @param suffix the suffix being processed
				 *
				 * @throw TypeError with the undefined suffix
				 */
				static void undefined(string suffix) throw(TypeError)
				{
					throw TypeError("Undefined numerical suffix: " + suffix);
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
					// Determine numerical type based on suffix
					string suffix = getSuffix(text);
					switch(type(suffix))
					{
						// Integer suffix
						case 'i':
							switch(bitLength(suffix))
							{
								// Integer types
								case 8:  return new Int8((char)stoi(text));
								case 16: return new Int16((short)stoi(text));
								case 32: return new Int32(stoi(text));
								case 64: return new Int64(stol(text));

								// Undefined integer length
								default: undefined(suffix);
							}
							break;

						// Float suffix
						case 'f':
							switch(bitLength(suffix))
							{
								// Float types
								case 32: return new Float32(stof(text));
								case 64: return new Float64(stod(text));

								// Undefined float type
								default: undefined(suffix);
							}
							break;

						// Undefined suffix
						default: undefined(suffix);
					}
				}
			}
		}
	}
}