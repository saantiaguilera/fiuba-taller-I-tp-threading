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
	std::cout << getTag() << "::evaluate" << std::endl;

	clearValues();
	//CDR
	bool start = true;

	flattenedEnvironment.clear();

	std::list<Expression*> environmentOfInner = *((*environment.begin())->evaluate()->getEnvironment());

	for (std::list<Expression*>::iterator innerIterator = environmentOfInner.begin(); innerIterator != environmentOfInner.end(); ++innerIterator) {
		if (start) {
			std::cout << "DELETING AN EXPRESSION OF TAG " << (*innerIterator)->getTag() << std::endl;
			start = false;
		} else {
			flattenedEnvironment.push_back(*innerIterator);
			std::cout << "Getting element from " << getTag() << std::endl;
		}

	}

	appendToValues();

	return this;
}

void ExpressionTailList::appendToValues() {
	std::cout << getTag() << "::appendToValues" << std::endl;

	clearValues();

	for (std::list<Expression*>::iterator iterator = flattenedEnvironment.begin() ;
				iterator != flattenedEnvironment.end() ; ++iterator) {

		std::list<Element*> iteratorValues = (*iterator)->evaluate()->getValues();

		std::list<Element*>::const_iterator end = iteratorValues.end();
		for (std::list<Element*>::const_iterator elementIterator = iteratorValues.begin() ; elementIterator != end; ++elementIterator) {
			values.push_back(new Element(**elementIterator));
		}

	}
}

std::string ExpressionTailList::getTag() {
	return "Cdr";
}

std::list<Expression*> * ExpressionTailList::getEnvironment() {
	return &flattenedEnvironment;
}

std::string ExpressionTailList::toString() {
	std::cout << getTag() << "::toString" << std::endl;
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
