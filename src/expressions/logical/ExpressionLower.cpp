/*
 * ExpressionLower.cpp
 *
 *  Created on: Apr 4, 2016
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

#include "../../threading/Mutex.h"

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionLogical.h"
#include "ExpressionLower.h"

ExpressionLower::ExpressionLower(ParserUtils *parserUtils) :
		ExpressionLogical(parserUtils) {
}

ExpressionLower::~ExpressionLower() {
}

bool ExpressionLower::operate(int leftValue, int rightValue) {
	return leftValue < rightValue;
}

std::string ExpressionLower::getTag() {
	return EXPRESSION_LOWER;
}
