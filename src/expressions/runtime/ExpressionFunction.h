/*
 * ExpressionFunction.h
 *
 *  Created on: Apr 6, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_RUNTIME_EXPRESSIONFUNCTION_H_
#define EXPRESSIONS_RUNTIME_EXPRESSIONFUNCTION_H_

#include <string>

class ExpressionFunction: public Expression {
private:
	ExpressionFunction(const ExpressionFunction&);
	ExpressionFunction& operator=(const ExpressionFunction&);

	std::string variableName; //The variable
	std::string functionName; //The defined function
	std::string body; //Body of the defined function

public:
	explicit ExpressionFunction(ParserUtils *parserUtils);
	virtual ~ExpressionFunction();
	virtual void parseBody(std::string line);
	//Create a mutation of this expression (X-Method)
	Expression * mutate(std::string variable);
	//known method ? NULL : runtime name tag
	virtual std::string getTag();
	virtual Expression * evaluate();
};

#endif /* EXPRESSIONS_RUNTIME_EXPRESSIONFUNCTION_H_ */
