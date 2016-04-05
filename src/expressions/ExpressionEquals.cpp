/*
 * ExpressionEquals.cpp
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#include <string>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <list>

class Expression;

#include "../RuntimeExpressionInterface.h"
#include "../ParserUtils.h"
#include "../Expression.h"
#include "ExpressionCommon.h"
#include "ExpressionEquals.h"

ExpressionEquals::ExpressionEquals(ParserUtils *parserUtils) : ExpressionCommon(parserUtils) { }

ExpressionEquals::~ExpressionEquals() {}

Expression * ExpressionEquals::evaluate() {
	bool start = true;
	bool different = false;
	int result = 0;

	for (std::list<Expression*>::const_iterator expressionIterator = environment.begin(); !different && expressionIterator != environment.end(); ++expressionIterator) {
		std::list<Element*> values = ((*expressionIterator)->evaluate())->getValues();

		for (std::list<Element*>::const_iterator elementIterator = values.begin(); elementIterator != values.end(); ++elementIterator) {
			if (start) {
				result = atoi((**elementIterator).c_str());
				start = false;
			} else {
				if (result != atoi((**elementIterator).c_str()))
					different = true;
			}
		}
	}

	if (different)
		getValues().push_back(new Element("1"));

	std::cout << "Function of tag " + getTag() << " has value: " << (different ? "1" : "()") << std::endl;

	return this;
}

std::string ExpressionEquals::getTag() {
	return "=";
}
