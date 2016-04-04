/*
 * Expression.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#include <string>
#include <list>
#include <cstdio>
#include <stdlib.h>
#include <iostream>

class Expression;

#include "RuntimeExpressionInterface.h"
#include "ParserUtils.h"
#include "Expression.h"

Expression::Expression(ParserUtils *parserUtils) : parserUtils(parserUtils) {
}

std::list<Element> Expression::getValues() {
	return this->values;
}

void Expression::setEnvironment(std::list<Expression*> expressions) {
	this->environment = expressions; //Todo check if this wont give a mem leak
}
