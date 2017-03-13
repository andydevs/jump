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
using namespace Jump::Values;

// Code
namespace Jump
{
    // ------------------------ REGEX -------------------------

    // Regex match constants
    const std::regex_constants::match_flag_type REGEX_MATCH_CONSTANTS
        = std::regex_constants::match_continuous;

    // Regexes
    const regex KEYWORD("\\b(const|var|state|stream|print|read|to|loop|end|if|otherwise|and|or|not|True|False|Null)\\b");
    const regex IDENTIFIER("[a-zA-Z][a-zA-Z0-9_]*");
    const regex STRING(STRING_REGEX);
    const regex NUMBER(NUMBER_REGEX);
    const regex OPERATION("[\\*\\+-/%=!><]+");
    const regex LPAREN("\\(");
    const regex RPAREN("\\)");
    const regex ENDLINE("(#.*?)?\r?\n");
    const regex WSPACE("[ \t]+");

    // Match results buffer
    static smatch matchResults;
    static string recievedString;

    // ----------------------- MATCHERS -----------------------

    /**
     * Returns true if string is at end of interpretation
     *
     * @return true if string is at end of interpretation
     */
    static bool isEnd(string& input) {
        return input.length() == 0;
    }

    /**
     * Eliminates whitespaces
     *
     * @param input the input string to modify
     */
    static void whitespace(string& input)
    {
        bool search = regex_search(input, matchResults, WSPACE, REGEX_MATCH_CONSTANTS);
        if (search) input.erase(0, matchResults.length());
    }

    /**
     * Return the last matched string
     *
     * @return the last matched string
     */
    static string recieved() {
        return recievedString;
    }

    /**
     * Returns true if the last match equals the given value
     *
     * @param value the value to check
     *
     * @return true if the last match equals the given value
     */
    static bool recievedWas(string value) {
        return recieved() == value;
    }

