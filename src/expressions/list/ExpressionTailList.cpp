/*
 * ExpressionTailList.cpp
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
#include "ExpressionTailList.h"

ExpressionTailList::ExpressionTailList(ParserUtils *parserUtils) : ExpressionCommon(parserUtils) { }

ExpressionTailList::~ExpressionTailList() {}

Expression * ExpressionTailList::evaluate() {
	clearValues();

	bool start = true;

	for (std::list<Expression*>::const_iterator expressionIterator = environment.begin(); expressionIterator != environment.end(); ++expressionIterator) {
		std::list<Element*> values = ((*expressionIterator)->evaluate())->getValues();

		for (std::list<Element*>::const_iterator elementIterator = values.begin(); elementIterator != values.end(); ++elementIterator) {
			if (start)
				start = false;
			else
				getValues().push_back(new Element(**elementIterator)); //Else it gets double deleted
		}
	}

	return this;
}

std::string ExpressionTailList::getTag() {
	return "Cdr";
}

std::string ExpressionTailList::toString() {
	std::string response;

	response = "(";

	std::list<Element*>::const_iterator end = values.end();
	for (std::list<Element*>::const_iterator elementIterator = values.begin() ; elementIterator != end;) {
		response += (**elementIterator);

		if (++elementIterator != end)
			response += " ";
	}

	response = ")";

	return response;
}
