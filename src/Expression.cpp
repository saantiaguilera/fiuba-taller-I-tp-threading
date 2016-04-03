/*
 * Expression.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#include "Expression.h"

Expression::Expression(RuntimeExpressionInterface *listener) {
	this->listener = listener;
}

std::list<Element> Expression::getValues() {
	return this->values;
}

void Expression::setEnvironment(std::list<Expression*> expressions) {
	this->environment = expressions; //Todo check if this wont give a mem leak
}
