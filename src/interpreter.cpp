/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/interpreter.h"
#include "Jump/Statements/print.h"
#include "Jump/Statements/read.h"
#include "Jump/Statements/loop.h"
#include "Jump/Statements/end.h"
#include "Jump/Statements/to.h"
#include "Jump/Values/string.h"
#include "Jump/Values/null.h"
#include "Jump/Values/boolean.h"
#include "Jump/Values/identifier.h"
#include "Jump/Values/expression.h"
#include "Jump/Values/Numbers/unsignedinteger.h"
#include "Jump/Values/Numbers/integer.h"
#include "Jump/Values/Numbers/float.h"
#include "Jump/Values/evaluate.h"
#include "Jump/Streams/printstream.h"
#include "Jump/Streams/readstream.h"
#include "Jump/Streams/arraystream.h"
#include "Jump/Errors/syntaxerror.h"

// Libraries being used
#include <cstdlib>
#include <string>
#include <iostream>

// Namespaces being used
using namespace std;
using namespace Jump::Statements;
using namespace Jump::Values;
using namespace Jump::Streams;
using namespace Jump::Errors;

/**
 * Jump is a new programming language that uses the state machine paradigm
 *
 * @author  Anshul Kharbanda
 * @created 7 - 15 - 2016
 */
namespace Jump {
    /**
     * Parses jump code into jump objects
     *
     * @author   Anshul Kharbanda
     * @created  3 - 13 - 2017
     */
    namespace Interpreter {
        /**
         * Regex match constants
         */
        const regex_constants::match_flag_type REGEX_MATCH_CONSTANTS
            = regex_constants::match_continuous;

        // ----------------------------- MATCHERS -----------------------------
        // Keywords
        static const regex OTHERWISE = regex("\\botherwise\\b");
        static const regex CONSTANT  = regex("\\bconst\\b");
        static const regex VARIABLE  = regex("\\bvar\\b");
        static const regex STREAM    = regex("\\bstream\\b");
        static const regex STATE     = regex("\\bstate\\b");
        static const regex READ      = regex("\\bread\\b");
        static const regex PRINT     = regex("\\bprint\\b");
        static const regex TO        = regex("\\bto\\b");
        static const regex FROM      = regex("\\bfrom\\b");
        static const regex LOOP      = regex("\\bloop\\b");
        static const regex END       = regex("\\bend\\b");
        static const regex IF        = regex("\\bif\\b");
        static const regex AND       = regex("\\band\\b");
        static const regex OR        = regex("\\bor\\b");
        static const regex NOT       = regex("\\bnot\\b");

        // Values
        static const regex STRING     = regex(Values::STRING_REGEX);
        static const regex NUMBER     = regex(Values::NUMBER_REGEX);
        static const regex BOOLEAN    = regex("\\b(True|False)\\b");
        static const regex NULLVALUE  = regex("\\bNull\\b");
        static const regex IDENTIFIER = regex("[a-zA-Z][a-zA-Z0-9_]*");

        // StreamTypes
        static const regex ARRAYSTREAM = regex("ArrayStream");

        // Operations
        static const regex ASSIGN    = regex("=");
        static const regex GREATER   = regex(">");
        static const regex GREATEQ   = regex(">=");
        static const regex EQUAL     = regex("==");
        static const regex NEQUAL    = regex("!=");
        static const regex LESSEQ    = regex("<=");
        static const regex LESS      = regex("<");
        static const regex ADD       = regex("\\+");
        static const regex SUB       = regex("-");
        static const regex MUL       = regex("\\*");
        static const regex DIV       = regex("\\/");
        static const regex MOD       = regex("%");
        static const regex INCREMENT = regex("\\+\\+");
        static const regex DECREMENT = regex("\\-\\-");
        static const regex LPAREN    = regex("\\(");
        static const regex RPAREN    = regex("\\)");

        // Space
        static const regex ENDLINE = regex("(#.*?)?\r?\n");
        static const regex WSPACE  = regex("[ \t]+");

        // ----------------------------- VARIABLES -----------------------------

        /**
         * The last input passed to the interpreter
         */
        static string s_input;

        /**
         * The last token recieved
         */
        static string s_recieved;

