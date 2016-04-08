/*
 * ExpressionPrint.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: santiago
 */

#include <string>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <list>
#include <map>

class Expression;

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionPrint.h"

ExpressionPrint::ExpressionPrint(ParserUtils *parserUtils) : ExpressionCommon(parserUtils) { }

ExpressionPrint::~ExpressionPrint() {}

Expression * ExpressionPrint::evaluate() {
	clearValues();

	for (std::list<Expression*>::const_iterator expressionIterator = environment.begin(); expressionIterator != environment.end(); ++expressionIterator) {
		std::list<Element*> values = ((*expressionIterator)->evaluate())->getValues();

		for (std::list<Element*>::const_iterator elementIterator = values.begin(); elementIterator != values.end(); ++elementIterator) {
			std::cout << **elementIterator << " "; //TODO CARE OF THIS SPACE. CHECK IF SERCOM ADDS IT OR NOT IN A FUNC
		}
	}

	std::cout << std::endl;

	return this;
}

std::string ExpressionPrint::getTag() {
	return "Print";
}



