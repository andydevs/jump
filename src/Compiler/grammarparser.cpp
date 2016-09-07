/*

Program: Jump

Jump is a new programming language that uses the state machine paradigm

Author:  Anshul Kharbanda
Created: 7 - 15 - 2016

*/

// Headers being used
#include "Jump/Compiler/grammarparser.h"
#include "Jump/Core/Statements/statements.h"
#include "Jump/Core/Values/identifier.h"
#include "Jump/Core/Values/string.h"
#include "Jump/Core/Values/null.h"
#include "Jump/Core/Values/Numbers/parser.h"
#include "Jump/Core/Values/expression.h"

// Libraries being used
#include <cstdlib>
#include <string>
#include <iostream>

// Namespaces being used
using namespace std;
using namespace Jump::Core;
using namespace Jump::Compiler::TokenParser;

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
		 * Performs grammar analysis on a token queue
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 18 - 2016
		 */
		namespace GrammarParser
		{
			// ----------------------- MATCHERS -----------------------

			/**
			 * Returns true if the next token in the given queue
			 * is an operation and equals the given operation
			 *
			 * @param tks  the queue of tokens to check
			 * @param oper the operation to check for
			 *
			 * @return true if the next token in the given queue
			 *		   is an operation and equals the given operation
			 */
			static bool isOperation(queue<Token> tks, string oper)
			{
				return tks.front() == Token("operation", oper);
			}

			/**
			 * Returns true if the next token in the given queue
			 * is a lparen
			 *
			 * @param tks the queue of tokens to check
			 *
			 * @return true if the next token in the given queue
			 *		   is a lparen
			 */
			static bool isLparen(queue<Token> tks)
			{
				return tks.front().klass() == "lparen";
			}

			/**
			 * Returns true if the next token in the given queue
			 * is a rparen
			 *
			 * @param tks the queue of tokens to check
			 *
			 * @return true if the next token in the given queue
			 *		   is a rparen
			 */
			static bool isRparen(queue<Token> tks)
			{
				return tks.front().klass() == "rparen";
			}

			/**
			 * Returns true if the next token in the given queue
			 * is a keyword
			 *
			 * @param tks the queue of tokens to check
			 *
			 * @return true if the next token in the given queue
			 *		   is a keyword
			 */
			static bool isKeyword(queue<Token> tks)
			{
				return tks.front().klass() == "keyword";
			}

			/**
			 * Returns true if the next token in the given queue
			 * is a keyword and equals the given word
			 *
			 * @param tks  the queue of tokens to check
			 * @param word the word to check for
			 *
			 * @return true if the next token in the given queue
			 *		   is a keyword and equals the given word
			 */
			static bool isKeyword(queue<Token> tks, string word)
			{
				return tks.front() == Token("keyword", word);
			}

			/**
			 * Returns true if the next token in the given queue
			 * is a statemachine declaration
			 *
			 * @param tks  the queue of tokens to check
			 *
			 * @return true if the next token in the given queue
			 *		   is a statemachine declaration
			 */
			static bool isDeclaration(queue<Token> tks)
			{
				return isKeyword(tks, "state");
			}

			/**
			 * Returns true if the next token in the given queue
			 * is an identifier
			 *
			 * @param tks the queue of tokens to check
			 *
			 * @return true if the next token in the given queue
			 *		   is an identifier
			 */
			static bool isIdentifier(queue<Token> tks)
			{
				return tks.front().klass() == "identifier";
			}

			/**
			 * Returns true if the next token in the given queue
			 * is a string
			 *
			 * @param tks the queue of tokens to check
			 *
			 * @return true if the next token in the given queue
			 *		   is a string
			 */
			static bool isString(queue<Token> tks)
			{
				return tks.front().klass() == "string";
			}

			/**
			 * Returns true if the next token in the given queue
			 * is a number
			 *
			 * @param tks the queue of tokens to check
			 *
			 * @return true if the next token in the given queue
			 *		   is a number
			 */
			static bool isNumber(queue<Token> tks)
			{
				return tks.front().klass() == "number";
			}

			/**
			 * Returns true if the next token in the given queue
			 * is a value
			 *
			 * @param tks the queue of tokens to check
			 *
			 * @return true if the next token in the given queue
			 *		   is a value
			 */
			static bool isValue(queue<Token> tks)
			{
				return isString(tks) || isNumber(tks) 
					|| isIdentifier(tks) || isLparen(tks);
			}

			/**
			 * Returns true if the next token in the given queue
			 * is an endline
			 *
			 * @param tks the queue of tokens to check
			 *
			 * @return true if the next token in the given queue
			 *		   is an endline
			 */
			static bool isEndline(queue<Token> tks)
			{
				return tks.front().klass() == "endline" || tks.front().klass() == "EOF";
			}

			/**
			 * Returns true if the given token queue is at the end 
			 * (and there are remaining tokens)
			 *
			 * @param tks the queue of tokens to check
			 *
			 * @return true if the given token queue is at the end 
			 *		   (and there are remaining tokens)
			 */
			static bool continuing(queue<Token> tks)
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
				if (isString(tks))
				{
					val = new Values::String(literal.substr(1, literal.length() - 2));
				}
				else if (isNumber(tks))
				{
					val = Values::Numbers::parse(literal.c_str());
				}
				else if (isIdentifier(tks))
				{
					val = new Values::Identifier(literal);
				}
				else if (isLparen(tks))
				{
					tks.pop();
					val = expression(tks);
					if (!isRparen(tks)) throw SyntaxError("Expected RPAREN");
				}
				else
				{
					throw SyntaxError("Unexpected token " + tks.front().toString() +  ". Expected Value Type");
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
				return addsub(tks);
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
					// Add to statement with the identifier token
					state->add(new Statements::To(tks.front().attribute()));
					tks.pop();
				}
				// Else throw SyntaxError
				else throw SyntaxError("Expected identifier after \"to\" keyword");
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

				// If next is value
				if (isValue(tks))
				{
					// Add print statement with the value token
					state->add(new Statements::Print(expression(tks)));
				}
				// Else if endline add blank print statement
				else if (isEndline(tks))
					state->add(new Statements::Print());
				// Else throw SyntaxError
				else
					throw SyntaxError("Unexpected token " + tks.front().toString() + ". expected ValueType or Endline");
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
				if (isKeyword(tks, "print"))
					print(state, tks);
				else if (isKeyword(tks, "to"))
					to(state, tks);
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

				// If assignment is given, set value, else set to null
				if (isOperation(tks, "="))
				{
					tks.pop();
					machine.constSet(name, expression(tks));
				}
				else throw SyntaxError("Expected = after constant declaration.");

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
				else
					throw SyntaxError("Unexpected StateMachine keyword: " + tks.front().attribute());
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

			// ------------------------ PARSE --------------------------

			/**
			 * Parses the given token queue into a StateMachine
			 *
			 * @param tks the tokens to parse into the StateMachine
			 *
			 * @return the StateMachine that was parsed
			 *
			 * @throw SyntaxError if an invalid token was detected
			 */
			StateMachine parse(queue<Token>& tks) throw(SyntaxError)
			{
				// Parse machine
				StateMachine machine;
				statemachine(machine, tks);

				// Return machine
				return machine;
			}
		}
	}
}