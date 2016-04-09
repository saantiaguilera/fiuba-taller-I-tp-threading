/*
 * ExpressionEquals.cpp
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
#include "ExpressionEquals.h"

/**
 * @Public
 * @Constructor
 */
ExpressionEquals::ExpressionEquals(ParserUtils *parserUtils) :
		ExpressionLogical(parserUtils) {
}

/**
 * @Public
 * @Destructor
 */
ExpressionEquals::~ExpressionEquals() {
}

bool ExpressionEquals::operate(int leftValue, int rightValue) {
	return leftValue == rightValue;
}

std::string ExpressionEquals::getTag() {
	return EXPRESSION_EQUALS;
}
