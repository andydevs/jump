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

// Libraries being used
#include <cstdlib>
#include <string>
#include <iostream>
#include <regex>

// Namespaces being used
using namespace std;
using namespace Jump;
using namespace Jump::Streams;
using namespace Jump::Errors;
using namespace Jump::Compiler::TokenParser;

// Code
namespace Jump
{
    // ------------------------ REGEX -------------------------

    const regex KEYWORD("\\b(const|var|state|stream|print|read|to|loop|end|if|otherwise|and|or|not|True|False|Null)\\b");
    const regex IDENTIFIER("[a-zA-Z][a-zA-Z0-9_]*");
    const regex STRING(STRING_REGEX);
    const regex NUMBER(NUMBER_REGEX);
    const regex OPERATION("[\\*\\+-/%=!><]+");
    const regex LPAREN("\\(");
    const regex RPAREN("\\)");
    const regex ENDLINE("(#.*?)?\r?\n");
    const regex WSPACE("[ \t]+");

    // ----------------------- MATCHERS -----------------------

    /**
     * Returns true if the next token in the given queue
     * is an operation and equals the given operation
     *
     * @param input the input string to check
     * @param oper the operation to check for
     *
     * @return true if the next token in the given queue
     *		   is an operation and equals the given operation
     */
    static bool isOperation(string input, string oper)
    {
        return tks.front() == Token("operation", oper);
    }

    /**
     * Returns true if the next token in the given queue
     * is a lparen
     *
     * @param input the input string to check
     *
     * @return true if the next token in the given queue
     *		   is a lparen
     */
    static bool isLparen(string input)
    {
        return tks.front().klass() == "lparen";
    }

    /**
     * Returns true if the next token in the given queue
     * is a rparen
     *
     * @param input the input string to check
     *
     * @return true if the next token in the given queue
     *		   is a rparen
     */
    static bool isRparen(string input)
    {
        return tks.front().klass() == "rparen";
    }

    /**
     * Returns true if the next token in the given queue
     * is a keyword
     *
     * @param input the input string to check
     *
     * @return true if the next token in the given queue
     *		   is a keyword
     */
    static bool isKeyword(string input)
    {
        return tks.front().klass() == "keyword";
    }

    /**
     * Returns true if the next token in the given queue
     * is a keyword and equals the given word
     *
     * @param input the input string to check
     * @param word the word to check for
     *
     * @return true if the next token in the given queue
     *		   is a keyword and equals the given word
     */
    static bool isKeyword(string input, string word)
    {
        return tks.front() == Token("keyword", word);
    }

    /**
     * Returns true if the next token in the given queue
     * is a state machine declaration
     *
     * @param input the input string to check
     *
     * @return true if the next token in the given queue
     *		   is a state machine declaration
     */
    static bool isDeclaration(string input)
    {
        return isKeyword(tks, "state")
            || isKeyword(tks, "var")
            || isKeyword(tks, "const")
            || isKeyword(tks, "stream");
    }

    /**
     * Returns true if the next token in the given queue
     * is an identifier
     *
     * @param input the input string to check
     *
     * @return true if the next token in the given queue
     *		   is an identifier
     */
    static bool isIdentifier(string input)
    {
        return tks.front().klass() == "identifier";
    }

    /**
     * Returns true if the next token in the given queue
     * is a string
     *
     * @param input the input string to check
     *
     * @return true if the next token in the given queue
     *		   is a string
     */
    static bool isString(string input)
    {
        return tks.front().klass() == "string";
    }

    /**
     * Returns true if the next token in the given queue
     * is a number
     *
     * @param input the input string to check
     *
     * @return true if the next token in the given queue
     *		   is a number
     */
    static bool isNumber(string input)
    {
        return tks.front().klass() == "number";
    }

    /**
     * Returns true if the next token in the given queue
     * is a value
     *
     * @param input the input string to check
     *
     * @return true if the next token in the given queue
     *		   is a value
     */
    static bool isValue(string input)
    {
        return isString(tks) || isNumber(tks)
            || isIdentifier(tks) || isLparen(tks);
    }

