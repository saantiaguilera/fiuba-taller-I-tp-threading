/*
 * ExpressionConstant.cpp
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#include <string>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>

class Expression;

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "ExpressionConstant.h"

ExpressionConstant::ExpressionConstant(ParserUtils *parserUtils) :
		Expression(parserUtils), value("") {
}

ExpressionConstant::~ExpressionConstant() {
}

Expression * ExpressionConstant::evaluate() {
	clearValues();

	getValues().push_back(new Element(this->value));

	return this;
}

std::string ExpressionConstant::getTag() {
	return EXPRESSION_CONST;
}

void ExpressionConstant::parseBody(std::string line) {
	this->value = line;
}

std::string ExpressionConstant::toString() {
	return value;
}
