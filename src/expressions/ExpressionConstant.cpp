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

class Expression;

#include "../RuntimeExpressionInterface.h"
#include "../ParserUtils.h"
#include "../Expression.h"
#include "ExpressionConstant.h"

ExpressionConstant::ExpressionConstant(ParserUtils *parserUtils) : Expression(parserUtils) , value("") { }

ExpressionConstant::~ExpressionConstant() {}

Expression * ExpressionConstant::evaluate() {
	getValues().push_back(new Element(this->value));
	std::cout << "Function of tag " + getTag() << " has value: " << this->value << std::endl;
	return this;
}

std::string ExpressionConstant::getTag() {
	return "Const";
}

void ExpressionConstant::parseBody(std::string &line, void *params) {
	std::cout << getTag() << " PARSEBODY:: " << line << std::endl;
	this->value = line;
}



