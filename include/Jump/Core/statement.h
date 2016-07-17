//-----------------------------------------------------------------------------------
// Program: Jump
// 
// Jump is a new programming language that uses the state machine paradigm
//
// Author:  Anshul Kharbanda
// Created: 7 - 15 - 2016
//-----------------------------------------------------------------------------------

#ifndef _CORE_STATEMENT_H_
#define _CORE_STATEMENT_H_

// Libraries being used
#include <string>

/**
 * Jump is a new programming language that uses the state machine paradigm
 *
 * @author  Anshul Kharbanda
 * @created 7 - 15 - 2016
 */
namespace Jump
{
	/**
	 * The core program
	 *
	 * @author  Anshul Kharbanda
	 * @created 7 - 16 - 2016
	 */
	namespace Core
	{
		/**
		 * A single statement in the Jump program
		 *
		 * @author  Anshul Kharbanda
		 * @created 7 - 16 - 2016
		 */
		class Statement
		{
		protected:
			/**
			 * The condition being checked
			 */
			bool m_condition;
		public:
			/**
			 * Creates an empty Statement
			 */
			Statement();

			/**
			 * Creates a Statement with the given condition
			 *
			 * @param condition the condition being checked
			 */
			Statement(bool condition);

			/**
			 * Copy constructor
			 *
			 * @param other the Statement to copy
			 */
			Statement(const Statement& other);

			/**
			 * Destroys the Statement
			 */
			~Statement();

			/**
			 * Executes the statement
			 *
			 * @return a reference to the next state (the state's name)
			 */
			std::string execute();

			/**
			 * Executes the Statement if the condition is true
			 *
			 * @return a reference to the next state (the state's name)
			 */
			virtual std::string conditionedExecute() = 0;
		};
	}
}

#endif