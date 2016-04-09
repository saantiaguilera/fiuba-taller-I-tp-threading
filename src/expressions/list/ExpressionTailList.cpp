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

#include "../../threading/Mutex.h"

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionTailList.h"

/**
 * @Public
 * @Constructor
 */
ExpressionTailList::ExpressionTailList(ParserUtils *parserUtils) :
		ExpressionCommon(parserUtils) {
}

/**
 * @Public
 * @Destructor
 */
ExpressionTailList::~ExpressionTailList() {
}

/**
 * @Private
 * @Note: This parses the evaluated inner
 * environment of our environment.
 * Although its confusing. Its something like this:
 * (cdr (list (env1) env2 env3))
 * So this will parse the env2, env3
 * already evaluated. (Because maybe
 * they change) and add it to a
 * flattenedEnvironment we have
 */
void ExpressionTailList::parseEvaluation(Expression *expression) {
	//If its a const append it
	if (expression->getTag() == EXPRESSION_CONST) {
		flattenedEnvironment.push_back(expression);
	} else {
		//Else loop through its environment and append it all
		std::list<Expression*> expressionEnvironment =
				*(expression->evaluate()->getEnvironment());

		for (std::list<Expression*>::iterator iterator =
				expressionEnvironment.begin();
				iterator != expressionEnvironment.end(); ++iterator) {
			flattenedEnvironment.push_back(*iterator);
		}
	}
}

/**
 * @Public
 * @Note This method uses a flattened environment
 * were we save the inner environment of our environment
 * Eg. (cdr (list 4 5 (list 1 2)))
 * cdr::environment == (list 4 5 (list 1 2))
 * cdr::flattenedEnv == 4 5 (list 1 2)
 *
 * This is useful because when we will print
 * We need to print the flat one. Else we will just
 * get (5 (1 2)) (remember cdr deleted the first one)
 * When we should get 5 (1 2)
 * (The starting and ending parenthesys check)
 */
Expression * ExpressionTailList::evaluate() {
	clearValues();

	bool start = true;

	flattenedEnvironment.clear();

	std::list<Expression*> environmentOfInner =
			*((*environment.begin())->evaluate()->getEnvironment());

	for (std::list<Expression*>::iterator innerIterator =
			environmentOfInner.begin();
			innerIterator != environmentOfInner.end(); ++innerIterator) {
		if (start) {
			//Just to "remove" the first value
			start = false;
		} else {
			parseEvaluation(*innerIterator);
		}
	}

	//Append the created flattenedEnv to the values
	appendToValues();

	return this;
}

/**
 * @Private
 * @Note This appends our whole flattened environment
 * into values, because we need to emit
 * results for outer expressions !!
 */
void ExpressionTailList::appendToValues() {
	clearValues();

	for (std::list<Expression*>::iterator iterator =
			flattenedEnvironment.begin();
			iterator != flattenedEnvironment.end(); ++iterator) {
		std::list<Element*> iteratorValues =
				(*(*iterator)->evaluate()->getValues());

		std::list<Element*>::const_iterator end = iteratorValues.end();
		for (std::list<Element*>::const_iterator elementIterator =
				iteratorValues.begin(); elementIterator != end;
				++elementIterator) {
			values.push_back(new Element(**elementIterator));
		}
	}
}

std::string ExpressionTailList::getTag() {
	return EXPRESSION_CDR;
}

std::list<Expression*> * ExpressionTailList::getEnvironment() {
	return &flattenedEnvironment;
}

/**
 * @Note Iterates through our values and prints them
 */
std::string ExpressionTailList::toString() {
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
