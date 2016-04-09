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

#include "../../threading/Mutex.h"

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionFrontList.h"

ExpressionFrontList::ExpressionFrontList(ParserUtils *parserUtils) :
		ExpressionCommon(parserUtils) {
}

ExpressionFrontList::~ExpressionFrontList() {
}

void ExpressionFrontList::parseEvaluation(Expression *expression) {
	if (expression->getTag() == EXPRESSION_CONST) {
		flattenedEnvironment.push_back(expression);
	} else {
		std::list<Expression*> expressionEnvironment =
				*(expression->evaluate()->getEnvironment());

		for (std::list<Expression*>::iterator iterator =
				expressionEnvironment.begin();
				iterator != expressionEnvironment.end(); ++iterator) {
			flattenedEnvironment.push_back(*iterator);
		}
	}
}

Expression * ExpressionFrontList::evaluate() {
	clearValues();
	bool done = false;
	//CAR

	flattenedEnvironment.clear();

	std::list<Expression*> environmentOfInner =
			*((*environment.begin())->evaluate()->getEnvironment());

	for (std::list<Expression*>::iterator innerIterator =
			environmentOfInner.begin();
			innerIterator != environmentOfInner.end(); ++innerIterator) {
		if (*innerIterator != NULL && !done) {
			done = true;
			parseEvaluation(*innerIterator);
		}
	}

	appendToValues();

	return this;
}

void ExpressionFrontList::appendToValues() {
	//std::cout << getTag() << "::appendToValues" << std::endl;

	clearValues();

	for (std::list<Expression*>::iterator iterator =
			flattenedEnvironment.begin();
			iterator != flattenedEnvironment.end(); ++iterator) {
		std::list<Element*> iteratorValues =
				(*iterator)->evaluate()->getValues();

		std::list<Element*>::const_iterator end = iteratorValues.end();
		for (std::list<Element*>::const_iterator elementIterator =
				iteratorValues.begin(); elementIterator != end;
				++elementIterator) {
			values.push_back(new Element(**elementIterator));
		}
	}
}

std::list<Expression*> * ExpressionFrontList::getEnvironment() {
	return &flattenedEnvironment;
}

std::string ExpressionFrontList::getTag() {
	return EXPRESSION_CAR;
}

std::string ExpressionFrontList::toString() {
	//std::cout << getTag() << "::toString" << std::endl;
	std::string response;

	if (values.size() != 1)
		response = SYMBOL_PARENTHESIS_OPEN;

	std::list<Element*>::const_iterator end = values.end();
	for (std::list<Element*>::const_iterator elementIterator = values.begin();
			elementIterator != end;) {
		response += (**elementIterator);

		if (++elementIterator != end)
			response += SYMBOL_SPACE;
	}

	if (values.size() != 1)
		response += SYMBOL_PARENTHESIS_CLOSE;

	return response;
}
