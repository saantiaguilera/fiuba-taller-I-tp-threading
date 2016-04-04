/*
 * ExpressionSubstraction.cpp
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

#include "../RuntimeExpressionInterface.h"
#include "../ParserUtils.h"
#include "../Expression.h"
#include "ExpressionArithmetic.h"
#include "ExpressionSubstraction.h"

ExpressionSubstraction::ExpressionSubstraction(ParserUtils *parserUtils) : ExpressionArithmetic(parserUtils) { }

ExpressionSubstraction::~ExpressionSubstraction() {}

int ExpressionSubstraction::operate(int dest, int src) {
	return dest - src;
}

std::string ExpressionSubstraction::getTag() {
	return "-";
}
