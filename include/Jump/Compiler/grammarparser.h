//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

#ifndef _COMPILER_GRAMMARPARSER_H_
#define _COMPILER_GRAMMARPARSER_H_

// Headers being used
#include "TokenParser/parser.h"
#include "Jump/Core/statemachine.h"

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
		 * Performs grammar analysis on a token queue
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 18 - 2016
		 */
		namespace GrammarParser
		{
			/**
			 * Parses the given token queue into the given StateMachine
			 *
			 * @param machine the StateMachine to be parsed
			 * @param tks     the tokens to parse into the StateMachine
			 *
			 * @return status code of parse
			 */
			int parse(Jump::Core::StateMachine& machine, std::queue<Jump::Compiler::TokenParser::Token>& tks);
		}
	}
}

#endif