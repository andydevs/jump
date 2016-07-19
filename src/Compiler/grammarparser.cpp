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
			 *
			 * @return status code of parses
			 */
			static int endline(queue<Token>& tks)
			{
				// Pop next token
				if (isEndline(tks)) tks.pop();

				// Return ok
				return 0;
			}

			// -------------- STATEMENTS --------------

			/**
			 * Parses a to statement
			 *
			 * @param state the state to add the statement to
			 * @param tks   the token queue to parse
			 *
			 * @return status code of parses
			 */
			static int to(State* state, queue<Token>& tks)
			{
				// Next token
				tks.pop();

				// If next is identifier
				if (isIdentifier(tks))
				{
					// Add to statement with the identifier token
					state->add(new Statements::To(tks.front().m_attribute));
					tks.pop();

					// Return ok
					return 0;
				}
				// Return error
				else return 1;
			}

			/**
			 * Parses a print statement
			 *
			 * @param state the state to add the statement to
			 * @param tks   the token queue to parse
			 *
			 * @return status code of parses
			 */
			static int print(State* state, queue<Token>& tks)
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
				else state->add(new Statements::Print(""));

				// Return exit
				return 0;
			}

			/**
			 * Parses a statement
			 *
			 * @param state the state to add the statement to
			 * @param tks   the token queue to parse
			 *
			 * @return status code of parses
			 */
			static int statement(State* state, queue<Token>& tks)
			{
				// Parse Statements
				if (isKeyword(tks, "print"))
				{
					if (!print(state, tks)) return 1;
				}
				else if (isKeyword(tks, "to"))
				{
					if (!to(state, tks)) return 1;
				}

				// Endline
				endline(tks);

				// Return ok
				return 0;
			}

			// -------------- STATEMACHINE --------------

			/**
			 * Parses a state
			 *
			 * @param machine the StateMachine to add the state to
			 * @param tks     the token queue to parse
			 *
			 * @return status code of parses
			 */
			static int state(StateMachine& machine, queue<Token>& tks)
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

					// Parse statements until next state declaration
					while (!isKeyword(tks, "state") && continuing(tks))
						if (!statement(state, tks)) return 1;

					// Set state in machine
					machine.stateSet(state);

					// Return ok
					return 0;
				}
				// Return error
				else return 1;
			}

			/**
			 * Parses a StateMachine declaration
			 *
			 * @param machine the StateMachine to parse
			 * @param tks     the token queue to parse
			 *
			 * @return status code of parses
			 */
			static int declaration(StateMachine& machine, queue<Token>& tks)
			{
				// Parse declaration
				if (isKeyword(tks, "state"))
					if (!state(machine, tks)) return 1;

				// Return ok
				return 0;
			}

			/**
			 * Parses a StateMachine
			 *
			 * @param machine the StateMachine to parse
			 * @param tks     the token queue to parse
			 *
			 * @return status code of parses
			 */
			static int statemachine(StateMachine& machine, queue<Token>& tks)
			{
				// Parse state machine declarations
				while (continuing(tks))
					if (!declaration(machine, tks)) return 1;

				// Return ok
				return 0;
			}

			// ------------------------ PARSE --------------------------

			/**
			 * Parses the given token queue into the given StateMachine
			 *
			 * @param machine the StateMachine to be parsed
			 * @param tks     the tokens to parse into the StateMachine
			 *
			 * @return status code to parse
			 */
			int parse(StateMachine& machine, queue<Token>& tks)
			{
				// Parse statemachine and return error code
				return statemachine(machine, tks);
			}
		}
	}
}