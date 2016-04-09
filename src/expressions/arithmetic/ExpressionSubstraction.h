/*
 * ExpressionSubstraction.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_EXPRESSIONSUBSTRACTION_H_
#define EXPRESSIONS_EXPRESSIONSUBSTRACTION_H_

class ExpressionSubstraction: public ExpressionArithmetic {
private:
	ExpressionSubstraction(const ExpressionSubstraction&);
	ExpressionSubstraction& operator=(const ExpressionSubstraction&);

public:
	ExpressionSubstraction(ParserUtils *parserUtils);
	virtual ~ExpressionSubstraction();
	virtual int operate(int dest, int src);
	virtual std::string getTag();
};

#endif /* EXPRESSIONS_EXPRESSIONSUBSTRACTION_H_ */
