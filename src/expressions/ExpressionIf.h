/*
 * ExpressionIf.h
 *
 *  Created on: Apr 6, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_EXPRESSIONIF_H_
#define EXPRESSIONS_EXPRESSIONIF_H_

//I know it should be a logical expression. But derp, this is more logical than the logical ones.

class ExpressionIf : public Expression {
	private:
		ExpressionIf(const ExpressionIf&);
		ExpressionIf& operator=(const ExpressionIf&);
		Expression *condition;
		Expression *trueExpression;
		Expression *falseExpression;

		void setExpression(Expression *expression);
		void parseInnerExpression(std::string &line, int startPosition);

	public:
		ExpressionIf(ParserUtils *parserUtils);
		virtual ~ExpressionIf();
		virtual std::string getTag(); //known method ? NULL : runtime name tag
		virtual void parseBody(std::string line);
		virtual Expression * evaluate();
};

#endif /* EXPRESSIONS_EXPRESSIONIF_H_ */
