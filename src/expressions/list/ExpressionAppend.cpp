/*
 * ExpressionAppend.cpp
 *
 *  Created on: Apr 9, 2016
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
#include "ExpressionAppend.h"

/**
 * @Public
 * @Constructor
 */
ExpressionAppend::ExpressionAppend(ParserUtils *parserUtils) :
		ExpressionCommon(parserUtils) {
}

/**
 * @Public
 * @Destructor
 */
ExpressionAppend::~ExpressionAppend() {
}

/**
 * @Note Appends all the values of our environment
 * to our values.
 * @Note This method creates values resembling
 * a flat environment
 */
Expression * ExpressionAppend::evaluate() {
	clearValues();

	for (std::list<Expression*>::const_iterator expressionIterator =
			environment.begin(); expressionIterator != environment.end();
			++expressionIterator) {
		std::list<Element*> values =
				(*((*expressionIterator)->evaluate())->getValues());

		for (std::list<Element*>::const_iterator elementIterator =
				values.begin(); elementIterator != values.end();
				++elementIterator) {
			getValues()->push_back(new Element(**elementIterator));
			//Else it gets double deleted
		}
	}

	return this;
}

std::string ExpressionAppend::getTag() {
	return EXPRESSION_APPEND;
}

/*
 * @Note Print all our environment
 * (That should be flattened because of how
 * evaluate works).
 */
std::string ExpressionAppend::toString() {
	std::string response;

	response = SYMBOL_PARENTHESIS_OPEN;

	std::list<Element*>::const_iterator end = values.end();
	for (std::list<Element*>::const_iterator elementIterator = values.begin();
			elementIterator != end;) {
		response += (**elementIterator);

		if (++elementIterator != end)
			response += SYMBOL_SPACE;
	}

	response += SYMBOL_PARENTHESIS_CLOSE;

	return response;
}
