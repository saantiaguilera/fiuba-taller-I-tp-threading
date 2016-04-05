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

class Expression;

#include "../../RuntimeExpressionInterface.h"
#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionList.h"

ExpressionList::ExpressionList(ParserUtils *parserUtils) : ExpressionCommon(parserUtils) { }

ExpressionList::~ExpressionList() {}

Expression * ExpressionList::evaluate() {
	int hardcodedCounter = 0;

	for (std::list<Expression*>::const_iterator expressionIterator = environment.begin(); expressionIterator != environment.end(); ++expressionIterator) {
		std::list<Element*> values = ((*expressionIterator)->evaluate())->getValues();

		for (std::list<Element*>::const_iterator elementIterator = values.begin(); elementIterator != values.end(); ++elementIterator) {
			getValues().push_back(*elementIterator); //TODO MAYBE CREATE ANOTHER ONE IN THE HEAP ? BECAUSE OF THE DELETE AT THE END
			hardcodedCounter++;
		}
	}

	std::cout << "Function of tag " + getTag() << " has size: " << hardcodedCounter << std::endl;

	return this;
}

std::string ExpressionList::getTag() {
	return "List";
}