    /**
     * Matches front of the string with the given regex
     *
     * @param input the input string to match
     * @param reg   the regex to match with
     *
     * @return true if string matches given regex
     */
    static bool recieve(string& input, regex reg) {
        whitespace(input);
        bool search = regex_search(input, matchResults, reg, REGEX_MATCH_CONSTANTS);
        cout << "s: " << search;
        if (search) {
            recievedString = matchResults.str();
            input.erase(0, matchResults.length());
            cout << " l: " << recieved();
        }
        cout << endl;
        return search;
    }

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
    static bool isOperation(string& input, string oper)
    {
        cout << "m: operation ";
        return recieve(input, OPERATION) && recievedWas(oper);
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
    static bool isLparen(string& input)
    {
        cout << "m: lparen ";
        return recieve(input, LPAREN);
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
    static bool isRparen(string& input)
    {
        cout << "m: rparen ";
        return recieve(input, RPAREN);
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
    static bool isKeyword(string& input)
    {
        cout << "m: keyword ";
        return recieve(input, KEYWORD);
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
    static bool isKeyword(string& input, string word)
    {
        return isKeyword(input) && recievedWas(word);
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
    static bool isDeclaration(string& input)
    {
        return isKeyword(input, "state")
            || isKeyword(input, "var")
            || isKeyword(input, "const")
            || isKeyword(input, "stream");
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
    static bool isIdentifier(string& input)
    {
        cout << "m: identifier ";
        return recieve(input, IDENTIFIER);
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
    static bool isString(string& input)
    {
        cout << "m: string ";
        return recieve(input, STRING);
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
    static bool isNumber(string& input)
    {
        cout << "m: number ";
        return recieve(input, NUMBER);
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
    static bool isValue(string& input)
    {
        cout << "m: value ";
        return isString(input) || isNumber(input)
            || isIdentifier(input) || isLparen(input);
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
    static bool isEndline(string& input)
    {
        cout << "m: endline ";
        return recieve(input, ENDLINE) || isEnd(input);
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
    static bool continuing(string& input)
    {
        return !isEnd(input);
    }

    // ----------------------- STATES --------------------------

    /**
     * Parses an endline
     *
     * @param input the token queue to parse
     */
    static void endline(string& input)
    {
        recieve(input, ENDLINE);
    }

    // -------------- STATEMENTS --------------

    /**
     * Parses an expression
     *
     * @param input the token queue to parse
     *
     * @return the expression parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* expression(string& input) throw(SyntaxError);

    /**
     * Parses a value
     *
     * @param input the token queue to parse
     *
     * @return the value parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Value* value(string& input) throw(SyntaxError)
    {
        cout << "value" << endl;

        string literal = recieved();
        Values::Value* val;
        if (isLparen(input))
        {

            val = expression(input);
            if (!isRparen(input)) throw SyntaxError("Expected RPAREN");
        }
        else if (isIdentifier(input))
        {
            val = new Values::Identifier(literal);
        }
        else
        {
            val = Values::evaluate(literal);
        }

        return val;
    }

    /**
     * Parses a muldivmodOp
     *
     * @param expr the muldivmod expression being parsed
     * @param input  the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void muldivmodOp(Values::Expression* expr, string& input) throw(SyntaxError)
    {
        cout << "muldivmodOp" << endl;

        if (isOperation(input, "*"))
        {

            expr->add(value(input), 0);
            muldivmodOp(expr, input);
        }
        else if (isOperation(input, "/"))
        {

            expr->add(value(input), 1);
            muldivmodOp(expr, input);
        }
        else if (isOperation(input, "%"))
        {

            expr->add(value(input), 2);
            muldivmodOp(expr, input);
        }
    }

    /**
     * Parses a muldivmod
     *
     * @param input the token queue to parse
     *
     * @return the muldivmod parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* muldivmod(string& input) throw(SyntaxError)
    {
        cout << "muldivmod" << endl;

        Values::Expression* expr = new Values::Expression(Values::OperLayer::MULDIVMOD);
        expr->add(value(input), 0);
        muldivmodOp(expr, input);
        return expr;
    }

    /**
     * Parses a addsubOp
     *
     * @param expr the addsub expression being parsed
     * @param input  the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void addsubOp(Values::Expression* expr, string& input) throw(SyntaxError)
    {
        cout << "addsubop" << endl;

        if (isOperation(input, "+"))
        {

            expr->add(muldivmod(input), 0);
            addsubOp(expr, input);
        }
        else if (isOperation(input, "-"))
        {

            expr->add(muldivmod(input), 1);
            addsubOp(expr, input);
        }
    }

    /**
     * Parses an addsub
     *
     * @param input the token queue to parse
     *
     * @return the addsub parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* addsub(string& input) throw(SyntaxError)
    {
        cout << "addsub" << endl;

        Values::Expression* expr = new Values::Expression(Values::OperLayer::ADDSUB);
        expr->add(muldivmod(input), 0);
        addsubOp(expr, input);
        return expr;
    }

    /**
     * Parses an compare
     *
     * @param input the token queue to parse
     *
     * @return the compare parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* compare(string& input) throw(SyntaxError)
    {
        cout << "compare" << endl;

        Values::Expression* expr = new Values::Expression(Values::OperLayer::COMPARE);
        expr->add(addsub(input), 0);
        if (isOperation(input, ">"))
        {

            expr->add(addsub(input), 0);
        }
        else if (isOperation(input, ">="))
        {

            expr->add(addsub(input), 1);
        }
        else if (isOperation(input, "=="))
        {

            expr->add(addsub(input), 2);
        }
        else if (isOperation(input, "!="))
        {

            expr->add(addsub(input), 3);
        }
        else if (isOperation(input, "<="))
        {

            expr->add(addsub(input), 4);
        }
        else if (isOperation(input, "<"))
        {

            expr->add(addsub(input), 5);
        }
        return expr;
    }

    /**
     * Parses an nott
     *
     * @param input the token queue to parse
     *
     * @return the nott parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* nott(string& input) throw(SyntaxError)
    {
        cout << "nott" << endl;

        if (isKeyword(input, "not"))
        {

            Values::Expression* expr = new Values::Expression(Values::OperLayer::NOT);
            expr->add(compare(input), 0);
            return expr;
        }
        else
        {
            return compare(input);
        }
    }

    /**
     * Parses a andOp
     *
     * @param expr the addsub expression being parsed
     * @param input  the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void andOp(Values::Expression* expr, string& input) throw(SyntaxError)
    {
        cout << "andop" << endl;

        if (isKeyword(input, "and"))
        {

            expr->add(nott(input), 0);
            andOp(expr, input);
        }
    }

    /**
     * Parses an and
     *
     * @param input the token queue to parse
     *
     * @return the and parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* andd(string& input) throw(SyntaxError)
    {
        cout << "andd" << endl;

        Values::Expression* expr = new Values::Expression(Values::OperLayer::AND);
        expr->add(nott(input), 0);
        andOp(expr, input);
        return expr;
    }

    /**
     * Parses a orOp
     *
     * @param expr the addsub expression being parsed
     * @param input  the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void orOp(Values::Expression* expr, string& input) throw(SyntaxError)
    {
        cout << "orop" << endl;

        if (isKeyword(input, "or"))
        {
            expr->add(andd(input), 0);
            orOp(expr, input);
        }
    }

    /**
     * Parses an orr
     *
     * @param input the token queue to parse
     *
     * @return the orr parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* orr(string& input) throw(SyntaxError)
    {
        cout << "orr" << endl;

        Values::Expression* expr = new Values::Expression(Values::OperLayer::OR);
        expr->add(andd(input), 0);
        orOp(expr, input);
        return expr;
    }

    /**
     * Parses an expression
     *
     * @param input the token queue to parse
     *
     * @return the expression parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static Values::Expression* expression(string& input) throw(SyntaxError)
    {
        cout << "expression" << endl;

        return orr(input);
    }

    /**
     * Parses an assign
     *
     * @param input the token queue to parse
     *
     * @return the assign parsed
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void assign(State* state, string& input) throw(SyntaxError)
    {
        cout << "assign" << endl;

        Values::Expression* expr = new Values::Expression(Values::OperLayer::ASSIGN);
        expr->add(expression(input), 0);
        if (isOperation(input, "="))
        {

            expr->add(expression(input), 0);
        }
        state->add(expr);
    }

    /**
     * Parses a end statement
     *
     * @param state the state to add the statement to
     * @param input   the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void end(State* state, string& input) throw(SyntaxError)
    {
        cout << "end" << endl;


        // Declare variable
        Values::Value* condition;

        // If condition is given (given by if), set condition
        if (isKeyword(input, "if"))
        {

            condition = expression(input);
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
     * @param input   the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void loop(State* state, string& input) throw(SyntaxError)
    {
        cout << "loop" << endl;


        // Declare variable
        Values::Value* condition;

        // If condition is given (given by if), set condition
        if (isKeyword(input, "if"))
        {

            condition = expression(input);
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
     * @param input   the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void to(State* state, string& input) throw(SyntaxError)
    {
        cout << "to" << endl;


        // If next is identifier
        if (isIdentifier(input))
        {
            // Get identifier
            string id = recieved();


            // Get condition
            Values::Value* condition;

            // If condition is given, set to condition
            if (isKeyword(input, "if"))
            {

                condition = expression(input);
            }
            // If condition is otherwise, set to true
            else if (isKeyword(input, "otherwise"))
            {

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
        else throw SyntaxError("Expected identifier after \"to\" keyword. Got: " + recieved());
    }

    /**
     * Parses a read statement
     *
     * @param state the state to add the statement to
     * @param input   the token queue to parse
     */
    static void read(State* state, string& input)
    {
        cout << "read" << endl;


        // Declare variables
        string streamRef = "stdin";
        string varRef;

        // Get first identifier
        if (isIdentifier(input))
        {
            varRef = recieved();

        }
        else throw SyntaxError("Unexpected token \"" + recieved() + "\". expected Identifier");

        // If operation is given
        if (isOperation(input, "->"))
        {
            // Next token


            // First identifier is stream, not variables
            streamRef = varRef;

            // Get variable
            if (isIdentifier(input))
            {
                varRef = recieved();

            }
            else throw SyntaxError("Unexpected token \"" + recieved() + "\". expected Identifier");
        }

        // Add statement
        state->add(new Statements::Read(new Values::Identifier(varRef), streamRef));
    }

    /**
     * Parses a print statement
     *
     * @param state the state to add the statement to
     * @param input   the token queue to parse
     */
    static void print(State* state, string& input)
    {
        cout << "print" << endl;


        // Declare variables
        Values::Value* toPrint;
        string streamRef;

        // If next is value, add print statement with the value token
        if (isValue(input) || isKeyword(input))
        {
            toPrint = expression(input);
        }
        // Else if endline add blank print statement
        else if (isEndline(input))
        {
            toPrint = new Values::Null();
        }
        // Else throw SyntaxError
        else
        {
            throw SyntaxError("Unexpected token \"" + recieved() + "\". expected ValueType, Keyword or Endline");
        }

        // If next is stream operator
        if (isOperation(input, "->"))
        {
            // Next token


            // Get streamref if identifier is given
            if (isIdentifier(input))
            {
                streamRef = recieved();

            }
            // Else throw error
            else
            {
                throw SyntaxError("Unexpected token \"" + recieved() + "\". expected Identifier");
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
     * @param input   the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void statement(State* state, string& input) throw(SyntaxError)
    {
        cout << "statement" << endl;

        // Parse Statements
        if (isKeyword(input, "read"))
            read(state, input);
        else if (isKeyword(input, "print"))
            print(state, input);
        else if (isKeyword(input, "to"))
            to(state, input);
        else if (isKeyword(input, "loop"))
            loop(state, input);
        else if (isKeyword(input, "end"))
            end(state, input);
        else
            assign(state, input);
    }

    // -------------- STATEMACHINE --------------

    /**
     * Parses a state
     *
     * @param machine the StateMachine to add the state to
     * @param input     the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void state(StateMachine& machine, string& input) throw(SyntaxError)
    {
        cout << "state" << endl;


        // If identifier is given
        if (isIdentifier(input))
        {
            // Generate state from identifier token
            State* state = new State(recieved());

            endline(input);

            try
            {
                // Parse statements until next state declaration (or end of program)
                while (continuing(input) && !isDeclaration(input))
                    if (isKeyword(input) || isValue(input))
                        statement(state, input);
                    else if (isEndline(input))
                        endline(input);
                    else
                        throw SyntaxError("Unexpected token \"" + recieved() + "\". Expected KEYWORD or ENDLINE");

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
     * @param input     the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void constant(StateMachine& machine, string& input) throw(SyntaxError)
    {
        cout << "constant" << endl;

        // Get constant name
        string name = recieved();


        // If assignment is given, set value, else throw error
        if (isOperation(input, "="))
        {
            machine.constSet(name, expression(input));
        }
        else throw SyntaxError("Expected \"=\" after constant declaration.");

        // Endline
        endline(input);
    }

    /**
     * Parses a variable
     *
     * @param machine the StateMachine to add the variable to
     * @param input     the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void variable(StateMachine& machine, string& input) throw(SyntaxError)
    {
        cout << "variable" << endl;


        // Get variable name
        string name = recieved();


        // If assignment is given, set value
        // Else set to null
        if (isOperation(input, "="))
        {

            machine.varSet(name, expression(input));
        }
        else
        {
            machine.varSet(name, new Values::Null());
        }

        // Endline
        endline(input);
    }

    static void stream(StateMachine& machine, string& input) throw(SyntaxError)
    {
        cout << "stream" << endl;

        // Get variable name
        string name = recieved();


        // If assignment is given, set stream
        if (isOperation(input, "="))
        {

            if (recieved() == "ArrayStream")
            {
                machine.streamSet(name, new ArrayStream());

            }
            else
                throw SyntaxError("Undefined stream type: " + recieved());
        }

        // Endline
        endline(input);
    }

    /**
     * Parses a StateMachine
     *
     * @param machine the StateMachine to parse
     * @param input     the token queue to parse
     *
     * @throw SyntaxError if invalid token sequence
     */
    static void statemachine(StateMachine& machine, string& input) throw(SyntaxError)
    {
        cout << "statemachine " << input.substr(0,5) << endl;

        // Parse state machine declarations
        while (!isEnd(input))
        {
            if (isKeyword(input))
                if (recievedWas("state"))  state(machine, input);
                else if (recievedWas("const")) constant(machine, input);
                else if (recievedWas("var")) variable(machine, input);
                else if (recievedWas("stream")) stream(machine, input);
                else throw SyntaxError("Undefined StateMachine declaration: " + recieved());
            else if (isEndline(input)) cout << "endline" << endl;
            else throw SyntaxError("Unexpected character \"" + input.substr(0,10) + "\". Expected KEYWORD or ENDLINE");
        }
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
    StateMachine interpret(string input) throw(SyntaxError)
    {
        // Create machine (with standard streams)
        StateMachine machine;
        machine.streamSet("stdin",  new ReadStream(cin));
        machine.streamSet("stdout", new PrintStream(cout));
        machine.streamSet("stderr", new PrintStream(cerr));
        machine.streamSet("prompt", new PrintStream(cout, " "));

        // Parse Machine
        statemachine(machine, input);

        // Return machine
        return machine;
    }
}
