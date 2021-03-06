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
#include <map>

class Expression;

#include "../../threading/Mutex.h"

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionArithmetic.h"
#include "ExpressionSubstraction.h"

/**
 * @Public
 * @Constructor
 */
ExpressionSubstraction::ExpressionSubstraction(ParserUtils *parserUtils) :
		ExpressionArithmetic(parserUtils) {
}

/**
 * @Public
 * @Destructor
 */
ExpressionSubstraction::~ExpressionSubstraction() {
}

int ExpressionSubstraction::operate(int dest, int src) {
	return dest - src;
}

std::string ExpressionSubstraction::getTag() {
	return EXPRESSION_SUBSTRACTION;
}
