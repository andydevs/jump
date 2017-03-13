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
#include "Values/evaluate.h"

// Libraries
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
     * Parses jump code into jump objects
     *
     * @author   Anshul Kharbanda
     * @created  3 - 13 - 2017
     */
    class Interpreter {
    private:
        // ----------------------------- MATCHERS -----------------------------
        // Words
        const std::regex CONSTANT   = std::regex("\\bconst\\b");
        const std::regex VARIABLE   = std::regex("\\bstate\\b");
        const std::regex STREAM     = std::regex("\\bstream\\b");
        const std::regex PRINT      = std::regex("\\bread\\b");
        const std::regex TO         = std::regex("\\bto\\b");
        const std::regex LOOP       = std::regex("\\bloop\\b");
        const std::regex END        = std::regex("\\bend\\b");
        const std::regex IF         = std::regex("\\bif\\b");
        const std::regex OTHERWISE  = std::regex("\\botherwise\\b");
        const std::regex AND        = std::regex("\\band\\b");
        const std::regex OR         = std::regex("\\bor\\b");
        const std::regex NOT        = std::regex("\\bnot\\b");
        const std::regex BOOLEAN    = std::regex("\\b(True|False)\\b");
        const std::regex NULLVALUE  = std::regex("\\bNull\\b");
        const std::regex IDENTIFIER = std::regex("[a-zA-Z][a-zA-Z0-9_]*");

        // Values
        const std::regex STRING = std::regex(Values::STRING_REGEX);
        const std::regex NUMBER = std::regex(Values::NUMBER_REGEX);

        // Operations
        const std::regex OPERATION = std::regex("[\\*\\+-/%=!><]+");
        const std::regex LPAREN    = std::regex("\\(");
        const std::regex RPAREN    = std::regex("\\)");

        // Space
        const std::regex ENDLINE = std::regex("(#.*?)?\r?\n");
        const std::regex WSPACE  = std::regex("[ \t]+");

        // ----------------------------- VARIABLES -----------------------------

        /**
         * The last input passed to the interpreter
         */
        std::string m_input;

        /**
         * The last token recieved
         */
        std::string m_recieved;

        /**
         * Last match results
         */
        std::smatch m_matched;

        /**
         * The statemachine being built
         */
        StateMachine machine;

        /**
         * Returns true if the front supplies the given token
         *
         * @param reg represents the token being recieved
         *
         * @return true if the front supplies the given token
         */
        bool recieve(std::regex reg);

        // ----------------------------- NODES -----------------------------
        void statemachine() throw(Errors::SyntaxError);
        void constant() throw(Errors::SyntaxError);
        void variable() throw(Errors::SyntaxError);
        void stream() throw(Errors::SyntaxError);
        void state() throw(Errors::SyntaxError);
        void print() throw(Errors::SyntaxError);
        void read() throw(Errors::SyntaxError);
        void to() throw(Errors::SyntaxError);
        void end() throw(Errors::SyntaxError);
        void loop() throw(Errors::SyntaxError);
        void feed() throw(Errors::SyntaxError);
        void feedop() throw(Errors::SyntaxError);
        void orr() throw(Errors::SyntaxError);
        void orop() throw(Errors::SyntaxError);
        void andd() throw(Errors::SyntaxError);
        void andop() throw(Errors::SyntaxError);
        void nott() throw(Errors::SyntaxError);
        void compare() throw(Errors::SyntaxError);
        void addsub() throw(Errors::SyntaxError);
        void addsubOp() throw(Errors::SyntaxError);
        void muldivmod() throw(Errors::SyntaxError);
        void muldivmodOp() throw(Errors::SyntaxError);
        void value() throw(Errors::SyntaxError);
    public:
        /**
         * Constructor for Interpreter
         */
        Interpreter() {}

        /**
         * Destructor for interpreter
         */
        ~Interpreter() {}

        /**
         * Interprets the string input as jump code and returns a StateMachine
         *
         * @param input the jump code to interpret
         *
         * @return the parsed StateMachine
         *
         * @throws SyntaxError if input is invalid jump code
         */
        StateMachine interpret(std::string input) throw(Errors::SyntaxError);
    };
}

#endif