    /**
     * Returns true if the next token in the given queue
     * is an endline
     *
     * @param input the input string to check
     *
     * @return true if the next token in the given queue
     *		   is an endline
     */
    static bool isEndline(string input)
    {
        return tks.front().klass() == "endline" || tks.front().klass() == "EOF";
    }

    /**
     * Returns true if the given token queue is at the end
     * (and there are remaining tokens)
     *
     * @param input the input string to check
     *
     * @return true if the given token queue is at the end
     *		   (and there are remaining tokens)
     */
    static bool continuing(string input)
    {
        return !tks.empty();
    }

    // ----------------------- STATES --------------------------

    /**
     * Parses an endline
     *
     * @param tks the token queue to parse
     */
    static void endline(queue<Token>& tks)
    {
        // Pop next token
        if (isEndline(tks)) tks.pop();
    }

    // -------------- STATEMENTS --------------

    /**
     * Parses an expression
     *
     * @param tks the token queue to parse
     *
     * @return the expression parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* expression(queue<Token>& tks) throw(SyntaxError);

    /**
     * Parses a value
     *
     * @param tks the token queue to parse
     *
     * @return the value parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Value* value(queue<Token>& tks) throw(SyntaxError)
    {
        string literal = tks.front().attribute();
        Values::Value* val;
        if (isLparen(tks))
        {
            tks.pop();
            val = expression(tks);
            if (!isRparen(tks)) throw SyntaxError("Expected RPAREN");
        }
        else if (isIdentifier(tks))
        {
            val = new Values::Identifier(literal);
        }
        else
        {
            val = Values::evaluate(literal);
        }
        tks.pop();
        return val;
    }

    /**
     * Parses a muldivmodOp
     *
     * @param expr the muldivmod expression being parsed
     * @param tks  the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void muldivmodOp(Values::Expression* expr, queue<Token>& tks) throw(SyntaxError)
    {
        if (isOperation(tks, "*"))
        {
            tks.pop();
            expr->add(value(tks), 0);
            muldivmodOp(expr, tks);
        }
        else if (isOperation(tks, "/"))
        {
            tks.pop();
            expr->add(value(tks), 1);
            muldivmodOp(expr, tks);
        }
        else if (isOperation(tks, "%"))
        {
            tks.pop();
            expr->add(value(tks), 2);
            muldivmodOp(expr, tks);
        }
    }

    /**
     * Parses a muldivmod
     *
     * @param tks the token queue to parse
     *
     * @return the muldivmod parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* muldivmod(queue<Token>& tks) throw(SyntaxError)
    {
        Values::Expression* expr = new Values::Expression(Values::OperLayer::MULDIVMOD);
        expr->add(value(tks), 0);
        muldivmodOp(expr, tks);
        return expr;
    }

    /**
     * Parses a addsubOp
     *
     * @param expr the addsub expression being parsed
     * @param tks  the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void addsubOp(Values::Expression* expr, queue<Token>& tks) throw(SyntaxError)
    {
        if (isOperation(tks, "+"))
        {
            tks.pop();
            expr->add(muldivmod(tks), 0);
            addsubOp(expr, tks);
        }
        else if (isOperation(tks, "-"))
        {
            tks.pop();
            expr->add(muldivmod(tks), 1);
            addsubOp(expr, tks);
        }
    }

    /**
     * Parses an addsub
     *
     * @param tks the token queue to parse
     *
     * @return the addsub parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* addsub(queue<Token>& tks) throw(SyntaxError)
    {
        Values::Expression* expr = new Values::Expression(Values::OperLayer::ADDSUB);
        expr->add(muldivmod(tks), 0);
        addsubOp(expr, tks);
        return expr;
    }

    /**
     * Parses an compare
     *
     * @param tks the token queue to parse
     *
     * @return the compare parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* compare(queue<Token>& tks) throw(SyntaxError)
    {
        Values::Expression* expr = new Values::Expression(Values::OperLayer::COMPARE);
        expr->add(addsub(tks), 0);
        if (isOperation(tks, ">"))
        {
            tks.pop();
            expr->add(addsub(tks), 0);
        }
        else if (isOperation(tks, ">="))
        {
            tks.pop();
            expr->add(addsub(tks), 1);
        }
        else if (isOperation(tks, "=="))
        {
            tks.pop();
            expr->add(addsub(tks), 2);
        }
        else if (isOperation(tks, "!="))
        {
            tks.pop();
            expr->add(addsub(tks), 3);
        }
        else if (isOperation(tks, "<="))
        {
            tks.pop();
            expr->add(addsub(tks), 4);
        }
        else if (isOperation(tks, "<"))
        {
            tks.pop();
            expr->add(addsub(tks), 5);
        }
        return expr;
    }

    /**
     * Parses an nott
     *
     * @param tks the token queue to parse
     *
     * @return the nott parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* nott(queue<Token>& tks) throw(SyntaxError)
    {
        if (isKeyword(tks, "not"))
        {
            tks.pop();
            Values::Expression* expr = new Values::Expression(Values::OperLayer::NOT);
            expr->add(compare(tks), 0);
            return expr;
        }
        else
        {
            return compare(tks);
        }
    }

    /**
     * Parses a andOp
     *
     * @param expr the addsub expression being parsed
     * @param tks  the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void andOp(Values::Expression* expr, queue<Token>& tks) throw(SyntaxError)
    {
        if (isKeyword(tks, "and"))
        {
            tks.pop();
            expr->add(nott(tks), 0);
            andOp(expr, tks);
        }
    }

    /**
     * Parses an and
     *
     * @param tks the token queue to parse
     *
     * @return the and parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* andd(queue<Token>& tks) throw(SyntaxError)
    {
        Values::Expression* expr = new Values::Expression(Values::OperLayer::AND);
        expr->add(nott(tks), 0);
        andOp(expr, tks);
        return expr;
    }

    /**
     * Parses a orOp
     *
     * @param expr the addsub expression being parsed
     * @param tks  the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void orOp(Values::Expression* expr, queue<Token>& tks) throw(SyntaxError)
    {
        if (isKeyword(tks, "or"))
        {
            tks.pop();
            expr->add(andd(tks), 0);
            orOp(expr, tks);
        }
    }

    /**
     * Parses an orr
     *
     * @param tks the token queue to parse
     *
     * @return the orr parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* orr(queue<Token>& tks) throw(SyntaxError)
    {
        Values::Expression* expr = new Values::Expression(Values::OperLayer::OR);
        expr->add(andd(tks), 0);
        orOp(expr, tks);
        return expr;
    }

    /**
     * Parses an expression
     *
     * @param tks the token queue to parse
     *
     * @return the expression parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* expression(queue<Token>& tks) throw(SyntaxError)
    {
        return orr(tks);
    }

    /**
     * Parses an assign
     *
     * @param tks the token queue to parse
     *
     * @return the assign parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void assign(State* state, queue<Token>& tks) throw(SyntaxError)
    {
        Values::Expression* expr = new Values::Expression(Values::OperLayer::ASSIGN);
        expr->add(expression(tks), 0);
        if (isOperation(tks, "="))
        {
            tks.pop();
            expr->add(expression(tks), 0);
        }
        state->add(expr);
    }

    /**
     * Parses a end statement
     *
     * @param state the state to add the statement to
     * @param tks   the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void end(State* state, queue<Token>& tks) throw(SyntaxError)
    {
        // Next token
        tks.pop();

        // Declare variable
        Values::Value* condition;

        // If condition is given (given by if), set condition
        if (isKeyword(tks, "if"))
        {
            tks.pop();
            condition = expression(tks);
        }
        // Else set condition to true
        // This is unwise, though
        else
        {
            condition = new Values::Boolean(true);
        }

        // Add end statement
        state->add(new Statements::End(condition));
    }

    /**
     * Parses a loop statement
     *
     * @param state the state to add the statement to
     * @param tks   the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void loop(State* state, queue<Token>& tks) throw(SyntaxError)
    {
        // Next token
        tks.pop();

        // Declare variable
        Values::Value* condition;

        // If condition is given (given by if), set condition
        if (isKeyword(tks, "if"))
        {
            tks.pop();
            condition = expression(tks);
        }
        // Else set condition to true
        // This is unwise, though
        else
        {
            condition = new Values::Boolean(true);
        }

        // Add loop statement
        state->add(new Statements::Loop(condition));
    }

    /**
     * Parses a to statement
     *
     * @param state the state to add the statement to
     * @param tks   the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void to(State* state, queue<Token>& tks) throw(SyntaxError)
    {
        // Next token
        tks.pop();

        // If next is identifier
        if (isIdentifier(tks))
        {
            // Get identifier
            string id = tks.front().attribute();
            tks.pop();

            // Get condition
            Values::Value* condition;

            // If condition is given, set to condition
            if (isKeyword(tks, "if"))
            {
                tks.pop();
                condition = expression(tks);
            }
            // If condition is otherwise, set to true
            else if (isKeyword(tks, "otherwise"))
            {
                tks.pop();
                condition = new Values::Boolean(true);
            }
            // Else set to true
            else
            {
                condition = new Values::Boolean(true);
            }

            // Add to statement with the identifier token
            state->add(new Statements::To(id, condition));
        }
        // Else throw SyntaxError
        else throw SyntaxError("Expected identifier after \"to\" keyword. Got: " + tks.front().toString());
    }

    /**
     * Parses a read statement
     *
     * @param state the state to add the statement to
     * @param tks   the token queue to parse
     */
    static void read(State* state, queue<Token>& tks)
    {
        // Next token
        tks.pop();

        // Declare variables
        string streamRef = "stdin";
        string varRef;

        // Get first identifier
        if (isIdentifier(tks))
        {
            varRef = tks.front().attribute();
            tks.pop();
        }
        else throw SyntaxError("Unexpected token " + tks.front().toString() + ". expected Identifier");

        // If operation is given
        if (isOperation(tks, "->"))
        {
            // Next token
            tks.pop();

            // First identifier is stream, not variables
            streamRef = varRef;

            // Get variable
            if (isIdentifier(tks))
            {
                varRef = tks.front().attribute();
                tks.pop();
            }
            else throw SyntaxError("Unexpected token " + tks.front().toString() + ". expected Identifier");
        }

        // Add statement
        state->add(new Statements::Read(new Values::Identifier(varRef), streamRef));
    }

