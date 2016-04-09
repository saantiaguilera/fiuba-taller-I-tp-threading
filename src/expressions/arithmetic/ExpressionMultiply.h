/*
 * ExpressionMultiply.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_EXPRESSIONMULTIPLY_H_
#define EXPRESSIONS_EXPRESSIONMULTIPLY_H_

#include <string>

class ExpressionMultiply: public ExpressionArithmetic {
private:
	ExpressionMultiply(const ExpressionMultiply&);
	ExpressionMultiply& operator=(const ExpressionMultiply&);

protected:
	virtual int operate(int dest, int src);

public:
	explicit ExpressionMultiply(ParserUtils *parserUtils);
	virtual ~ExpressionMultiply();

	virtual std::string getTag();
};

#endif /* EXPRESSIONS_EXPRESSIONMULTIPLY_H_ */
