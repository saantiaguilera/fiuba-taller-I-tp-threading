/*
 * ExpressionIf.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: santiago
 */


#include <string>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cctype>
#include <list>

class Expression;

#include "../RuntimeExpressionInterface.h"
#include "../ParserUtils.h"
#include "../Expression.h"
#include "ExpressionIf.h"

ExpressionIf::ExpressionIf(ParserUtils *parserUtils) : Expression(parserUtils) , condition(NULL) ,
		trueExpression(NULL) , falseExpression(NULL) { }

ExpressionIf::~ExpressionIf() {}

void ExpressionIf::setExpression(Expression *expression) {
	if (condition == NULL)
		condition = expression;
	else if (trueExpression == NULL)
		trueExpression = expression;
	else if (falseExpression == NULL)
		falseExpression = expression;
}

void ExpressionIf::parseInnerExpression(std::string &temp, int startPoint) {
	int count = 0;
	int start = -1;
	int end = -1;

	for (std::string::size_type i = startPoint; i < temp.size(); ++i) {
		if (temp[i] == '('){
			if (count == 0)
				start = i;
			count++;
		}
		if (temp[i] == ')') {
			count--;
			if (count == 0) {
				end = i;

				//Get recursive and continue for this new expression
				std::string stuff = temp.substr(start, end - start + 1);
				std::cout << "INNER EXPRESSION:: " << stuff << std::endl;

				setExpression(parserUtils->parseExpression(stuff));

				//Remove the expression and start again
				temp.replace(start, stuff.length() + 1, "");
			}
		}
	}
}

void ExpressionIf::parseBody(std::string line) {
	std::cout << "BODY:: " << line << std::endl;

	int i = 0;
	//+. Iterate while there are data in the line
	while (line.size() > 0) {
		switch (line[i]) {
		case '(': //Its an innter function
			parseInnerExpression(line, i);

			//Start again
			i = 0;

			break;
		case '"': { //Its a literal !
			std::string literal = line.substr(i + 1, line.find('"', i + 1) - i - 1);

			std::cout << "LITERAL:: " << literal << std::endl;

			environment.push_back(parserUtils->expressionFromConstant(literal));

			//Remove the expression and start again
			line.replace(i, literal.length(), "");

			//Start again
			i = 0;

			}
			break;
		case ' ': //Do nothing, increment i
			++i;
			break;

		default: //Either a number or a variable
			if (isdigit(line[i])) {
				std::string literal = line.substr(i, line.find(' ', i + 1) - i);

				std::cout << "NUMBER:: " << literal << std::endl;

				setExpression(parserUtils->expressionFromConstant(literal));

				//Remove the expression and start again
				line.replace(i, literal.length() + 1, "");

				//Start again
				i = 0;
			}

			if (isalpha(line[i])) {
				std::string literal = line.substr(i, line.find(' ', i + 1) - i);

				std::cout << "VARIABLE:: " << literal << std::endl;

				//TODO setExpression(parserUtils->expressionFromConstant(literal));

				//Remove the expression and start again
				line.replace(i, literal.length() + 1, "");

				//Start again
				i = 0;
			}
		}
	}

}

Expression * ExpressionIf::evaluate() {
	Expression* result;
	if ((condition->evaluate())->getValues().size() > 0) {
		//True;
		std::cout << "Function of tag " + getTag() << " was: TRUE" << std::endl;

		result = trueExpression->evaluate();
	} else {
		//False
		std::cout << "Function of tag " + getTag() << " was: FALSE" << std::endl;

		result = falseExpression->evaluate();
	}
	/**
	 * TODO
	 * All this if/else change it for
	 * result = (condition->evaluate())->getValues().size() > 0 ? trueExpression : falseExpression;
	 * result->evaluate();
	 */

	//Before returning, set the values of the expression evaluated as result
	std::list<Element*> values = result->getValues();
	for (std::list<Element*>::const_iterator expressionIterator = values.begin(); expressionIterator != values.end(); ++expressionIterator) {
		getValues().push_back(new Element(**expressionIterator));
	}

	return this;
}

std::string ExpressionIf::getTag() {
	return "If";
}
