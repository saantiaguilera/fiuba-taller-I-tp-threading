/*
 * ExpressionSync.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */


#include <string>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cctype>
#include <list>
#include <map>

class Expression;

#include "../../threading/Mutex.h"

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "ExpressionSync.h"

/**
 * @Public
 * @Constructor
 */
ExpressionSync::ExpressionSync(ParserUtils *parserUtils) :
		Expression(parserUtils) {
}

/**
 * @Public
 * @Destructor
 */
ExpressionSync::~ExpressionSync() {
}

/**
 * @Note: Does nothing
 * Sync doesnt have a body
 */
void ExpressionSync::parseBody(std::string line) {
}

Expression * ExpressionSync::evaluate() {
	return NULL; //No use. Return null to make it blow if someone tries to
}

std::string ExpressionSync::getTag() {
	return EXPRESSION_SYNC;
}
