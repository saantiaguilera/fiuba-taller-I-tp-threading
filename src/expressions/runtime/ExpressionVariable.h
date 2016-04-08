/*
 * ExpressionVariable.h
 *
 *  Created on: Apr 6, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_RUNTIME_EXPRESSIONVARIABLE_H_
#define EXPRESSIONS_RUNTIME_EXPRESSIONVARIABLE_H_

class ExpressionVariable : public ExpressionCommon {
	private:
		ExpressionVariable(const ExpressionVariable&);
		ExpressionVariable& operator=(const ExpressionVariable&);

		std::string variableName;
	public:
		ExpressionVariable(ParserUtils *parserUtils);
		virtual ~ExpressionVariable();
		virtual void parseBody(std::string line);
		virtual std::string getTag(); //known method ? NULL : runtime name tag
		virtual Expression * evaluate();
		virtual void injectExpression(Expression *expression);
};

#endif /* EXPRESSIONS_RUNTIME_EXPRESSIONVARIABLE_H_ */
