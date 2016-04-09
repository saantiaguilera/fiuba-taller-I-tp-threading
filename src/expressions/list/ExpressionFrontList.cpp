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
	std::cout << getTag() << "::evaluate" << std::endl;
	clearValues();
	bool done = false;
	//CAR

	flattenedEnvironment.clear();

	std::list<Expression*> environmentOfInner = *((*environment.begin())->evaluate()->getEnvironment());

	for (std::list<Expression*>::iterator innerIterator = environmentOfInner.begin() ;
			innerIterator != environmentOfInner.end() ;) {

		if (*innerIterator != NULL) {
			if (done) {
				std::cout << "SKIPPING AN EXPRESSION OF TAG " << (*innerIterator)->getTag() << std::endl;
			} else {
				std::cout << "Getting element from " << getTag() << ":: " << std::endl;
				done = true;

				flattenedEnvironment.push_back(*innerIterator);

				++innerIterator;
			}
		} else ++innerIterator;

	}

	appendToValues();

	return this;
}

void ExpressionFrontList::appendToValues() {
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

std::list<Expression*> * ExpressionFrontList::getEnvironment() {
	return &flattenedEnvironment;
}

std::string ExpressionFrontList::getTag() {
	return "Car";
}

std::string ExpressionFrontList::toString() {
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
