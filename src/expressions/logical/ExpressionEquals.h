/*
 * ExpressionEquals.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_EXPRESSIONEQUALS_H_
#define EXPRESSIONS_EXPRESSIONEQUALS_H_

#include <string>

/**
 * Expression that resembles the =
 */
class ExpressionEquals: public ExpressionLogical {
private:
	ExpressionEquals(const ExpressionEquals&);
	ExpressionEquals& operator=(const ExpressionEquals&);

protected:
	virtual bool operate(int leftValue, int rightValue);

public:
	explicit ExpressionEquals(ParserUtils *parserUtils);
	virtual ~ExpressionEquals();

	virtual std::string getTag();
};

#endif /* EXPRESSIONS_EXPRESSIONEQUALS_H_ */
