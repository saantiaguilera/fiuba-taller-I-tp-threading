/*
 * ParserUtils.cpp
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#include <string>
#include <list>
#include <cstdio>
#include <cctype>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <stdexcept>

class Expression;

#include "threading/Mutex.h"

#include "ParserUtils.h"

#include "Expression.h"

#include "expressions/ExpressionCommon.h"

#include "expressions/logical/ExpressionLogical.h"
#include "expressions/arithmetic/ExpressionArithmetic.h"

#include "expressions/arithmetic/ExpressionSum.h"
#include "expressions/misc/ExpressionConstant.h"
#include "expressions/arithmetic/ExpressionMultiply.h"
#include "expressions/arithmetic/ExpressionDivide.h"
#include "expressions/arithmetic/ExpressionSubstraction.h"
#include "expressions/logical/ExpressionEquals.h"
#include "expressions/logical/ExpressionLower.h"
#include "expressions/logical/ExpressionHigher.h"
#include "expressions/list/ExpressionFrontList.h"
#include "expressions/list/ExpressionList.h"
#include "expressions/list/ExpressionTailList.h"
#include "expressions/logical/ExpressionIf.h"
#include "expressions/misc/ExpressionPrint.h"
#include "expressions/runtime/ExpressionFunction.h"
#include "expressions/runtime/ExpressionVariable.h"
#include "expressions/runtime/ExpressionSync.h"
#include "expressions/list/ExpressionAppend.h"

#include "threading/ReentrantLock.h"
#include "threading/Thread.h"
#include "threading/ParserWorker.h"

/**
 * Inner class for using as predicative
 * Overrides the operator()
 */
class IsFunction {
public:
	IsFunction() {
	}

	bool operator()(char c) {
		return c == SYMBOL_PARENTHESIS_OPEN || c == SYMBOL_PARENTHESIS_CLOSE;
	}
};

/**
 * @Private
 * @Note: This list will hold the current
 * threads that are alive
 */
std::list<Thread*> threads;

/**
 * @Public
 * @Constructor
 */
ParserUtils::ParserUtils() {
	runtimeFunctions = new std::map<std::string, Expression*>();
	runtimeVariables = new std::map<std::string, Expression*>();
}

/**
 * @Private
 * @MainThread
 * @Note: This joins each thread, and then deletes them from the
 * thread list. There cant be race conditions since we are
 * in the main UI and other threads dont have access to
 * the thread list (list is in the stack of the main thread)
 */
void cleanThreads() {
	for (std::list<Thread*>::iterator threadIterator = threads.begin();
			threadIterator != threads.end(); ++threadIterator) {
		(*threadIterator)->join();

		if (*threadIterator != NULL) {
			delete *threadIterator;
			*threadIterator = NULL;
		} //While iterating clean the list
	}

	//Clear the corrupted nodes
	threads.clear();
}

/**
 * @note: I know this shouldnt be like this
 * (its a bad smell to implement the if != NULL
 * then delete.
 * But since the Runtime functions need to last
 * till end of program and they will be
 * inside other expressions
 * They will be double removed and this will crash.
 * Solution could be to use a copy constructor.
 * But that would use a lot more heap
 * and I prefer 6 bad smell lines than 2x heap
 */
ParserUtils::~ParserUtils() {
	for (std::map<std::string, Expression*>::iterator it =
			runtimeVariables->begin(); it != runtimeVariables->end(); ++it) {
		if (it->second != NULL) {
			delete it->second;
			it->second = NULL;
		}
	}

	for (std::map<std::string, Expression*>::iterator it =
			runtimeFunctions->begin(); it != runtimeFunctions->end(); ++it) {
		if (it->second != NULL) {
			delete it->second;
			it->second = NULL;
		}
	}

	cleanThreads();

	cleanHistory();

	delete runtimeVariables;
	delete runtimeFunctions;
}

/**
 * @Private
 * @Note: Cleans the history of evaluated
 * expressions.
 */
void ParserUtils::cleanHistory() {
	for (std::list<Expression*>::iterator it = history.begin();
			it != history.end(); ++it) {
		if (*it != NULL) {
			delete *it;
			*it = NULL;
		}
	}

	//Clear the corrupted nodes
	history.clear();
}

/**
 * @Public
 * @Note Parses a Lisp line and then
 * evaluates it.
 */
