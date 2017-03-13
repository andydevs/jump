/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

// Includes
#include "statemachine.h"
#include "Errors/syntaxerror.h"

// Libraries
#include <string.h>

/**
 * Jump is a new programming language that uses the state machine paradigm
 *
 * @author  Anshul Kharbanda
 * @created 7 - 15 - 2016
 */
namespace Jump
{
    /**
     * Interprets the string input as jump code and returns a StateMachine
     *
     * @param input the jump code to interpret
     *
     * @return the parsed StateMachine
     *
     * @throws SyntaxError if input is invalid jump code
     */
    StateMachine interpret(std::string input) throws Errors::SyntaxError;
}

#endif
