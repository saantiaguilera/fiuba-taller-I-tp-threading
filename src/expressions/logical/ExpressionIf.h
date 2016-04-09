/*
 * ExpressionIf.h
 *
 *  Created on: Apr 6, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_EXPRESSIONIF_H_
#define EXPRESSIONS_EXPRESSIONIF_H_

#include <string>

//I know it should be a logical expression.
//But derp, this is more logical than the logical ones.

class ExpressionIf: public ExpressionCommon {
private:
	ExpressionIf(const ExpressionIf&);
	ExpressionIf& operator=(const ExpressionIf&);

	Expression *condition;
	Expression *trueExpression;
	Expression *falseExpression;

protected:
	virtual void injectExpression(Expression *expression);

public:
	explicit ExpressionIf(ParserUtils *parserUtils);
	virtual ~ExpressionIf();

	virtual std::string getTag();

	virtual Expression * evaluate();
	virtual std::string toString();
};

#endif /* EXPRESSIONS_EXPRESSIONIF_H_ */
