/*
 * ExpressionArithmetic.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONARITHMETIC_H_
#define EXPRESSIONARITHMETIC_H_

class ExpressionArithmetic : public ExpressionCommon {
	private:
		ExpressionArithmetic(const ExpressionArithmetic&);
		ExpressionArithmetic& operator=(const ExpressionArithmetic&);

	public:
		ExpressionArithmetic(ParserUtils *parserUtils);
		virtual ~ExpressionArithmetic();
		virtual std::string getTag() = 0; //known method ? NULL : runtime name tag
		virtual Expression * evaluate();
		virtual int operate(int dest, int src) = 0;
};

#endif /* EXPRESSIONARITHMETIC_H_ */
