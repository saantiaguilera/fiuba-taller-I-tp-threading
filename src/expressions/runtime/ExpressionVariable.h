/*
 * ExpressionVariable.h
 *
 *  Created on: Apr 6, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_RUNTIME_EXPRESSIONVARIABLE_H_
#define EXPRESSIONS_RUNTIME_EXPRESSIONVARIABLE_H_

#include <string>

/**
 * Expression that resembles the SETQ
 */
class ExpressionVariable: public ExpressionCommon {
private:
	ExpressionVariable(const ExpressionVariable&);
	ExpressionVariable& operator=(const ExpressionVariable&);

	std::string body;
	std::string variableName;

public:
	explicit ExpressionVariable(ParserUtils *parserUtils);
	virtual ~ExpressionVariable();

	virtual void parseBody(std::string line);
	virtual Expression * evaluate();
	Expression * mutate();

	virtual std::string getTag();
};

#endif /* EXPRESSIONS_RUNTIME_EXPRESSIONVARIABLE_H_ */
