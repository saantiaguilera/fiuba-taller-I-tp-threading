/*
 * ExpressionConstant.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONCONSTANT_H_
#define EXPRESSIONCONSTANT_H_

#include <string>

/**
 * Expression that resembles a CONSTANT.
 * This can be either a Literal or a Number.
 */
class ExpressionConstant: public Expression {
private:
	ExpressionConstant(const ExpressionConstant&);
	ExpressionConstant& operator=(const ExpressionConstant&);
	Element value;

public:
	explicit ExpressionConstant(ParserUtils *parserUtils);
	virtual ~ExpressionConstant();

	virtual Expression * evaluate();
	virtual void parseBody(std::string line);
	virtual std::string toString();

	virtual std::string getTag();
};

#endif /* EXPRESSIONCONSTANT_H_ */
