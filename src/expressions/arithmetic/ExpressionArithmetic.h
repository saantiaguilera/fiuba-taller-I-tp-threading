/*
 * ExpressionArithmetic.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONARITHMETIC_H_
#define EXPRESSIONARITHMETIC_H_

#include <string>

class ExpressionArithmetic: public ExpressionCommon {
private:
	ExpressionArithmetic(const ExpressionArithmetic&);
	ExpressionArithmetic& operator=(const ExpressionArithmetic&);

protected:
	virtual int operate(int dest, int src) = 0;

public:
	explicit ExpressionArithmetic(ParserUtils *parserUtils);
	virtual ~ExpressionArithmetic();

	virtual std::string getTag() = 0;

	virtual Expression * evaluate();
	virtual std::string toString();
};

#endif /* EXPRESSIONARITHMETIC_H_ */
