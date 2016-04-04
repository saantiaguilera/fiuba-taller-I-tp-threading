/*
 * ExpressionMultiply.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_EXPRESSIONMULTIPLY_H_
#define EXPRESSIONS_EXPRESSIONMULTIPLY_H_

class ExpressionMultiply : public ExpressionArithmetic {
	private:
		ExpressionMultiply(const ExpressionMultiply&);
		ExpressionMultiply& operator=(const ExpressionMultiply&);

	public:
		ExpressionMultiply(ParserUtils *parserUtils);
		virtual ~ExpressionMultiply();
		virtual Expression * evaluate();
		virtual std::string getTag();

};

#endif /* EXPRESSIONS_EXPRESSIONMULTIPLY_H_ */