void ParserUtils::run(std::string &line) {
	//This is done in the main thread, because we need to catch sync
	Expression *expression = parseExpression(line);

	/**
	 * Since DEFUN and SETQ are in runtime
	 * They need to have the lifetime of
	 * the parser.
	 * So only add to history "short spawned"
	 * expressions
	 */
	if (expression->getTag() != EXPRESSION_DEFUN
			&& expression->getTag() != EXPRESSION_SETQ)
		history.push_back(expression);

	/**
	 * Ideally the best would be to use a
	 * interface (abstract class in this case)
	 * that has a onJoinThreads() and this is
	 * triggered by the sync expression in his
	 * evaluate().
	 * But since evaluate() wont be done on the main
	 * thread, we cant do this approach
	 * else the JOIN will be done from a different
	 * thread, and this is not what we want.
	 */
	if (expression->getTag() == EXPRESSION_SYNC) {
		//GC the threads (This first joins them)
		cleanThreads();

		//GC the history
		cleanHistory();
	} else {
		//Its a common expression, spawn a worker
		ParserWorker *thread = new ParserWorker(expression);

		//Append it to the "threads that are running"
		threads.push_back(thread);

		//Start the thread
		thread->start();
	}
}

/**
 * @Public
 * @Note This is awful
 * @Note Although I couldnt find any
 * good approach for this, one that was far more
 * better than this was:
 * - Create a factory class like this:
 * class Factory {
 * public:
 *      virtual Expression * build() = 0;
 * }
 *
 * And then for each do a
 * class FactorySum : public Factory {
 *      virtual Expression * build() {
 *            return new ExpressionSum();
 *      }
 * }
 *
 * But this would make me have 2x classes and
 * Since I have dirs to make it more readable
 * And the Sercom cant manage dirs (or the make
 * failed when I used dirs) I didnt do this
 * (Simple because of laziness. But know
 * that it was the same result but with a
 * better approach :D)
 *
 * @Returns the particular expression that matches
 * the given string.
 * Eg. string: + --> ExpressionSum
 */
Expression * ParserUtils::expressionFromKnownStrings(std::string &string) {
	if (string == EXPRESSION_SUM)
		return new ExpressionSum(this);
	if (string == EXPRESSION_SUBSTRACTION)
		return new ExpressionSubstraction(this);
	if (string == EXPRESSION_MULTIPLY)
		return new ExpressionMultiply(this);
	if (string == EXPRESSION_DIVIDE)
		return new ExpressionDivide(this);
	if (string == EXPRESSION_EQUALS)
		return new ExpressionEquals(this);
	if (string == EXPRESSION_HIGHER)
		return new ExpressionHigher(this);
	if (string == EXPRESSION_LOWER)
		return new ExpressionLower(this);
	if (string == EXPRESSION_LIST)
		return new ExpressionList(this);
	if (string == EXPRESSION_CAR)
		return new ExpressionFrontList(this);
	if (string == EXPRESSION_CDR)
		return new ExpressionTailList(this);
	if (string == EXPRESSION_APPEND)
		return new ExpressionAppend(this);
	if (string == EXPRESSION_IF)
		return new ExpressionIf(this);
	if (string == EXPRESSION_DEFUN)
		return new ExpressionFunction(this);
	if (string == EXPRESSION_PRINT)
		return new ExpressionPrint(this);
	if (string == EXPRESSION_SETQ)
		return new ExpressionVariable(this);
	if (string == EXPRESSION_SYNC)
		return new ExpressionSync(this);

	//If its a number or it has "" its a constant !!
	if ((string.find_first_not_of("0123456789") == std::string::npos)
			|| string.find(SYMBOL_QUOTATIONS) != std::string::npos)
		return new ExpressionConstant(this);
	else //Damn, they invoked something that doesnt exist.
		throw std::logic_error(EXCEPTION_BAD_FUNCTION);
}

/**
 * @Public
 * @Returns an expression from a function
 * Eg: line = * --> ExpressionMultiply
 */
Expression * ParserUtils::expressionFromFunction(std::string &line) {
	return expressionFromKnownStrings(line);
}

/**
 * @Public
 * @Returns a runtime expression (An expression that was
 * defined by the user)
 */
Expression * ParserUtils::expressionFromRuntime(std::string &tag) {
	/**
	 * This cant produce a race condition
	 * Since there are not changes in the
	 * shared data
	 */
	for (std::map<std::string, Expression*>::iterator it =
			runtimeFunctions->begin(); it != runtimeFunctions->end(); ++it)
		if (it->first == tag)
			return it->second;

	//Oops, we didnt found that runtime expression
	return NULL;
}

/**
 * @Public
 * @Param line: A complete Lisp line
 * Eg. (+ 45 2)
 *
 * @Return the body of the Lisp line
 * Eg. (+ 45 2) --> 45 2
 */
