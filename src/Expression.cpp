/*
 * Expression.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#include "Expression.h"

Expression::Expression(std::string line) {
	parse(line);
}

Expression::~Expression() {}
