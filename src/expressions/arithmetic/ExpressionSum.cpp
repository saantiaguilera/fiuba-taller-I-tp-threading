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

#include "../../threading/Mutex.h"

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionArithmetic.h"
#include "ExpressionSum.h"

/**
 * @Public
 * @Constructor
 */
ExpressionSum::ExpressionSum(ParserUtils *parserUtils) :
		ExpressionArithmetic(parserUtils) {
}

/**
 * @Public
 * @Destructor
 */
ExpressionSum::~ExpressionSum() {
}

int ExpressionSum::operate(int dest, int src) {
	return dest + src;
}

std::string ExpressionSum::getTag() {
	return EXPRESSION_SUM;
}