std::string ParserUtils::bodyToString(std::string &line) {
	std::string function = functionToString(line);
	int start = line.find(function) + function.length() + 1;
	int end = line.find_last_of(SYMBOL_PARENTHESIS_CLOSE);

	if (end > 0)
		return line.substr(start,
				end - line.find(function) - function.length() - 1);

	//It has to be a literal or a constant (since they dont have body)
	throw std::logic_error(EXCEPTION_NO_BODY);
}

/**
 * @Public
 * @Param line: A complete Lisp line
 * Eg. (+ 45 2)
 *
 * @Return the function of the Lisp line
 * Eg. (+ 45 2) --> +
 */
std::string ParserUtils::functionToString(std::string line) {
	std::istringstream iss(line);

	std::string result;
	iss >> result;

	result.erase(std::remove_if(result.begin(), result.end(), IsFunction()),
			result.end());

	return result;
}

/**
 * @Public
 *
 * @Param line A complete Lisp line
 *
 * @Note: Runtime functions held more priority
 * than the Lisp defined ones.
 * Eg. If there is a runtime function that was also
 * called "+". It will be used the runtime one.
 *
 * @Returns an expression that represents
 * the Lisp line
 */
Expression * ParserUtils::parseExpression(std::string &line) {
	//Get the expression according to the symbol
	std::string function = functionToString(line);

	//Check if the function is from runtime
	Expression *expression = expressionFromRuntime(function);

	//Get the body
	std::string stuff;
	try {
		stuff = bodyToString(line);
	} catch (const std::logic_error &exception) {
		//If there is no body it means the function itself is a constant
		//Or a literal
		if (exception.what() == EXCEPTION_NO_BODY)
			stuff = function;
	}

	try {
		if (expression != NULL) { //Runtime expression
			//Return a mutation !
			expression = ((ExpressionFunction*) expression)->mutate(stuff);
		} else { //Local expression
			expression = expressionFromFunction(function);
			expression->parseBody(stuff);
		}
	} catch (const std::logic_error &exception) {
		//There was a problem parsing or mutating the expression.
		//Delete it to avoid a leak and pass the ex.
		delete expression;
		throw exception;
	}

	return expression;
}

/**
 * @Public
 *
 * @Returns a expression from a constant.
 *
 * @Note: Constant can be either a number or a literal
 * Eg. "Hello" // 45 are both constants
 */
Expression * ParserUtils::expressionFromConstant(std::string line) {
	Expression *expression = new ExpressionConstant(this);
	expression->parseBody(line);

	return expression;
}

/**
 * @Public
 *
 * @Returns an expression from a runtime variable (setq)
 */
Expression * ParserUtils::expressionFromVariable(std::string tag) {
	/**
	 * @Note: This can produce a race condition
	 * Since someone can try to use the
	 * same expression* while its mutating
	 *
	 * Iterate through our runtime variables and if
	 * its found, return a mutation.
	 */
	for (std::map<std::string, Expression*>::iterator it =
			runtimeVariables->begin(); it != runtimeVariables->end(); ++it)
		if (it->first == tag) {
			ReentrantLock lock(mutex);
			return (((ExpressionVariable*) (it->second))->mutate());
		}

	//Damn, that variable doesnt exist !!
	return NULL;
}

/**
 * @Public
 *
 * @Note: Adds to the runtime functions a new one
 * with a given tag and its expression.
 *
 * @Warning: Expression must be of type ExpressionFunction
 * Else it wont be able to be mutated when retrieved.
 *
 * (TODO Make this method receive a ExpressionFunction *
 * instead of Expression *)
 */
Expression * ParserUtils::appendRuntimeFunction(std::string tag,
		Expression *expression) {
	/**
	 * This can produce a race condition
	 * Since someone can be accessing the shared
	 * data while we are deleting / changing
	 * the function
	 */
	ReentrantLock lock(mutex);

	if (runtimeFunctions->find(tag) != runtimeFunctions->end())
		delete (*runtimeFunctions)[tag];

	(*runtimeFunctions)[tag] = expression;

	return expression;
}

/**
 * @Public
 *
 * @Note: Adds to the runtime variables a new one
 * with a given tag and its Expression
 *
 * @Warning: Expression must be of type ExpressionVariable
 * Else it wont be able to be mutated when retrieved.
 *
 * (TODO Make this method receive a ExpressionVariable *
 * instead of Expression *)
 */
Expression * ParserUtils::appendRuntimeVariable(std::string tag,
		Expression *expression) {
	/**
	 * This can produce a race condition
	 * Since someone can be accessing the shared
	 * data while we are deleting / changing
	 * the function
	 */
	ReentrantLock lock(mutex);

	if (runtimeVariables->find(tag) != runtimeVariables->end())
		delete (*runtimeVariables)[tag];

	(*runtimeVariables)[tag] = expression;

	return expression;
}