    /**
     * Parses a print statement
     *
     * @param state the state to add the statement to
     * @param tks   the token queue to parse
     */
    static void print(State* state, queue<Token>& tks)
    {
        // Next token
        tks.pop();

        // Declare variables
        Values::Value* toPrint;
        string streamRef;

        // If next is value, add print statement with the value token
        if (isValue(tks) || isKeyword(tks))
        {
            toPrint = expression(tks);
        }
        // Else if endline add blank print statement
        else if (isEndline(tks))
        {
            toPrint = new Values::Null();
        }
        // Else throw SyntaxError
        else
        {
            throw SyntaxError("Unexpected token " + tks.front().toString() + ". expected ValueType, Keyword or Endline");
        }

        // If next is stream operator
        if (isOperation(tks, "->"))
        {
            // Next token
            tks.pop();

            // Get streamref if identifier is given
            if (isIdentifier(tks))
            {
                streamRef = tks.front().attribute();
                tks.pop();
            }
            // Else throw error
            else
            {
                throw SyntaxError("Unexpected token " + tks.front().toString() + ". expected Identifier");
            }
        }
        // Else streamref is stdout
        else
        {
            streamRef = "stdout";
        }

        // Add statement to state
        state->add(new Statements::Print(toPrint, streamRef));
    }

