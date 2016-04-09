/*
 * ExpressionPrint.cpp
 *
 *  Created on: Apr 6, 2016
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
#include "../../threading/ReentrantLock.h"

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionPrint.h"

ExpressionPrint::ExpressionPrint(ParserUtils *parserUtils) :
		ExpressionCommon(parserUtils) {
}

ExpressionPrint::~ExpressionPrint() {
}

Expression * ExpressionPrint::evaluate() {
	clearValues();

	/**
	 * This needs to be locked
	 * Else a race condition can occur over
	 * the std::cout (shared object)
	 */
	ReentrantLock lock(mutex);

	std::list<Expression*>::const_iterator end = environment.end();
	for (std::list<Expression*>::const_iterator expressionIterator =
			environment.begin(); expressionIterator != end;) {
		std::cout << ((*expressionIterator)->evaluate())->toString();

		//Space the values unless its the last
		if (++expressionIterator != end)
			std::cout << SYMBOL_SPACE;
	}

	std::cout << std::endl;

	return this;
}

std::string ExpressionPrint::getTag() {
	return EXPRESSION_PRINT;
}
