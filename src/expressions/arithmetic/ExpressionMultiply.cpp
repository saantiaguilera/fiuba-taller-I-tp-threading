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
#include <map>

class Expression;

#include "../../threading/Mutex.h"

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionArithmetic.h"
#include "ExpressionMultiply.h"

/**
 * @Public
 * @Constructor
 */
ExpressionMultiply::ExpressionMultiply(ParserUtils *parserUtils) :
		ExpressionArithmetic(parserUtils) {
}

ExpressionMultiply::~ExpressionMultiply() {
}

int ExpressionMultiply::operate(int dest, int src) {
	return dest * src;
}

std::string ExpressionMultiply::getTag() {
	return EXPRESSION_MULTIPLY;
}
