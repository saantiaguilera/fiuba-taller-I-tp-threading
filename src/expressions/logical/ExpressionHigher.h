/*
 * ExpressionHigher.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_LOGICAL_EXPRESSIONHIGHER_H_
#define EXPRESSIONS_LOGICAL_EXPRESSIONHIGHER_H_

#include <string>

/**
 * Expression that resembles the <
 */
class ExpressionHigher: public ExpressionLogical {
private:
	ExpressionHigher(const ExpressionHigher&);
	ExpressionHigher& operator=(const ExpressionHigher&);

protected:
	virtual bool operate(int leftValue, int rightValue);

public:
	explicit ExpressionHigher(ParserUtils *parserUtils);
	virtual ~ExpressionHigher();

	virtual std::string getTag();
};

#endif /* EXPRESSIONS_LOGICAL_EXPRESSIONHIGHER_H_ */
