//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "Jump/Compiler/grammarparser.h"

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
			 *		   is a declaration
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
				return tks.front().m_klass == "identifier";
			}

			/**
			 * Returns true if the next token in the given queue
			 * is an string
			 *
			 * @param tks the queue of tokens to check
			 *
			 * @return true if the next token in the given queue
			 *		   is an string
			 */
			static bool isString(queue<Token> tks)
			{
				return tks.front().m_klass == "string";
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
				return tks.front().m_klass == "endline";
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
					state->add(new Statements::To(tks.front().m_attribute));
					tks.pop();
				}
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

				// If next is string
				if (isString(tks))
				{
					// Add print statement with the string token
					state->add(new Statements::Print(tks.front().m_attribute));
					tks.pop();
				}
				// Else add blank print statement
				else state->add(new Statements::Print());
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

				// Endline
				endline(tks);
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
					State* state = new State(tks.front().m_attribute);
					tks.pop();
					endline(tks);

					// Parse statements until next state declaration (or end of program)
					while (continuing(tks) && !isDeclaration(tks))
						statement(state, tks);

					// Set state in machine
					machine.stateSet(state);
				}
				// Throw error
				else throw SyntaxError("Expected identifier after \"state\" keyword");
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
					declaration(machine, tks);
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