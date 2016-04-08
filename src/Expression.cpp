/*
 * Expression.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#include <string>
#include <list>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <map>

class Expression;

#include "ParserUtils.h"
#include "Expression.h"

Expression::Expression(ParserUtils *parserUtils) : parserUtils(parserUtils) {}

/**
 * @note: I know this shouldnt be like this (its a bad smell to implement the if != NULL
 * then delete.
 * But since the Runtime functions need to last till end of program and they will be
 * inside other expressions
 * They will be double removed and this will crash.
 * Solution could be to use a copy constructor. But that would use a lot more heap
 * and I prefer 6 bad smell lines than 2x heap
 */
Expression::~Expression() {
	clearEnvironment();

	clearValues();
}

void Expression::clearValues() {
	for (std::list<Element*>::iterator valuesIterator = values.begin(); valuesIterator != values.end(); ++valuesIterator){
		if (*valuesIterator != NULL) {
			delete (*valuesIterator);
			*valuesIterator = NULL;
		}
	}

	values.clear();
}

void Expression::clearEnvironment() {
	for (std::list<Expression*>::iterator expressionIterator = environment.begin(); expressionIterator != environment.end(); ++expressionIterator) {
		if (*expressionIterator != NULL) {
			delete (*expressionIterator);
			(*expressionIterator) = NULL;
		}
	}

	environment.clear();
}

std::list<Element*> &Expression::getValues() {
	return this->values;
}

void Expression::setEnvironment(std::list<Expression*> expressions) {
	this->environment = expressions; //Todo check if this wont give a mem leak
}

std::string Expression::toString() {
	std::string returnString = "";

	for (std::list<Expression*>::iterator expressionIterator = environment.begin(); expressionIterator != environment.end(); ++expressionIterator) {
		returnString += ((*expressionIterator)->evaluate())->toString();
	}

	return returnString;
}
