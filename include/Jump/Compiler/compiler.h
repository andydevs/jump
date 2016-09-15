/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _COMPILER_COMPILER_H_
#define _COMPILER_COMPILER_H_

// Headers being used
#include "Jump/statemachine.h"
#include "Jump/Errors/syntaxerror.h"

// Libraries being used
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
		 * Compiles the input into a StateMachine
		 *
		 * @param input the input to compile
		 *
		 * @return the StateMachine compiled from the input
		 *
		 * @throw SyntaxError if there is an error in the syntax of the input
		 */
		Jump::Core::StateMachine compile(std::string input) throw(Core::Errors::SyntaxError);
	}
}

#endif