# Jump

Jump is the first programming language that follows the state machine paradigm. State machines have a wide variety of applications including robotics programming, web design, game design, and app development. Jump is an easy, intuitive language for writing state machines for whatever projects you may be working on.

## Table of Contents
 - [The State Machine Paradigm](#the-state-machine-paradigm)
 - [The Jump Language](#the-jump-language)
 	- [States](#states)
 	- [Statements](#statements)
 		- [Print Statement](#print-statement)
 			- [Prompt Statement](#prompt-statement)
 		- [Read Statement](#read-statement)
 		- [To Statement](#to-statement)
 			- [Loop Statement](#loop-statement)
 			- [End Statement](#end-statement)

## The State Machine Paradigm

The state machine paradigm consists of designing stackless algorithms as a series of states which transition to each other.

A state machine language should have these fundamental components:

- A way to define states
- A conditional transition command that transfers to a given state if a given condition is true
- A defined entry state that is transitioned to at the start of the program
- A defined exit state that is transitioned to to end the program
- A defined default state that is transitioned to by default when a state block reaches end of execution (usually the exit state)
- Global tables of variables, constants, and IO streams that are referenced by all states
- Read and print statements which input and output data
- Data types like strings, numerical values, booleans, etc
- Expressions which operate on data and assign that data to variables

A simple state machine program can be written in pseudocode as follows:

	global constant VALUE = 2
	global variable difference = 0
	global variable input

	global iostream stdin

	state start
		prompt "Input value"
		read stdin into input
		transition to other

	state other
		print "I am dog"
		difference = value - input
		transition to final_a if difference > 1
		transition to final_b if difference == 1
		transition to final_c otherwise

	state final_a
		print "Difference is greater than 1"

	state final_b
		print "Difference is 1"

	state final_c
		print "Difference is less than 1"

## The Jump Language

### States

	state <name>

A state is defined using the `state` keyword, followed by a name for the state. After which, each line until the next declaration or the end of file is a statement declaration. 

### Statements

#### Print Statement

	print <value> [-> <stream>]

The `print` statement prints the given string (along with a newline character) to the output stream. Print statements are defined as follows:

##### Prompt Statement

	prompt <value> [-> <stream>]

A derivative of the `print` statement, the `prompt` statement prints a space instead of a newline after the string. This can be used for prompts to get inputs from the user.

#### Read Statement

	read [<stream> ->] <name>

The `read` statement reads a value from the input stream into the given variable.

#### To Statement

	to <name> [if <cond> | otherwise]

The `to` statement defines transitions. The `if` clause is an optional condition specifier which will only let the transition execute if the condition is true. The `otherwise` clause always evaluates to true and serves as a decorator for transition blocks.

##### Loop Statement

	loop [if <cond> | otherwise]

The `loop` statement is shorthand for a transition to the beginning of the current state.

##### End Statement

	end [if <cond> | otherwise]

The `end` statement is shorthand for a transition to the end state