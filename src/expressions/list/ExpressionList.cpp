/*
 * ExpressionList.cpp
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
#include "ExpressionList.h"

ExpressionList::ExpressionList(ParserUtils *parserUtils) :
		ExpressionCommon(parserUtils) {
}

ExpressionList::~ExpressionList() {
}

Expression * ExpressionList::evaluate() {
	clearValues();

	for (std::list<Expression*>::const_iterator expressionIterator =
			environment.begin(); expressionIterator != environment.end();
			++expressionIterator) {
		std::list<Element*> values =
				((*expressionIterator)->evaluate())->getValues();

		for (std::list<Element*>::const_iterator elementIterator =
				values.begin(); elementIterator != values.end();
				++elementIterator) {
			getValues().push_back(new Element(**elementIterator));
			//Else it gets double deleted
		}
	}

	return this;
}

std::string ExpressionList::getTag() {
	return "List";
}

std::string ExpressionList::toString() {
	std::string response;

	response = "(";

	std::list<Expression*>::const_iterator end = environment.end();
	for (std::list<Expression*>::const_iterator expressionIterator =
			environment.begin(); expressionIterator != end;) {
		response += (*expressionIterator)->toString();

		if (++expressionIterator != end)
			response += " ";
	}

	response += ")";

	return response;
}