        /**
         * The statemachine being built
         */
        static StateMachine* s_machine;

        /**
         * The state being built
         */
        static State* s_state;

        // -------------------------- PRIVATE FUNCTIONS ------------------------

        /**
         * Checks a single flag in the flag buffer
         *
         * @param flags the flag buffer
         * @param flag  the flag to check
         *
         * @return true if the flag is on
         */
        static bool flag(int flags, int flag);

        /**
         * Prints a debug message
         *
         * @param flags   flag buffer
         * @param message the message to print
         */
        static void debug(int flags, string message);

        /**
         * Returns a SyntaxError which descries unexpected token
         *
         * @param exp the expected value
         *
         * @return SyntaxError which describes unexpected
         */
        static Errors::SyntaxError unexpected(string exp);

        /**
         * Returns the last recieved token
         *
         * @return the last recieved token
         */
        static string recieved();

        /**
         * Returns true if the string is at end
         *
         * @return true if the string is at end
         */
        static bool atEnd();

        /**
         * Returns true if the front can supply the given token (without supplying it)
         *
         * @param reg represents the token being recieved
         *
         * @return true if the front can supply the given token
         */
        static bool percieve(regex reg);

        /**
         * Returns true if the front supplies the given token
         *
         * @param reg represents the token being recieved
         *
         * @return true if the front supplies the given token
         */
        static bool recieve(regex reg);

        /**
         * Asserts that the given token appears next in the input
         *
         * @param reg represents the token being recieved
         * @param exp the string to print in SyntaxError, identifying what was expected
         *
         * @throw SyntaxError if token is not found
         */
        static void require(regex reg, string exp) throw(Errors::SyntaxError);

        /**
         * Returns a peek at the first 5 characters of the input
         *
         * @return a peek at the first 5 characters of the input
         */
        static string peek();

        // ------------------------------- NODES -------------------------------
        static void statemachine(int flags) throw(Errors::SyntaxError);
        static void constant(int flags) throw(Errors::SyntaxError);
        static void variable(int flags) throw(Errors::SyntaxError);
        static void stream(int flags) throw(Errors::SyntaxError);
        static void state(int flags) throw(Errors::SyntaxError);
        static void print(int flags) throw(Errors::SyntaxError);
        static void read(int flags) throw(Errors::SyntaxError);
        static void to(int flags) throw(Errors::SyntaxError);
        static void end(int flags) throw(Errors::SyntaxError);
        static void loop(int flags) throw(Errors::SyntaxError);
        // ---------------------------- EXPRESSION -----------------------------
        static Values::Value* feed(int flags) throw(Errors::SyntaxError);
        static Values::Value* orr(int flags) throw(Errors::SyntaxError);
        static Values::Value* andd(int flags) throw(Errors::SyntaxError);
        static Values::Value* nott(int flags) throw(Errors::SyntaxError);
        static Values::Value* compare(int flags) throw(Errors::SyntaxError);
        static Values::Value* addsub(int flags) throw(Errors::SyntaxError);
        static Values::Value* muldivmod(int flags) throw(Errors::SyntaxError);
        static Values::Value* value(int flags) throw(Errors::SyntaxError);

        // --------------------------- MAIN FUNCTION ---------------------------

        /**
         * Interprets the string input as jump code and returns a StateMachine
         *
         * @param input the jump code to interpret
         * @param flags parse flags
         *
         * @return the parsed StateMachine
         *
         * @throws JumpError if input is invalid jump code
         */
        StateMachine* interpret(string input, int flags) throw(SyntaxError) {
            debug(flags, "Interpreting...");
            debug(flags, "--------------------------------------------------");

            // Recieve input
            s_input = input;

            // Create state machine
            s_machine = new StateMachine();
            s_machine->streamSet(Streams::STDNames::READ,   new ReadStream(cin));
            s_machine->streamSet(Streams::STDNames::PRINT,  new PrintStream(cout));
            s_machine->streamSet(Streams::STDNames::ERROR,  new PrintStream(cerr));
            s_machine->streamSet(Streams::STDNames::PROMPT, new PrintStream(cout, " "));

            // Start parser
            statemachine(flags);

            // End debug
            debug(flags, "--------------------------------------------------");

            // Return completed machine
            return s_machine;
        }