    /**
     * Parses a statement
     *
     * @param state the state to add the statement to
     * @param tks   the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void statement(State* state, queue<Token>& tks) throw(SyntaxError)
    {
        // Parse Statements
        if (isKeyword(tks, "read"))
            read(state, tks);
        else if (isKeyword(tks, "print"))
            print(state, tks);
        else if (isKeyword(tks, "to"))
            to(state, tks);
        else if (isKeyword(tks, "loop"))
            loop(state, tks);
        else if (isKeyword(tks, "end"))
            end(state, tks);
        else
            assign(state, tks);
    }

    // -------------- STATEMACHINE --------------

    /**
     * Parses a state
     *
     * @param machine the StateMachine to add the state to
     * @param tks     the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void state(StateMachine& machine, queue<Token>& tks) throw(SyntaxError)
    {
        // Next token
        tks.pop();

        // If identifier is given
        if (isIdentifier(tks))
        {
            // Generate state from identifier token
            State* state = new State(tks.front().attribute());
            tks.pop();
            endline(tks);

            try
            {
                // Parse statements until next state declaration (or end of program)
                while (continuing(tks) && !isDeclaration(tks))
                    if (isKeyword(tks) || isValue(tks))
                        statement(state, tks);
                    else if (isEndline(tks))
                        endline(tks);
                    else
                        throw SyntaxError("Unexpected token " + tks.front().toString() + ". Expected KEYWORD or ENDLINE");

                // Set state in machine
                machine.stateSet(state);
            }
            catch (SyntaxError& e)
            {
                // Delete state if error
                delete state;
                throw e;
            }
        }
        // Throw error
        else throw SyntaxError("Expected identifier after \"state\" keyword");
    }

    /**
     * Parses a constant
     *
     * @param machine the StateMachine to add the constant to
     * @param tks     the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void constant(StateMachine& machine, queue<Token>& tks) throw(SyntaxError)
    {
        // Next
        tks.pop();

        // Get constant name
        string name = tks.front().attribute();
        tks.pop();

        // If assignment is given, set value, else throw error
        if (isOperation(tks, "="))
        {
            tks.pop();
            machine.constSet(name, expression(tks));
        }
        else throw SyntaxError("Expected \"=\" after constant declaration.");

        // Endline
        endline(tks);
    }

    /**
     * Parses a variable
     *
     * @param machine the StateMachine to add the variable to
     * @param tks     the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void variable(StateMachine& machine, queue<Token>& tks) throw(SyntaxError)
    {
        // Next
        tks.pop();

        // Get variable name
        string name = tks.front().attribute();
        tks.pop();

        // If assignment is given, set value
        // Else set to null
        if (isOperation(tks, "="))
        {
            tks.pop();
            machine.varSet(name, expression(tks));
        }
        else
        {
            machine.varSet(name, new Values::Null());
        }

        // Endline
        endline(tks);
    }

    static void stream(StateMachine& machine, queue<Token>& tks) throw(SyntaxError)
    {
        // Next
        tks.pop();

        // Get variable name
        string name = tks.front().attribute();
        tks.pop();

        // If assignment is given, set stream
        if (isOperation(tks, "="))
        {
            tks.pop();
            if (tks.front().attribute() == "ArrayStream")
            {
                machine.streamSet(name, new ArrayStream());
                tks.pop();
            }
            else
                throw SyntaxError("Undefined stream type: " + tks.front().attribute());
        }

        // Endline
        endline(tks);
    }

    /**
     * Parses a StateMachine declaration
     *
     * @param machine the StateMachine to parse
     * @param tks     the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void declaration(StateMachine& machine, queue<Token>& tks) throw(SyntaxError)
    {
        // Parse declaration
        if (isKeyword(tks, "state"))
            state(machine, tks);
        else if (isKeyword(tks, "const"))
            constant(machine, tks);
        else if (isKeyword(tks, "var"))
            variable(machine, tks);
        else if (isKeyword(tks, "stream"))
            stream(machine, tks);
        else
            throw SyntaxError("Undefined StateMachine declaration: " + tks.front().attribute());
    }

    /**
     * Parses a StateMachine
     *
     * @param machine the StateMachine to parse
     * @param tks     the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void statemachine(StateMachine& machine, queue<Token>& tks) throw(SyntaxError)
    {
        // Parse state machine declarations
        while (continuing(tks))
            if (isKeyword(tks))
                declaration(machine, tks);
            else if (isEndline(tks))
                endline(tks);
            else
                throw SyntaxError("Unexpected token " + tks.front().toString() + ". Expected KEYWORD or ENDLINE");
    }

    /**
     * Interprets the string input as jump code and returns a StateMachine
     *
     * @param input the jump code to interpret
     *
     * @return the parsed StateMachine
     *
     * @throws SyntaxError if input is invalid jump code
     */
    StateMachine interpret(string input) throws SyntaxError
    {

    }
}
