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
using namespace Jump::Streams;
using namespace Jump::Values;
using namespace Jump::Errors;

/**
 * Jump is a new programming language that uses the state machine paradigm
 *
 * @author  Anshul Kharbanda
 * @created 7 - 15 - 2016
 */
namespace Jump {
    /**
     * Interprets the string input as jump code and returns a StateMachine
     *
     * @param input the jump code to interpret
     *
     * @return the parsed StateMachine
     *
     * @throws JumpError if input is invalid jump code
     */
    StateMachine Interpreter::interpret(string input) throw(JumpError) {
        // Recieve input
        m_input = input;

        // Create state machine
        m_machine = StateMachine();
        m_machine.setStream("stdin",  new ReadStream(cin));
        m_machine.setStream("stdout", new PrintStream(cout));
        m_machine.setStream("stderr", new PrintStream(cerr));
        m_machine.setStream("prompt", new PrintStream(cout, " "));

        // Start parser
        statemachine();

        // Return completed machine
        return m_machine;
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
    bool Interpreter::end() {
        return m_input.length() == 0;
    }

    /**
     * Returns true if the front can supply the given token (without supplying it)
     *
     * @param reg represents the token being recieved
     *
     * @return true if the front can supply the given token
     */
    bool percieve(std::regex reg) {
        // Eliminate whitespaces
        bool search = regex_search(m_input, m_matched, WSPACE, REGEX_MATCH_CONSTANTS);
        if (search) input.erase(0, m_matched.length());

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
        // Eliminate whitespaces
        bool search = regex_search(m_input, m_matched, WSPACE, REGEX_MATCH_CONSTANTS);
        if (search) input.erase(0, m_matched.length());

        // Search
        bool search = regex_search(m_input, m_matched, reg, REGEX_MATCH_CONSTANTS);
        if (search) {
            m_recieved = m_matched.str();
            m_input.erase(0, m_matched.length());
        }
        return search;
    }

    /**
     * Asserts that the given token appears next in the input
     *
     * @param reg represents the token being recieved
     * @param exp the string to print in SyntaxError, identifying what was expected
     *
     * @throw SyntaxError if token is not found
     */
    void require(std::regex reg, std::string exp) throw(SyntaxError) {
        if (!require(reg)) throw SyntaxError("Unexpected token " + feed() + " expected " + exp);
    }

    /**
     * Reutrns the value stored in the statemachine at the given id
     *
     * @param id the id to store
     *
     * @return the value stored in the statemachine at the given id
     *
     * @throw ReferenceError if value is not found in either const or var
     */
    Value* Interpreter::get(std::string id) throw(ReferenceError) {
        try {
            m_machine.constGet(id)
        } catch (ReferenceError e) {
            m_machine.varGet(id);
        }
    }

    /**
     * Returns a peek at the first 5 characters of the input
     *
     * @return a peek at the first 5 characters of the input
     */
    string peek() {
        if (m_input.length() > 5) return m_input.substr(0,5) + "...";
        else return m_input;
    }

    // ----------------------------- NODES -----------------------------
    void Interpreter::statemachine() throw(JumpError) {
        while(!end()) {
            if (recieve(CONSTANT)) constant();
            else if (recieve(VARIABLE)) variable();
            else if (recieve(STREAM)) stream();
            else if (recieve(STATE)) state();
            else if (recieve(ENDLINE)) continue;
            else throw SyntaxError("Unexpected token " + peek() + " Expected const, var, stream, state, or ENDLINE");
        }
    }

    void Interpreter::constant() throw(JumpError) {
        require(IDENTIFIER, "IDENTIFIER after const");
        string id = recieved();
        require(ASSIGN, "= after IDENTIFIER (constants need to be set on declaration)");
        m_machine->constSet(id, feed());
        recieve(ENDLINE);
    }

    void Interpreter::variable() throw(JumpError) {
        require(IDENTIFIER, "IDENTIFIER after var");
        string id = recieved();
        if (recieved(ASSIGN)) m_machine->varSet(id, feed());
        recieve(ENDLINE);
    }

    void Interpreter::stream() throw(JumpError) {
        require(IDENTIFIER, "IDENTIFIER after stream");
        string id = recieved();
        require(ASSIGN, "= after IDENTIFIER");
        if (recieve(ARRAYSTREAM)) m_machine->streamSet(id, new ArrayStream());
        else throw SyntaxError("Unexpected token " + peek() + " Expected STREAMTYPE after =");
    }

    void Interpreter::state() throw(JumpError) {
        require(IDENTIFIER, "IDENTIFIER after state");
        string id = recieved();
        require(ENDLINE, "ENDLINE after state definition");
        m_state = new State(id);
        while(!end()) {
            if (recieve(READ)) read();
            else if (recieve(PRINT)) print();
            else if (recieve(TO)) to();
            else if (recieve(LOOP)) loop();
            else if (recieve(END)) end();
            else if (percieve(STATE)
                  || percieve(CONSTANT)
                  || percieve(VARIABLE)
                  || percieve(STREAM)) break;
            else feed();
        }
        m_machine.stateSet(m_state);
    }

    void Interpreter::print() throw(JumpError) {
        feed();
        string id = "stdout";
        if (recieve(PIPE)) {
            require(IDENTIFIER, "IDENTIFIER after ->");
            id = recieved();
        }
        m_state->add(new Print(m_value, id));
    }

    void Interpreter::read() throw(JumpError) {
        require(IDENTIFIER, "IDENTIFIER after read");
        string id1 = recieved(), id2;

        if (recieve(PIPE)) {
            require(IDENTIFIER, "IDENTIFIER after read");
            id2 = recieved();
            m_state->add(new Read(new Identifier(id2), id1));
        } else m_state->add(new Read(new Identifier(id1)));
    }

    void Interpreter::to() throw(JumpError) {
        require(IDENTIFIER, "IDENTIFIER after to");
        string id = recieved();

        if (recieve(IF)) {
            feed();
            m_state->add(new To(id, m_value));
        } else {
            recieve(OTHERWISE);
            m_state->add(new To(id));
        }
    }

    void Interpreter::end() throw(JumpError) {
        if (recieve(IF)) {
            feed();
            m_state->add(new End(m_value));
        } else {
            recieve(OTHERWISE);
            m_state->add(new End(new Boolean(true)));
        }
    }

    void Interpreter::loop() throw(JumpError) {
        if (recieve(IF)) {
            feed();
            m_state->add(new Loop(m_value));
        } else {
            recieve(OTHERWISE);
            m_state->add(new Loop(new Boolean(true)));
        }
    }

    // ------------------------------ EXPRESSION ------------------------------

    void Interpreter::feed() throw(JumpError) {

    }

    void Interpreter::feedop() throw(JumpError) {

    }

    void Interpreter::orr() throw(JumpError) {

    }

    void Interpreter::orop() throw(JumpError) {

    }

    void Interpreter::andd() throw(JumpError) {

    }

    void Interpreter::andop() throw(JumpError) {

    }

    void Interpreter::nott() throw(JumpError) {

    }

    void Interpreter::compare() throw(JumpError) {

    }

    void Interpreter::addsub() throw(JumpError) {

    }

    void Interpreter::addsubOp() throw(JumpError) {

    }

    void Interpreter::muldivmod() throw(JumpError) {

    }

    void Interpreter::muldivmodOp() throw(JumpError) {

    }

    void Interpreter::value() throw(JumpError) {

    }
}
