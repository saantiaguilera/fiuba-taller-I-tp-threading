/*
 * ExpressionLower.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_LOGICAL_EXPRESSIONLOWER_H_
#define EXPRESSIONS_LOGICAL_EXPRESSIONLOWER_H_

#include <string>

/**
 * Expression that resembles the <
 */
class ExpressionLower: public ExpressionLogical {
private:
	ExpressionLower(const ExpressionLower&);
	ExpressionLower& operator=(const ExpressionLower&);

protected:
	virtual bool operate(int leftValue, int rightValue);

public:
	explicit ExpressionLower(ParserUtils *parserUtils);
	virtual ~ExpressionLower();

	virtual std::string getTag();
};

#endif /* EXPRESSIONS_LOGICAL_EXPRESSIONLOWER_H_ */
