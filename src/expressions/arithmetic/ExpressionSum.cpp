/*
 * ExpressionSum.cpp
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
#include <map>

class Expression;
class ExpressionFunction;

#include "../../RuntimeExpressionInterface.h"
#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "../runtime/ExpressionFunction.h"
#include "ExpressionArithmetic.h"
#include "ExpressionSum.h"

ExpressionSum::ExpressionSum(ParserUtils *parserUtils) : ExpressionArithmetic(parserUtils) { }

ExpressionSum::~ExpressionSum() {}

int ExpressionSum::operate(int dest, int src) {
	return dest + src;
}

std::string ExpressionSum::getTag() {
	return "+";
}