        // -------------------------- IMPLEMEMTATION ---------------------------

        /**
         * Checks a single flag in the flag buffer
         *
         * @param flags the flag buffer
         * @param flag  the flag to check
         *
         * @return true if the flag is on
         */
        static bool flag(int flags, int flag) {
            return (flags & flag) == flag;
        }

        /**
         * Prints a debug message
         *
         * @param flags   flag buffer
         * @param message the message to print
         */
        static void debug(int flags, string message) {
            if (flag(flags,DEBUG)) cout << message << endl;
        }

        /**
         * Returns a SyntaxError which descries unexpected token
         *
         * @param exp the expected value
         *
         * @return SyntaxError which describes unexpected
         */
        static SyntaxError unexpected(string ex) {
            return SyntaxError("unexpected token " + peek() + ". Expected " + ex);
        }

        /**
         * Returns the last recieved token
         *
         * @return the last recieved token
         */
        static string recieved() {
            return s_recieved;
        }

        /**
         * Returns true if the string is at end
         *
         * @return true if the string is at end
         */
        static bool atEnd() {
            return s_input.length() == 0;
        }

        /**
         * Returns true if the front can supply the given token (without supplying it)
         *
         * @param reg represents the token being recieved
         *
         * @return true if the front can supply the given token
         */
        static bool percieve(regex reg) {
            // Match object
            smatch matched;

            // Eliminate whitespaces
            bool found = regex_search(s_input, matched, WSPACE, REGEX_MATCH_CONSTANTS);
            if (found) s_input.erase(0, matched.length());

            // Search
            return regex_search(s_input, reg, REGEX_MATCH_CONSTANTS);
        }

        /**
         * Returns true if the front supplies the given token
         *
         * @param reg represents the token being recieved
         *
         * @return true if the front supplies the given token
         */
        static bool recieve(regex reg) {
            // Match object
            smatch matched;

            // Eliminate whitespaces
            bool found = regex_search(s_input, matched, WSPACE, REGEX_MATCH_CONSTANTS);
            if (found) s_input.erase(0, matched.length());

            // Search
            found = regex_search(s_input, matched, reg, REGEX_MATCH_CONSTANTS);
            if (found) {
                // Supply token
                s_recieved = matched.str();
                s_input.erase(0, matched.length());
            }
            return found;
        }

        /**
         * Asserts that the given token is supplied next in the input
         *
         * @param reg represents the token being recieved
         * @param exp the string to print in SyntaxError, identifying what was expected
         *
         * @throw SyntaxError if token is not found
         */
        static void require(regex reg, string ex) throw(SyntaxError) {
            if (!recieve(reg)) throw unexpected(ex);
        }

        /**
         * Returns a peek at the first 5 characters of the input
         *
         * @return a peek at the first 5 characters of the input
         */
        static string peek() {
            if (s_input.length() > 5) return s_input.substr(0,10) + "...";
            else return s_input;
        }

        // ----------------------------- NODES -----------------------------

        /**
         * Statemachine node
         */
        static void statemachine(int flags) throw(SyntaxError) {
            debug(flags, "statemachine");

            while(!atEnd()) {
                if (recieve(CONSTANT)) constant(flags);
                else if (recieve(VARIABLE)) variable(flags);
                else if (recieve(STREAM)) stream(flags);
                else if (recieve(STATE)) state(flags);
                else if (recieve(ENDLINE)) continue;
                else throw unexpected("const, var, stream, state, or ENDLINE");
                if (atEnd()) debug(flags, "-X- terminate -X-");
            }
        }

        /**
         * Constant node
         */
        static void constant(int flags) throw(SyntaxError) {
            debug(flags, "  constant");

            require(IDENTIFIER, "IDENTIFIER after const");
            string id = recieved(); debug(flags, "      id = " + id);
            require(ASSIGN, "= after IDENTIFIER (constants need to be set on declaration)");
            s_machine->constSet(id, feed(flags));
            recieve(ENDLINE);
        }

