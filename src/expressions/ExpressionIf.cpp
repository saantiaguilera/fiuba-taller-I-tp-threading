/*
 * ExpressionIf.cpp
 *
 *  Created on: Apr 6, 2016
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

#include "../ParserUtils.h"
#include "../Expression.h"
#include "ExpressionCommon.h"
#include "ExpressionIf.h"

ExpressionIf::ExpressionIf(ParserUtils *parserUtils) : ExpressionCommon(parserUtils) , condition(NULL) ,
		trueExpression(NULL) , falseExpression(NULL) { }

ExpressionIf::~ExpressionIf() {}

void ExpressionIf::injectExpression(Expression *expression) {
	if (condition == NULL)
		condition = expression;
	else if (trueExpression == NULL)
		trueExpression = expression;
	else if (falseExpression == NULL)
		falseExpression = expression;
}

Expression * ExpressionIf::evaluate() {
	Expression* result;
	if ((condition->evaluate())->getValues().size() > 0) {
		//True;
		std::cout << "Function of tag " + getTag() << " was: TRUE" << std::endl;

		result = (trueExpression->evaluate());
	} else {
		//False
		std::cout << "Function of tag " + getTag() << " was: FALSE" << std::endl;

		result = (falseExpression->evaluate());
	}
	/**
	 * TODO
	 * All this if/else change it for
	 * result = (condition->evaluate())->getValues().size() > 0 ? trueExpression : falseExpression;
	 * result->evaluate();
	 */

	return result;
}

std::string ExpressionIf::getTag() {
	return "If";
}
