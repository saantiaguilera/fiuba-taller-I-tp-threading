/*
 * ExpressionMultiply.cpp
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
#include "ExpressionMultiply.h"

ExpressionMultiply::ExpressionMultiply(ParserUtils *parserUtils) : ExpressionArithmetic(parserUtils) { }

ExpressionMultiply::~ExpressionMultiply() {}

Expression * ExpressionMultiply::evaluate() {
	int result = 0;
	for (std::list<Expression*>::const_iterator expressionIterator = environment.begin(); expressionIterator != environment.end(); ++expressionIterator) {
		std::list<Element> values = ((*expressionIterator)->evaluate())->getValues();
		for (std::list<Element>::const_iterator elementIterator = values.begin(); elementIterator != values.end(); ++elementIterator) {
			result *= atoi((*elementIterator).c_str());
		}
	}

    std::ostringstream os ;
    os << result;
	getValues().push_back(os.str());

	std::cout << "Function of tag " + getTag() << " has value: " << result << std::endl;

	return this;
}

std::string ExpressionMultiply::getTag() {
	return "*";
}
