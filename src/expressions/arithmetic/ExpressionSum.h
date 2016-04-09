/*
 * ExpressionSum.h
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONSUM_H_
#define EXPRESSIONSUM_H_

#include <string>

class ExpressionSum: public ExpressionArithmetic {
private:
	ExpressionSum(const ExpressionSum&);
	ExpressionSum& operator=(const ExpressionSum&);

protected:
	virtual int operate(int dest, int src);

public:
	explicit ExpressionSum(ParserUtils *parserUtils);
	virtual ~ExpressionSum();

	virtual std::string getTag();
};

#endif /* EXPRESSIONSUM_H_ */
