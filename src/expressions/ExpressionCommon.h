/*
 * ExpressionsCommon.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_EXPRESSIONCOMMON_H_
#define EXPRESSIONS_EXPRESSIONCOMMON_H_

const char SYMBOL_PARENTHESIS_OPEN = '(';
const char SYMBOL_PARENTHESIS_CLOSE = ')';
const char SYMBOL_SPACE = ' ';
const char SYMBOL_QUOTATIONS = '"';

#include <string>

/**
 * Abstract class that inherits Expression
 * This class resembles a common expression being able to:
 * - Parse the default body (Not setq/defun stuff)
 * (Can parse inner expressions)
 * - Inject the expression to a particular place.
 * (By default its the environment, but its overridable)
 */
class ExpressionCommon: public Expression {
private:
	ExpressionCommon(const ExpressionCommon&);
	ExpressionCommon& operator=(const ExpressionCommon&);

	void parseInnerExpression(std::string &line, int startPosition);

protected:
	virtual void injectExpression(Expression *expression);

public:
	explicit ExpressionCommon(ParserUtils *parserUtils);
	virtual ~ExpressionCommon();

	virtual std::string getTag() = 0;

	virtual void parseBody(std::string line);
	virtual Expression * evaluate() = 0;
};

#endif /* EXPRESSIONS_EXPRESSIONCOMMON_H_ */
