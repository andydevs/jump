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
        /**
         * Regex match constants
         */
        const std::regex_constants::match_flag_type REGEX_MATCH_CONSTANTS
            = std::regex_constants::match_continuous;

        // ----------------------------- MATCHERS -----------------------------
        // Keywords
        const std::regex CONSTANT   = std::regex("\\bconst\\b");
        const std::regex VARIABLE   = std::regex("\\bstate\\b");
        const std::regex STREAM     = std::regex("\\bstream\\b");
        const std::regex STATE      = std::regex("\\bstate\\b");
        const std::regex READ       = std::regex("\\bread\\b");
        const std::regex PRINT      = std::regex("\\bprint\\b");
        const std::regex TO         = std::regex("\\bto\\b");
        const std::regex LOOP       = std::regex("\\bloop\\b");
        const std::regex END        = std::regex("\\bend\\b");
        const std::regex IF         = std::regex("\\bif\\b");
        const std::regex OTHERWISE  = std::regex("\\botherwise\\b");
        const std::regex AND        = std::regex("\\band\\b");
        const std::regex OR         = std::regex("\\bor\\b");
        const std::regex NOT        = std::regex("\\bnot\\b");

        // Values
        const std::regex STRING     = std::regex(Values::STRING_REGEX);
        const std::regex NUMBER     = std::regex(Values::NUMBER_REGEX);
        const std::regex BOOLEAN    = std::regex("\\b(True|False)\\b");
        const std::regex NULLVALUE  = std::regex("\\bNull\\b");
        const std::regex IDENTIFIER = std::regex("[a-zA-Z][a-zA-Z0-9_]*");

        // StreamTypes
        const std::regex ARRAYSTREAM = std::regex("ArrayStream");

        // Operations
        const std::regex ASSIGN  = std::regex("=");
        const std::regex PIPE    = std::regex("->");
        const std::regex GREATER = std::regex(">");
        const std::regex GREATEQ = std::regex(">=");
        const std::regex EQUAL   = std::regex("==");
        const std::regex NEQUAL  = std::regex("!=");
        const std::regex LESSEQ  = std::regex("<=");
        const std::regex LESS    = std::regex("<");
        const std::regex ADD     = std::regex("+");
        const std::regex SUB     = std::regex("-");
        const std::regex MUL     = std::regex("*");
        const std::regex DIV     = std::regex("/");
        const std::regex MOD     = std::regex("%");
        const std::regex LPAREN  = std::regex("\\(");
        const std::regex RPAREN  = std::regex("\\)");

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
         * The statemachine being built
         */
        StateMachine m_machine;

        /**
         * The state being built
         */
        State* m_state;

        /**
         * Returns a SyntaxError which descries unexpected token
         *
         * @param exp the expected value
         *
         * @return SyntaxError which describes unexpected
         */
        Errors::SyntaxError unexpected(std::string exp);

        /**
         * Returns the last recieved token
         *
         * @return the last recieved token
         */
        std::string recieved();

        /**
         * Returns true if the string is at end
         *
         * @return true if the string is at end
         */
        bool atEnd();

        /**
         * Returns true if the front can supply the given token (without supplying it)
         *
         * @param reg represents the token being recieved
         *
         * @return true if the front can supply the given token
         */
        bool percieve(std::regex reg);

        /**
         * Returns true if the front supplies the given token
         *
         * @param reg represents the token being recieved
         *
         * @return true if the front supplies the given token
         */
        bool recieve(std::regex reg);

        /**
         * Asserts that the given token appears next in the input
         *
         * @param reg represents the token being recieved
         * @param exp the string to print in SyntaxError, identifying what was expected
         *
         * @throw SyntaxError if token is not found
         */
        void require(std::regex reg, std::string exp) throw(Errors::SyntaxError);

        /**
         * Returns a peek at the first 5 characters of the input
         *
         * @return a peek at the first 5 characters of the input
         */
        std::string peek();

        // ------------------------------- NODES -------------------------------
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
        // ---------------------------- EXPRESSION -----------------------------
        Values::Value* feed() throw(Errors::SyntaxError);
        Values::Value* orr() throw(Errors::SyntaxError);
        Values::Value* andd() throw(Errors::SyntaxError);
        Values::Value* nott() throw(Errors::SyntaxError);
        Values::Value* compare() throw(Errors::SyntaxError);
        Values::Value* addsub() throw(Errors::SyntaxError);
        Values::Value* muldivmod() throw(Errors::SyntaxError);
        Values::Value* value() throw(Errors::SyntaxError);
    public:
        /**
         * Constructor for Interpreter
         */
        Interpreter();

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
