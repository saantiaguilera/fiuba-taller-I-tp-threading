/*
 * ExpressionMultiply.cpp
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
#include "ExpressionArithmetic.h"
#include "ExpressionMultiply.h"

ExpressionMultiply::ExpressionMultiply(ParserUtils *parserUtils) : ExpressionArithmetic(parserUtils) { }

ExpressionMultiply::~ExpressionMultiply() {}

int ExpressionMultiply::operate(int dest, int src) {
	return dest * src;
}

std::string ExpressionMultiply::getTag() {
	return "*";
}
