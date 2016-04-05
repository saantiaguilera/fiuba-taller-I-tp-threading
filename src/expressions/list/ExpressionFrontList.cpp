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

class Expression;

#include "../../RuntimeExpressionInterface.h"
#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionFrontList.h"

ExpressionFrontList::ExpressionFrontList(ParserUtils *parserUtils) : ExpressionCommon(parserUtils) { }

ExpressionFrontList::~ExpressionFrontList() {}

Expression * ExpressionFrontList::evaluate() {
	std::string element = "";

	std::list<Expression*>::const_iterator expressionIterator = environment.begin();

	if(expressionIterator != environment.end()) {
		std::list<Element*> values = ((*expressionIterator)->evaluate())->getValues();
		std::list<Element*>::const_iterator elementIterator = values.begin();

		if (elementIterator != values.end()) {
			getValues().push_back(new Element(**elementIterator)); //Else it gets double deleted
			element = (**elementIterator);
		}
	}

	std::cout << "Function of tag " + getTag() << " has size: " << element << std::endl;

	return this;
}

std::string ExpressionFrontList::getTag() {
	return "Car";
}
