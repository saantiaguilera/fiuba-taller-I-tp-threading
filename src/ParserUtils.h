/*
 * ParserUtils.h
 *
 *  Created on: Apr 3, 2016
 *      Author: santiago
 */

#ifndef PARSERUTILS_H_
#define PARSERUTILS_H_

/**
 * Im gonna be using the what() argument instead of
 * creating 2 exceptions class.
 */
const std::string EXCEPTION_BAD_FUNCTION = "BadFunction";
const std::string EXCEPTION_NO_BODY = "NoBody";

#include <map>
#include <string>
#include <list>

/**
 * Class for the parser.
 * Maybe it had to be named LispParser ?
 */
class ParserUtils {
private:
	//Mutex for multithreading
	Mutex mutex;

	/**
	 * Inner variables.
	 *
	 * @param runtimeVariables is a list
	 * that contains all the user defined
	 * variables (setq)
	 *
	 * @param runtimeFunctions is a list
	 * that contains all the user defined
	 * functions (defun)
	 *
	 * @param history is a history of all
	 * the expressions parsed + evaluated.
	 * Purpose of history is to be able to
	 * clean it once a sync is made (because
	 * we wont need those expressions anymore)
	 * This could be achievend by deleting each
	 * after they were evaluated, but there were
	 * problems with the recursion I think ?
	 * I dont remember why I couldnt achieve it
	 * like that.
	 *
	 * In other words, history works as a GC
	 */
	std::map<std::string, Expression*> * runtimeVariables;
	std::map<std::string, Expression*> * runtimeFunctions;
	std::list<Expression*> history;

	//Private method to run the GC
	void cleanHistory();

	//Private method to help parse a line into sections
	std::string bodyToString(std::string &line);
	std::string functionToString(std::string line);

public:
	ParserUtils();
	~ParserUtils();

	//Parse and evaluate a Lisp line
	void run(std::string &line);

	/**
	 * Careful with the usage of the methods below
	 * They all act for getting a particular expression
	 * While parseExp() is the generic one
	 * All the others are for getting a desired one
	 * Eg. expressionFromFunction will give an expression
	 * from the known lisp functions (+ * - / list.....)
	 */

	Expression * parseExpression(std::string &line);

	Expression * expressionFromConstant(std::string line);
	Expression * expressionFromVariable(std::string tag);
	Expression * expressionFromKnownStrings(std::string &string);
	Expression * expressionFromFunction(std::string &line);
	Expression * expressionFromRuntime(std::string &line);

	/**
	 * Both methods below are for appending a variable or
	 * function to the runtime with a given tag
	 */

	Expression * appendRuntimeVariable(std::string tag, Expression *expression);
	Expression * appendRuntimeFunction(std::string tag, Expression *expression);
};

#endif /* PARSERUTILS_H_ */
