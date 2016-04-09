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
#include <stdexcept>

class Expression;

#include "../threading/Mutex.h"

#include "../ParserUtils.h"
#include "../Expression.h"
#include "ExpressionCommon.h"

/**
 * @Public
 * @Constructor
 */
ExpressionCommon::ExpressionCommon(ParserUtils *parserUtils) :
		Expression(parserUtils) {
}

/**
 * @Public
 * @Destructor
 */
ExpressionCommon::~ExpressionCommon() {
}

/**
 * @Private
 *
 * @Note: Parses in a line from a starting point an
 * inner expression.
 *
 * @Param temp is the whole body
 * @Param startPoint is the start of an inner expression
 *
 * @Returns void. But invokes the injectExpression() for
 * injecting the parsed inner expression.
 *
 * @Throws EXPRESSION_BAD_FUNCTION if no expression could be
 * created
 */
void ExpressionCommon::parseInnerExpression(std::string &temp, int startPoint) {
	//Init variables we will be using
	int count = 0; //For counting over how many ( we pass.
	int start = -1;
	int end = -1;
	bool found = false;

	//Iterate from the start point over the end of the body
	for (std::string::size_type i = startPoint; i < temp.size() && !found;
			++i) {
		//If we found an opening parenthesys
		if (temp[i] == SYMBOL_PARENTHESIS_OPEN) {
			if (count == 0) //And its the first one !
				start = i; //Change the start
			count++; //Increment the count
		}

		//If we found a closing one
		if (temp[i] == SYMBOL_PARENTHESIS_CLOSE) {
			count--; //Reduce the count
			if (count == 0) { //If its zero its the end!!
				end = i;

				//Get recursive and continue for this new expression
				std::string stuff = temp.substr(start, end - start + 1);

				injectExpression(parserUtils->parseExpression(stuff));

				//Remove the expression and notify
				temp.replace(start, stuff.length() + 1, "");

				found = true;
			}
		}
	}

	//If we couldnt found it or the end/start wasnt changed, throw
	if (!found || end == -1 || start == -1)
		throw std::logic_error(EXCEPTION_BAD_FUNCTION);
}

/**
 * @Protected
 *
 * @Note: Injects an inner expression.
 *
 * @Default: It injects it to the environment
 */
void ExpressionCommon::injectExpression(Expression *expression) {
	environment.push_back(expression);
}

/**
 * @Public
 * @Note: Parses the body of an expression
 */
void ExpressionCommon::parseBody(std::string line) {
	//Clear the environment in case its already filled
	clearEnvironment();

	unsigned int i = 0;
	//Iterate while there is data in the line
	while (line.size() > 0 && i < line.size()) {
		switch (line[i]) {
		case SYMBOL_PARENTHESIS_OPEN: //Its an inner function
			parseInnerExpression(line, i);

			//Start again
			i = 0;

			break;
		case SYMBOL_QUOTATIONS: { //Its a literal !
			std::string literal = line.substr(i + 1,
					line.find(SYMBOL_QUOTATIONS, i + 1) - i - 1);

			injectExpression(parserUtils->expressionFromConstant(literal));

			//Remove the expression and start again
			//(+3 because of init, " and space)
			line.replace(i, literal.length() + 3, "");

			//Start again
			i = 0;
		}
			break;
		case ' ': //Do nothing, increment i
			++i;
			break;

		default: //Either a number or a variable
			if (isdigit(line[i])) { //Number then
				std::string literal = line.substr(i, line.find(SYMBOL_SPACE, i + 1) - i);

				injectExpression(parserUtils->expressionFromConstant(literal));

				//Remove the expression and start again
				line.replace(i, literal.length() + 1, "");

				//Start again
				i = 0;
			}

			if (isalpha(line[i])) { //Variable
				std::string literal = line.substr(i, line.find(SYMBOL_SPACE, i + 1) - i);

				injectExpression(parserUtils->expressionFromVariable(literal));

				//Remove the expression and start again
				line.replace(i, literal.length() + 1, "");

				//Start again
				i = 0;
			}
		}
	}
}
