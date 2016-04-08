/*
 * ExpressionFrontList.cpp
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
#include "ExpressionFrontList.h"

ExpressionFrontList::ExpressionFrontList(ParserUtils *parserUtils) : ExpressionCommon(parserUtils) { }

ExpressionFrontList::~ExpressionFrontList() {}

Expression * ExpressionFrontList::evaluate() {
	clearValues();

	std::list<Expression*>::const_iterator expressionIterator = environment.begin();

	if(expressionIterator != environment.end()) {
		std::list<Element*> values = ((*expressionIterator)->evaluate())->getValues();
		std::list<Element*>::const_iterator elementIterator = values.begin();

		if (elementIterator != values.end())
			getValues().push_back(new Element(**elementIterator)); //Else it gets double deleted
	}

	return this;
}

std::string ExpressionFrontList::getTag() {
	return "Car";
}

std::string ExpressionFrontList::toString() {
	std::string response;

	if (values.size() != 1)
		response = "(";

	std::list<Element*>::const_iterator end = values.end();
	for (std::list<Element*>::const_iterator elementIterator = values.begin() ; elementIterator != end;) {
		response += (**elementIterator);

		if (++elementIterator != end)
			response += " ";
	}

	if (values.size() != 1)
		response += ")";

	return response;
}