        /**
         * Variable node
         */
        static void variable(int flags) throw(SyntaxError) {
            debug(flags, "  variable");

            require(IDENTIFIER, "IDENTIFIER after var");
            string id = recieved(); debug(flags, "      id = " + id);
            if (recieve(ASSIGN)) s_machine->varSet(id, feed(flags));
            else s_machine->varSet(id, new Null());
            recieve(ENDLINE);
        }

        /**
         * Stream node
         */
        static void stream(int flags) throw(SyntaxError) {
            debug(flags, "  stream");

            // Identifier
            require(IDENTIFIER, "IDENTIFIER after stream");
            string id = recieved(); debug(flags, "      id = " + id);

            // Assignment
            require(ASSIGN, "= after IDENTIFIER");

            // Stream
            Streams::Stream* stream;
            if (recieve(ARRAYSTREAM)) stream = new ArrayStream();
            else throw unexpected("STREAMTYPE after =");

            // Require parentheses
            int i = 0;
            require(LPAREN, "LPAREN after stream ID");
            while(!percieve(RPAREN)) {
                stream->attributeSet(i, feed(flags));
                if (percieve(ENDLINE)) throw unexpected("RPAREN after stream definition");
                i++;
            }
            recieve(RPAREN);

            // Add stream
            s_machine->streamSet(id, stream);
        }

        /**
         * State node
         */
        static void state(int flags) throw(SyntaxError) {
            debug(flags, "  state");

            require(IDENTIFIER, "IDENTIFIER after state");
            string id = recieved(); debug(flags, "      id = " + id);
            require(ENDLINE, "ENDLINE after state definition");
            s_state = new State(id);
            while(!atEnd()) {
                if (recieve(READ)) read(flags);
                else if (recieve(PRINT)) print(flags);
                else if (recieve(TO)) to(flags);
                else if (recieve(LOOP)) loop(flags);
                else if (recieve(END)) end(flags);
                else if (percieve(STATE)
                      || percieve(CONSTANT)
                      || percieve(VARIABLE)
                      || percieve(STREAM)) break;
                else if (recieve(ENDLINE)) continue;
                else s_state->add(feed(flags));
            }
            s_machine->stateSet(s_state);
        }

        /**
         * Print node
         */
        static void print(int flags) throw(SyntaxError) {
            debug(flags, "      print");
            string id = Streams::STDNames::PRINT;
            if (recieve(ENDLINE)) {
                debug(flags, "          nullprint");
                s_state->add(new Print(new Null(), id));
            } else {
                Value* val = feed(flags);
                if (recieve(TO)) {
                    require(IDENTIFIER, "IDENTIFIER after ->");
                    id = recieved();
                }
                debug(flags, "          value = " + val->toString());
                debug(flags, "          outto = " + id);
                s_state->add(new Print(val, id));
            }
        }

        /**
         * Read node
         */
        static void read(int flags) throw(SyntaxError) {
            debug(flags, "      read");

            require(IDENTIFIER, "IDENTIFIER after read");
            string id1 = recieved(), id2 = Streams::STDNames::READ;

            if (recieve(FROM)) {
                require(IDENTIFIER, "IDENTIFIER after read");
                id2 = recieved();
            }

            s_state->add(new Read(new Identifier(id1), id2));
        }

        /**
         * To node
         */
        static void to(int flags) throw(SyntaxError) {
            debug(flags, "      to");

            require(IDENTIFIER, "IDENTIFIER after to");
            string id = recieved();
            debug(flags, "          id = " + id);

            if (recieve(IF)) {
                s_state->add(new To(id, feed(flags)));
            } else {
                recieve(OTHERWISE);
                s_state->add(new To(id));
            }
        }

        /**
         * End node
         */
        static void end(int flags) throw(SyntaxError) {
            debug(flags, "      end");

            if (recieve(IF)) {
                s_state->add(new End(feed(flags)));
            } else {
                recieve(OTHERWISE);
                s_state->add(new End(new Boolean(true)));
            }
        }

        /**
         * Loop node
         */
        static void loop(int flags) throw(SyntaxError) {
            debug(flags, "      loop");

            if (recieve(IF)) {
                s_state->add(new Loop(feed(flags)));
            } else {
                recieve(OTHERWISE);
                s_state->add(new Loop(new Boolean(true)));
            }
        }

