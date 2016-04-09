/*
 * ExpressionLower.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_LOGICAL_EXPRESSIONLOWER_H_
#define EXPRESSIONS_LOGICAL_EXPRESSIONLOWER_H_

#include <string>

class ExpressionLower: public ExpressionLogical {
private:
	ExpressionLower(const ExpressionLower&);
	ExpressionLower& operator=(const ExpressionLower&);

public:
	explicit ExpressionLower(ParserUtils *parserUtils);
	virtual ~ExpressionLower();
	virtual bool operate(int leftValue, int rightValue);
	virtual std::string getTag();
};

#endif /* EXPRESSIONS_LOGICAL_EXPRESSIONLOWER_H_ */
