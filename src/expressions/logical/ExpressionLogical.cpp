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

#include "../../threading/Mutex.h"

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionLogical.h"

//Posible return values for a logic expression
#define LOGICAL_SUCCESS_RETURN "1"
#define LOGICAL_FAILURE_RETURN "()"

/**
 * @Public
 * @Constructor
 */
ExpressionLogical::ExpressionLogical(ParserUtils *parserUtils) :
		ExpressionCommon(parserUtils) {
}

/**
 * @Public
 * @Destructor
 */
ExpressionLogical::~ExpressionLogical() {
}

/**
 * @Note:
 * Iterates through all the values and compares them
 * among the others, invoking the operate(lv,rv) method.
 * With just one failure the result is a fail.
 *
 * Eg. (= 4 (+ 2 2) 8)
 * operate(4, 2+2) --> true.
 * operate(2+2, 8) --> false.
 */
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
				(*((*expressionIterator)->evaluate())->getValues());

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
		getValues()->push_back(new Element(LOGICAL_SUCCESS_RETURN));

	return this;
}

std::string ExpressionLogical::toString() {
	if (values.size() == 1)
		return LOGICAL_SUCCESS_RETURN;

	return LOGICAL_FAILURE_RETURN;
}
