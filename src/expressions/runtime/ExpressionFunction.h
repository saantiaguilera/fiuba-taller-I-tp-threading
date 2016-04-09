/*
 * ExpressionFunction.h
 *
 *  Created on: Apr 6, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_RUNTIME_EXPRESSIONFUNCTION_H_
#define EXPRESSIONS_RUNTIME_EXPRESSIONFUNCTION_H_

#include <string>

/**
 * Expression that resembles the DEFUN
 *
 * @Note: This defun doesnt feature recursivness
 * for itself (yes for others or even
 * different runtime expressions inside of it)
 *
 * This means:
 * (defun op (ENV) (* op (cdr ENV))) --> NO.
 */
class ExpressionFunction: public Expression {
private:
	ExpressionFunction(const ExpressionFunction&);
	ExpressionFunction& operator=(const ExpressionFunction&);

	std::string variableName; //The variable
	std::string functionName; //The defined function
	std::string body; //Body of the defined function

public:
	explicit ExpressionFunction(ParserUtils *parserUtils);
	virtual ~ExpressionFunction();

	virtual void parseBody(std::string line);
	virtual Expression * evaluate();
	Expression * mutate(std::string variable);

	virtual std::string getTag();
};

#endif /* EXPRESSIONS_RUNTIME_EXPRESSIONFUNCTION_H_ */
