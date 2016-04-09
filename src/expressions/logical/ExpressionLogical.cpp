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
#include <map>

class Expression;

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionLogical.h"

ExpressionLogical::ExpressionLogical(ParserUtils *parserUtils) :
		ExpressionCommon(parserUtils) {
}

ExpressionLogical::~ExpressionLogical() {
}

Expression * ExpressionLogical::evaluate() {
	clearValues();

	bool start = true;
	bool fail = false;
	int result = 0;

	for (std::list<Expression*>::const_iterator expressionIterator =
			environment.begin();
			!fail && expressionIterator != environment.end();
			++expressionIterator) {
		std::list<Element*> values =
				((*expressionIterator)->evaluate())->getValues();

		for (std::list<Element*>::const_iterator elementIterator =
				values.begin(); elementIterator != values.end();
				++elementIterator) {
			if (start) {
				result = atoi((**elementIterator).c_str());
				start = false;
			} else {
				if (!operate(result, atoi((**elementIterator).c_str())))
					fail = true;
			}
		}
	}

	if (!fail)
		getValues().push_back(new Element("1"));

	return this;
}

std::string ExpressionLogical::toString() {
	if (values.size() == 1)
		return "1";

	return "()";
}
