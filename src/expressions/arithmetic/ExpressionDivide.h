/*
 * ExpressionDivide.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_EXPRESSIONDIVIDE_H_
#define EXPRESSIONS_EXPRESSIONDIVIDE_H_

#include <string>

class ExpressionDivide: public ExpressionArithmetic {
private:
	ExpressionDivide(const ExpressionDivide&);
	ExpressionDivide& operator=(const ExpressionDivide&);

protected:
	virtual int operate(int dest, int src);

public:
	explicit ExpressionDivide(ParserUtils *parserUtils);
	virtual ~ExpressionDivide();

	virtual std::string getTag();
};

#endif /* EXPRESSIONS_EXPRESSIONDIVIDE_H_ */
