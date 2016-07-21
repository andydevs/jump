# Jump

Jump is the first programming language that follows the state machine paradigm. State machines have a wide variety of applications including robotics programming, web design, game design, and app development. Jump is an easy, intuitive language for writing state machines for whatever projects you may be working on.

## Table of Contents
 - [The State Machine Paradigm](#the-state-machine-paradigm)
 - [The Jump Language](#the-jump-language)
 	- [States and Transitions](#states-and-transitions)

## The State Machine Paradigm

The state machine paradigm consists of designing algorithms as a series of states which represent different parts of the algorithm.

A state machine language should have these fundamental components:

- A way to define states
- A conditional transition command that transfers to a given state if a given condition is true
- A defined entry state that is transitioned to at the start of the program
- A defined exit state that is transitioned to by default when a state block reaches end of execution
- Global tables of variables, constants, and IO streams that are referenced by all states

A simple state machine program can be written in pseudocode as follows:

	global variable value = 2

	state start
		print "Hello world"
		transition to other

	state other
		print "I am dog"
		transition to final_a if value is greater than 1
		transition to final_b if value is equal to 1
		transition to final_c otherwise

	state final_a
		print "Value is greater than 1"

	state final_b
		print "Value is 1"

	state final_c
		print "Value is less than 1"

## The Jump Language

### States and Transitions

States are defined as follows:

	state <name>

After which, each line until the next declaration or the end of file is a statement declaration. 

Within the state, transitions are defined using the `to` statement as follows:

	to <name> [if <cond>]

### Statements

#### Print Statement

The `print` statement prints the given string to the output stream. Print statements are defined as follows:

	print "Hello World"