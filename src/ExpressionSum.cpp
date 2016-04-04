/*
 * ExpressionSum.cpp
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#include <string>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <list>

class Expression;

#include "RuntimeExpressionInterface.h"
#include "ParserUtils.h"
#include "Expression.h"
#include "ExpressionSum.h"

ExpressionSum::ExpressionSum(ParserUtils *parserUtils) : Expression(parserUtils) { }

ExpressionSum::~ExpressionSum() {}

Expression * ExpressionSum::evaluate() {
	int result = 0;
	for (std::list<Expression*>::const_iterator expressionIterator = environment.begin(); expressionIterator != environment.end(); ++expressionIterator) {
		std::list<Element> values = ((*expressionIterator)->evaluate())->getValues();
		for (std::list<Element>::const_iterator elementIterator = values.begin(); elementIterator != values.end(); ++elementIterator) {
			result += atoi((*elementIterator).c_str());
		}
	}

	std::cout << "Function of tag " + getTag() << " has value: " << result << std::endl;
	return 0;
}

std::string ExpressionSum::getTag() {
	return "+";
}

void ExpressionSum::parseBody(std::string &line, void *params) {
	std::cout << "PARSEBODY:: " << line << std::endl;

	//+. Parse first param
	int count = 0;
	int start = -1;
	int end = -1;
	bool stop = false;

	for (std::string::size_type i = 0; i < line.size() && !stop; ++i) {
		if (line[i] == '('){
			if (count == 0)
				start = i;
			count++;
		}
			if (line[i] == ')') {
				count--;
				if (count == 0) {
					end = i;
					stop = true;
				}
			}
		}
	if (end != -1 && start != -1) {
		std::string stuff = line.substr(start, end - start + 1);
		std::cout << "FIRST PARAM:: " << stuff << std::endl;
		parserUtils->bodyToString(stuff);
	} else {
		int start = 0;
		int end = line.find_last_of(")") - start;
		std::cout << "Cut reached, stuff to join with func is " << line.substr(start, end) << std::endl;
		std::cout << "Checking if second params are available" << std::endl;
		return;
		//No more parenthesis. Cut condition here
	}
}
