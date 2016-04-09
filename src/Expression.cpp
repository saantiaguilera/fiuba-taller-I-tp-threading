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

#include "threading/Mutex.h"

#include "ParserUtils.h"
#include "Expression.h"

/**
 * @Public
 * @Constructor
 */
Expression::Expression(ParserUtils *parserUtils) :
		parserUtils(parserUtils) {
}

/**
 * @Public
 * @Destructor
 */
Expression::~Expression() {
	clearEnvironment();

	clearValues();
}

/**
 * @Protected
 * @Note: Clean the list of values
 */
void Expression::clearValues() {
	for (std::list<Element*>::iterator valuesIterator = values.begin();
			valuesIterator != values.end(); ++valuesIterator) {
		if (*valuesIterator != NULL) {
			delete (*valuesIterator);
			*valuesIterator = NULL;
		}
	}

	values.clear();
}

/**
 * @Protected
 * @Note: Clean the environment
 */
void Expression::clearEnvironment() {
	for (std::list<Expression*>::iterator expressionIterator =
			environment.begin(); expressionIterator != environment.end();
			++expressionIterator) {
		if (*expressionIterator != NULL) {
			delete (*expressionIterator);
			(*expressionIterator) = NULL;
		}
	}

	environment.clear();
}

/**
 * @Public
 * @Note: Getter for the values list
 */
std::list<Element*> * Expression::getValues() {
	return &values;
}

/**
 * @Protected
 * @Note: Setter for the environment
 */
void Expression::setEnvironment(std::list<Expression*> expressions) {
	this->environment = expressions;
}

/**
 * @Public
 * @Note: Getter for the environment
 */
std::list<Expression*> * Expression::getEnvironment() {
	return &environment;
}

/**
 * @Public
 * @Note: By default an expression just tells
 * all his environment to be parsed as string
 * and it returns it.
 *
 * @Overridable
 */
std::string Expression::toString() {
	std::string returnString = "";

	for (std::list<Expression*>::iterator expressionIterator =
			environment.begin(); expressionIterator != environment.end();
			++expressionIterator) {
		returnString += ((*expressionIterator)->evaluate())->toString();
	}

	return returnString;
}
