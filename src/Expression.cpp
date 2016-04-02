/*
 * Expression.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#include "Expression.h"

Expression::Expression(std::list<Expression*> &runtimeExpressions) {
	this->runtimeExpressions = runtimeExpressions;
}

std::list<Element> Expression::getValues() {
	return this->values;
}

void Expression::setEnvironment(std::list<Expression*> expressions) {
	this->environment = expressions; //Todo check if this wont give a mem leak
}
