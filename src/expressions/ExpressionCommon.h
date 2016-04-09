/*
 * ExpressionsCommon.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_EXPRESSIONCOMMON_H_
#define EXPRESSIONS_EXPRESSIONCOMMON_H_

class ExpressionCommon: public Expression {
private:
	ExpressionCommon(const ExpressionCommon&);
	ExpressionCommon& operator=(const ExpressionCommon&);

	void parseInnerExpression(std::string &line, int startPosition);

public:
	ExpressionCommon(ParserUtils *parserUtils);
	virtual ~ExpressionCommon();
	virtual std::string getTag() = 0; //known method ? NULL : runtime name tag

	virtual void parseBody(std::string line);

	virtual void injectExpression(Expression *expression);

	virtual Expression * evaluate() = 0;
};

#endif /* EXPRESSIONS_EXPRESSIONCOMMON_H_ */
