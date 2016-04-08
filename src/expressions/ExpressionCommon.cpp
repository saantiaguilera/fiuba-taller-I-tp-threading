/*
 * ExpressionsCommon.cpp
 *
 *  Created on: Apr 4, 2016
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

#include "../ParserUtils.h"
#include "../Expression.h"
#include "ExpressionCommon.h"

ExpressionCommon::ExpressionCommon(ParserUtils *parserUtils) : Expression(parserUtils) { }

ExpressionCommon::~ExpressionCommon() {}

void ExpressionCommon::parseInnerExpression(std::string &temp, int startPoint) {
	int count = 0;
	int start = -1;
	int end = -1;
	bool found = false;

	for (std::string::size_type i = startPoint; i < temp.size() && !found; ++i) {
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

				injectExpression(parserUtils->parseExpression(stuff));

				//Remove the expression and start again
				temp.replace(start, stuff.length() + 1, "");

				found = true;
			}
		}
	}
}

void ExpressionCommon::injectExpression(Expression *expression) {
	environment.push_back(expression);
}

void ExpressionCommon::parseBody(std::string line) {
	clearEnvironment();

	unsigned int i = 0;
	//+. Iterate while there are data in the line
	while (line.size() > 0 && i < line.size()) {
		switch (line[i]) {
		case '(': //Its an innter function
			parseInnerExpression(line, i);

			//Start again
			i = 0;

			break;
		case '"': { //Its a literal !
			std::string literal = line.substr(i + 1, line.find('"', i + 1) - i - 1);

			injectExpression(parserUtils->expressionFromConstant(literal));

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

				injectExpression(parserUtils->expressionFromConstant(literal));

				//Remove the expression and start again
				line.replace(i, literal.length() + 1, "");

				//Start again
				i = 0;
			}

			if (isalpha(line[i])) {
				std::string literal = line.substr(i, line.find(' ', i + 1) - i);

				injectExpression(parserUtils->expressionFromVariable(literal));

				//Remove the expression and start again
				line.replace(i, literal.length() + 1, "");

				//Start again
				i = 0;
			}
		}
	}

}
