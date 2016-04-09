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
#include <map>

class Expression;

#include "../../threading/Mutex.h"

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionArithmetic.h"

ExpressionArithmetic::ExpressionArithmetic(ParserUtils *parserUtils) :
		ExpressionCommon(parserUtils) {
}

ExpressionArithmetic::~ExpressionArithmetic() {
}

/**
 * @Note Loops over all our environment operating
 * between the values.
 * Eg. (* 4 5 9)
 * 1. 4 * 5 = 20
 * 2. 20 * 9 = D: too hard
 * Joke. 180.
 *
 * @Note Doesnt accept literals. Can have unexpected
 * behaviour if so.
 *
 */
Expression * ExpressionArithmetic::evaluate() {
	clearValues();

	bool start = true;
	int result = 0;

	for (std::list<Expression*>::const_iterator expressionIterator =
			environment.begin(); expressionIterator != environment.end();
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
				result = operate(result, atoi((**elementIterator).c_str()));
			}
		}
	}

	std::ostringstream os;
	os << result;
	getValues()->push_back(new Element(os.str()));

	return this;
}

std::string ExpressionArithmetic::toString() {
	std::list<Element*>::const_iterator elementIterator = values.begin();

	//This arithmetics should always return 1 value.
	//Else someone hacked me and this features n dimens.
	return (**elementIterator);
}
