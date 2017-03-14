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
     * Constructor for Interpreter
     */
    Interpreter::Interpreter():
    m_input(""),
    m_recieved(""),
    m_machine() {}

    /**
     * Interprets the string input as jump code and returns a StateMachine
     *
     * @param input the jump code to interpret
     *
     * @return the parsed StateMachine
     *
     * @throws JumpError if input is invalid jump code
     */
    StateMachine Interpreter::interpret(string input) throw(SyntaxError) {
        // Recieve input
        m_input = input;

        // Create state machine
        m_machine = StateMachine();
        m_machine.streamSet("stdin",  new ReadStream(cin));
        m_machine.streamSet("stdout", new PrintStream(cout));
        m_machine.streamSet("stderr", new PrintStream(cerr));
        m_machine.streamSet("prompt", new PrintStream(cout, " "));

        // Start parser
        statemachine();

        // Return completed machine
        return m_machine;
    }

    /**
     * Returns a SyntaxError which descries unexpected token
     *
     * @param exp the expected value
     *
     * @return SyntaxError which describes unexpected
     */
    SyntaxError Interpreter::unexpected(std::string ex) {
        return SyntaxError("unexpected token " + peek() + ". Expected " + ex);
    }

    /**
     * Returns the last recieved token
     *
     * @return the last recieved token
     */
    string Interpreter::recieved() {
        return m_recieved;
    }

    /**
     * Returns true if the string is at end
     *
     * @return true if the string is at end
     */
    bool Interpreter::atEnd() {
        return m_input.length() == 0;
    }

    /**
     * Returns true if the front can supply the given token (without supplying it)
     *
     * @param reg represents the token being recieved
     *
     * @return true if the front can supply the given token
     */
    bool Interpreter::percieve(std::regex reg) {
        // Match object
        smatch matched;

        // Eliminate whitespaces
        bool found = regex_search(m_input, matched, WSPACE, REGEX_MATCH_CONSTANTS);
        if (found) m_input.erase(0, matched.length());

        // Search
        return regex_search(m_input, reg, REGEX_MATCH_CONSTANTS);
    }

    /**
     * Returns true if the front supplies the given token
     *
     * @param reg represents the token being recieved
     *
     * @return true if the front supplies the given token
     */
    bool Interpreter::recieve(regex reg) {
        // Match object
        smatch matched;

        // Eliminate whitespaces
        bool found = regex_search(m_input, matched, WSPACE, REGEX_MATCH_CONSTANTS);
        if (found) m_input.erase(0, matched.length());

        // Search
        found = regex_search(m_input, matched, reg, REGEX_MATCH_CONSTANTS);
        if (found) {
            // Supply token
            m_recieved = matched.str();
            m_input.erase(0, matched.length());
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
    void Interpreter::require(std::regex reg, std::string ex) throw(SyntaxError) {
        if (!recieve(reg)) throw unexpected(ex);
    }

    /**
     * Returns a peek at the first 5 characters of the input
     *
     * @return a peek at the first 5 characters of the input
     */
    string Interpreter::peek() {
        if (m_input.length() > 5) return m_input.substr(0,5) + "...";
        else return m_input;
    }

    // ----------------------------- NODES -----------------------------

    /**
     * Statemachine node
     */
    void Interpreter::statemachine() throw(SyntaxError) {
        while(!atEnd()) {
            if (recieve(CONSTANT)) constant();
            else if (recieve(VARIABLE)) variable();
            else if (recieve(STREAM)) stream();
            else if (recieve(STATE)) state();
            else if (recieve(ENDLINE)) continue;
            else throw unexpected("const, var, stream, state, or ENDLINE");
        }
    }

    /**
     * Constant node
     */
    void Interpreter::constant() throw(SyntaxError) {
        require(IDENTIFIER, "IDENTIFIER after const");
        string id = recieved();
        require(ASSIGN, "= after IDENTIFIER (constants need to be set on declaration)");
        m_machine.constSet(id, feed());
        recieve(ENDLINE);
    }

    /**
     * Variable node
     */
    void Interpreter::variable() throw(SyntaxError) {
        require(IDENTIFIER, "IDENTIFIER after var");
        string id = recieved();
        if (recieve(ASSIGN)) m_machine.varSet(id, feed());
        recieve(ENDLINE);
    }

    /**
     * Stream node
     */
    void Interpreter::stream() throw(SyntaxError) {
        require(IDENTIFIER, "IDENTIFIER after stream");
        string id = recieved();
        require(ASSIGN, "= after IDENTIFIER");
        if (recieve(ARRAYSTREAM)) m_machine.streamSet(id, new ArrayStream());
        else throw unexpected("STREAMTYPE after =");
    }

    /**
     * State node
     */
    void Interpreter::state() throw(SyntaxError) {
        require(IDENTIFIER, "IDENTIFIER after state");
        string id = recieved();
        require(ENDLINE, "ENDLINE after state definition");
        m_state = new State(id);
        while(!atEnd()) {
            if (recieve(READ)) read();
            else if (recieve(PRINT)) print();
            else if (recieve(TO)) to();
            else if (recieve(LOOP)) loop();
            else if (recieve(END)) end();
            else if (percieve(STATE)
                  || percieve(CONSTANT)
                  || percieve(VARIABLE)
                  || percieve(STREAM)) break;
            else m_state->add(feed());
        }
        m_machine.stateSet(m_state);
    }

    /**
     * Print node
     */
    void Interpreter::print() throw(SyntaxError) {
        Value* val = feed();
        string id = "stdout";
        if (recieve(PIPE)) {
            require(IDENTIFIER, "IDENTIFIER after ->");
            id = recieved();
        }
        m_state->add(new Print(val, id));
    }

    /**
     * Read node
     */
    void Interpreter::read() throw(SyntaxError) {
        require(IDENTIFIER, "IDENTIFIER after read");
        string id1 = recieved(), id2;

        if (recieve(PIPE)) {
            require(IDENTIFIER, "IDENTIFIER after read");
            id2 = recieved();
            m_state->add(new Read(new Identifier(id2), id1));
        } else m_state->add(new Read(new Identifier(id1)));
    }

    /**
     * To node
     */
    void Interpreter::to() throw(SyntaxError) {
        require(IDENTIFIER, "IDENTIFIER after to");
        string id = recieved();

        if (recieve(IF)) {
            m_state->add(new To(id, feed()));
        } else {
            recieve(OTHERWISE);
            m_state->add(new To(id));
        }
    }

    /**
     * End node
     */
    void Interpreter::end() throw(SyntaxError) {
        if (recieve(IF)) {
            m_state->add(new End(feed()));
        } else {
            recieve(OTHERWISE);
            m_state->add(new End(new Boolean(true)));
        }
    }

    /**
     * Loop node
     */
    void Interpreter::loop() throw(SyntaxError) {
        if (recieve(IF)) {
            m_state->add(new Loop(feed()));
        } else {
            recieve(OTHERWISE);
            m_state->add(new Loop(new Boolean(true)));
        }
    }

    // ------------------------------ EXPRESSION ------------------------------

    /**
     * Feed node
     *
     * @return Feed expression
     */
    Value* Interpreter::feed() throw(SyntaxError) {
        Expression* val = new Expression(OperLayer::ASSIGN);
        val->add(orr(), 0);
        if (recieve(ASSIGN)) val->add(orr(), 0);
        return val;
    }

    /**
     * Or node
     *
     * @return Or expression
     */
    Value* Interpreter::orr() throw(SyntaxError) {
        Expression* val = new Expression(OperLayer::OR);
        val->add(andd(), 0);
        while (recieve(OR)) val->add(andd(), 0);
        return val;
    }

    /**
     * And node
     *
     * @return And expression
     */
    Value* Interpreter::andd() throw(SyntaxError) {
        Expression* val = new Expression(OperLayer::AND);
        val->add(nott(), 0);
        while (recieve(AND)) val->add(nott(), 0);
        return val;
    }

    /**
     * Not node
     *
     * @return Not expression
     */
    Value* Interpreter::nott() throw(SyntaxError) {
        Value* val;
        if (recieve(NOT)) {
            val = new Expression(OperLayer::NOT);
            ((Expression*)val)->add(compare(), 0);
            return val;
        } else {
            return compare();
        }
    }

    /**
     * Compare node
     *
     * @return Compare expression
     */
    Value* Interpreter::compare() throw(SyntaxError) {
        Expression* val = new Expression(COMPARE);
        val->add(addsub(), 0);
        if (recieve(GREATER)) val->add(addsub(), 0);
        else if (recieve(GREATEQ)) val->add(addsub(), 1);
        else if (recieve(EQUAL)) val->add(addsub(), 2);
        else if (recieve(NEQUAL)) val->add(addsub(), 3);
        else if (recieve(LESSEQ)) val->add(addsub(), 4);
        else if (recieve(LESS)) val->add(addsub(), 5);
        return val;
    }

    /**
     * AddSub node
     *
     * @return AddSub expression
     */
    Value* Interpreter::addsub() throw(SyntaxError) {
        Expression* val = new Expression(ADDSUB);
        val->add(muldivmod(), 0);
        while(percieve(ADD) || percieve(SUB))
            if (recieve(ADD)) val->add(muldivmod(),      0);
            else if (recieve(SUB)) val->add(muldivmod(), 1);
        return val;
    }

    /**
     * MulDivMod node
     *
     * @return MulDivMod expression
     */
    Value* Interpreter::muldivmod() throw(SyntaxError) {
        Expression* val = new Expression(MULDIVMOD);
        val->add(value(), 0);
        while(percieve(MUL) || percieve(DIV) || percieve(MOD))
            if (recieve(MUL)) val->add(value(),      0);
            else if (recieve(DIV)) val->add(value(), 1);
            else if (recieve(MOD)) val->add(value(), 2);
        return val;
    }

    /**
     * Value node
     *
     * @return Value expression
     */
    Value* Interpreter::value() throw(SyntaxError) {
        if (recieve(STRING)) return new String(recieved().substr(1,recieved().length()-2));
        else if (recieve(NUMBER)) return number(recieved());
        else if (recieve(BOOLEAN)) return new Boolean(recieved() == "True");
        else if (recieve(NULLVALUE)) return new Null();
        else if (recieve(IDENTIFIER)) return new Identifier(recieved());
        else if (recieve(LPAREN)) {
            Value* val = feed();
            require(RPAREN, "RPAREN after expression");
            return val;
        }
        else return new Null();
    }
}
