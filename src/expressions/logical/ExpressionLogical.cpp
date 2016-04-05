/*
 * ExpressionLogical.cpp
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

#include "../../RuntimeExpressionInterface.h"
#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionLogical.h"

ExpressionLogical::ExpressionLogical(ParserUtils *parserUtils) : ExpressionCommon(parserUtils) { }

ExpressionLogical::~ExpressionLogical() {}

Expression * ExpressionLogical::evaluate() {
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
				if (operate(result, atoi((**elementIterator).c_str())))
					different = true;
			}
		}
	}

	if (different)
		getValues().push_back(new Element("1"));

	std::cout << "Function of tag " + getTag() << " has value: " << (different ? "1" : "()") << std::endl;

	return this;
}
