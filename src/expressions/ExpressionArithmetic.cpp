/*
 * ExpressionArithmetic.cpp
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
#include <list>

class Expression;

#include "../RuntimeExpressionInterface.h"
#include "../ParserUtils.h"
#include "../Expression.h"
#include "ExpressionArithmetic.h"

ExpressionArithmetic::ExpressionArithmetic(ParserUtils *parserUtils) : Expression(parserUtils) { }

ExpressionArithmetic::~ExpressionArithmetic() {}

Expression * ExpressionArithmetic::evaluate() {
	int result = 0;
	for (std::list<Expression*>::const_iterator expressionIterator = environment.begin(); expressionIterator != environment.end(); ++expressionIterator) {
		std::list<Element*> values = ((*expressionIterator)->evaluate())->getValues();
		for (std::list<Element*>::const_iterator elementIterator = values.begin(); elementIterator != values.end(); ++elementIterator) {
			result = operate(result, atoi((**elementIterator).c_str()));
		}
	}

    std::ostringstream os ;
    os << result;
	getValues().push_back(new Element(os.str()));

	std::cout << "Function of tag " + getTag() << " has value: " << result << std::endl;

	return this;
}

void ExpressionArithmetic::parseBody(std::string &line, void *params) {
	std::cout << "PARSEBODY:: " << line << std::endl;
	std::string temp = line;

	//+. Iterate while there are data in the line
	while (temp.find_first_not_of(' ') != std::string::npos) {
		int count = 0;
		int start = -1;
		int end = -1;
		bool stop = false;

		//Find an inner expression if existing
		if (temp.find('(') != std::string::npos) {
			for (std::string::size_type i = 0; i < temp.size() && !stop; ++i) {
				if (temp[i] == '('){
					if (count == 0)
						start = i;
					count++;
				}
				if (temp[i] == ')') {
					count--;
					if (count == 0) {
						end = i;
						stop = true;
					}
				}
			}
		}

		//Inner expression found
		if (end != -1 && start != -1) {
			//Get recursive and continue for this new expression
			std::cout << "There is an inner expression. Parse it" << std::endl;
			std::string stuff = temp.substr(start, end - start + 1);
			std::cout << "FIRST PARAM:: " << stuff << std::endl;
			environment.push_back(parserUtils->parseExpression(stuff));

			//Remove the expression and start again
			std::cout << "REMOVING EXPRESSION." << std::endl;
		    temp.replace(start, stuff.length(), "");
		} else { //Just constants
			std::cout << "Cut reached, adding constants" << std::endl;

			std::istringstream iss(temp);
			std::string value;
			while( iss >> value ) {
				std::cout << "CONSTANT:: " << value << std::endl;
				environment.push_back(parserUtils->expressionFromConstant(value));
			}

			//No more parenthesis. Cut condition here
			temp = "";
		}
	}
}
