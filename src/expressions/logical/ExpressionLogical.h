/*
 * ExpressionLogical.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_LOGICAL_EXPRESSIONLOGICAL_H_
#define EXPRESSIONS_LOGICAL_EXPRESSIONLOGICAL_H_

#include <string>

class ExpressionLogical: public ExpressionCommon {
private:
	ExpressionLogical(const ExpressionLogical&);
	ExpressionLogical& operator=(const ExpressionLogical&);

protected:
	virtual bool operate(int leftValue, int rightValue) = 0;

public:
	explicit ExpressionLogical(ParserUtils *parserUtils);
	virtual ~ExpressionLogical();

	virtual std::string getTag() = 0;

	virtual Expression * evaluate();
	virtual std::string toString();
};

#endif /* EXPRESSIONS_LOGICAL_EXPRESSIONLOGICAL_H_ */
