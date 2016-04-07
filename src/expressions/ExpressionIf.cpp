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
#include <map>

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

			setExpression(parserUtils->expressionFromConstant(literal));

			//Remove the expression and start again (+3 because of init, " and space)
			line.replace(i, literal.length() + 3, "");

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

				setExpression(parserUtils->expressionFromVariable(literal));

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

		result = (trueExpression->evaluate());
	} else {
		//False
		std::cout << "Function of tag " + getTag() << " was: FALSE" << std::endl;

		result = (falseExpression->evaluate());
	}
	/**
	 * TODO
	 * All this if/else change it for
	 * result = (condition->evaluate())->getValues().size() > 0 ? trueExpression : falseExpression;
	 * result->evaluate();
	 */

	return result;
}

std::string ExpressionIf::getTag() {
	return "If";
}
