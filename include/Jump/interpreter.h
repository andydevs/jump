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
#include <string>

/**
 * Jump is a new programming language that uses the state machine paradigm
 *
 * @author  Anshul Kharbanda
 * @created 7 - 15 - 2016
 */
namespace Jump
{
    /**
     * Parses jump code into jump objects
     *
     * @author   Anshul Kharbanda
     * @created  3 - 13 - 2017
     */
    namespace Interpreter {
        // ---------------------------- PARSE FLAGS ----------------------------
        // Prints debug messages
        const int DEBUG = 1;

        /**
         * Interprets the string input as jump code and returns a StateMachine
         *
         * @param input the jump code to interpret
         * @param flags parse flags
         *
         * @return the parsed StateMachine
         *
         * @throws SyntaxError if input is invalid jump code
         */
        StateMachine interpret(std::string input, int flags) throw(Errors::SyntaxError);
    }
}

#endif
