/*
 * ExpressionLogical.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_LOGICAL_EXPRESSIONLOGICAL_H_
#define EXPRESSIONS_LOGICAL_EXPRESSIONLOGICAL_H_

class ExpressionLogical : public ExpressionCommon {
	private:
		ExpressionLogical(const ExpressionLogical&);
		ExpressionLogical& operator=(const ExpressionLogical&);

	public:
		ExpressionLogical(ParserUtils *parserUtils);
		virtual ~ExpressionLogical();
		virtual std::string getTag() = 0; //known method ? NULL : runtime name tag
		virtual Expression * evaluate();
		virtual bool operate(int leftValue, int rightValue) = 0;
};

#endif /* EXPRESSIONS_LOGICAL_EXPRESSIONLOGICAL_H_ */