        // ------------------------------ EXPRESSION ------------------------------

        /**
         * Feed node
         *
         * @return Feed expression
         */
        static Value* feed(int flags) throw(SyntaxError) {
            Expression* val = new Expression(OperLayer::ASSIGN);
            val->add(orr(flags), 0);
            if (recieve(ASSIGN)) val->add(orr(flags), 0);
            return val;
        }

        /**
         * Or node
         *
         * @return Or expression
         */
        static Value* orr(int flags) throw(SyntaxError) {
            Expression* val = new Expression(OperLayer::OR);
            val->add(andd(flags), 0);
            while (recieve(OR)) val->add(andd(flags), 0);
            return val;
        }

        /**
         * And node
         *
         * @return And expression
         */
        static Value* andd(int flags) throw(SyntaxError) {
            Expression* val = new Expression(OperLayer::AND);
            val->add(nott(flags), 0);
            while (recieve(AND)) val->add(nott(flags), 0);
            return val;
        }

        /**
         * Not node
         *
         * @return Not expression
         */
        static Value* nott(int flags) throw(SyntaxError) {
            Value* val;
            if (recieve(NOT)) {
                val = new Expression(OperLayer::NOT);
                ((Expression*)val)->add(compare(flags), 0);
                return val;
            } else {
                return compare(flags);
            }
        }

        /**
         * Compare node
         *
         * @return Compare expression
         */
        static Value* compare(int flags) throw(SyntaxError) {
            Expression* val = new Expression(COMPARE);
            val->add(addsub(flags), 0);
            if (recieve(GREATEQ)) val->add(addsub(flags), 1);
            else if (recieve(LESSEQ)) val->add(addsub(flags), 4);
            else if (recieve(EQUAL)) val->add(addsub(flags), 2);
            else if (recieve(NEQUAL)) val->add(addsub(flags), 3);
            else if (recieve(GREATER)) val->add(addsub(flags), 0);
            else if (recieve(LESS)) val->add(addsub(flags), 5);
            return val;
        }

        /**
         * AddSub node
         *
         * @return AddSub expression
         */
        static Value* addsub(int flags) throw(SyntaxError) {
            Expression* val = new Expression(ADDSUB);
            val->add(muldivmod(flags), 0);
            while(percieve(ADD) || percieve(SUB))
                if (recieve(ADD)) val->add(muldivmod(flags),      0);
                else if (recieve(SUB)) val->add(muldivmod(flags), 1);
            return val;
        }

        /**
         * MulDivMod node
         *
         * @return MulDivMod expression
         */
        static Value* muldivmod(int flags) throw(SyntaxError) {
            Expression* val = new Expression(MULDIVMOD);
            val->add(value(flags), 0);
            while(percieve(MUL) || percieve(DIV) || percieve(MOD))
                if (recieve(MUL)) val->add(value(flags),      0);
                else if (recieve(DIV)) val->add(value(flags), 1);
                else if (recieve(MOD)) val->add(value(flags), 2);
            return val;
        }

        /**
         * Value node
         *
         * @return Value expression
         */
        static Value* value(int flags) throw(SyntaxError) {
            string id; Value* increment;
            if (recieve(STRING)) return new String(recieved().substr(1,recieved().length()-2));
            else if (recieve(NUMBER)) return number(recieved());
            else if (recieve(BOOLEAN)) return new Boolean(recieved() == "True");
            else if (recieve(NULLVALUE)) return new Null();
            else if (recieve(IDENTIFIER)) {
                id = recieved();
                if (recieve(INCREMENT)) {
                    increment = new Expression(OperLayer::INCREMENT);
                    ((Expression*)increment)->add(new Identifier(id), 0);
                } else if (recieve(DECREMENT)) {
                    increment = new Expression(OperLayer::INCREMENT);
                    ((Expression*)increment)->add(new Identifier(id), 1);
                } else {
                    increment = new Identifier(id);
                }
                return increment;
            } else if (recieve(LPAREN)) {
                Value* val = feed(flags);
                require(RPAREN, "RPAREN after expression");
                return val;
            } else throw unexpected("ValueType");
        }
    }
}
