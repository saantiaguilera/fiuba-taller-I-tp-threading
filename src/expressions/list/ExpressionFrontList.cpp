/*
 * ExpressionFrontList.cpp
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

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionFrontList.h"

ExpressionFrontList::ExpressionFrontList(ParserUtils *parserUtils) : ExpressionCommon(parserUtils) { }

ExpressionFrontList::~ExpressionFrontList() {}

Expression * ExpressionFrontList::evaluate() {
	clearValues();
	bool done = false;
	//CAR
	std::list<Expression*>::iterator expressionIterator = environment.begin();

	if(expressionIterator != environment.end()) {
		std::list<Expression*> innerEnvironment = ((*expressionIterator)->evaluate()->getEnvironment());

		for (std::list<Expression*>::iterator innerIterator = innerEnvironment.begin() ;
				innerIterator != innerEnvironment.end() ; ++innerIterator) {

			if (*innerIterator != NULL) {
				if (done) {
					innerIterator = innerEnvironment.erase(innerIterator);
				} else {
					done = true;

					std::list<Element*> values = (*innerIterator)->evaluate()->getValues();

					for (std::list<Element*>::const_iterator elementIterator = values.begin(); elementIterator != values.end(); ++elementIterator) {
						getValues().push_back(new Element(**elementIterator)); //Else it gets double deleted
					//	std::cout << "Getting element from " << getTag() << ":: " << **elementIterator << std::endl;
					}
				}
			}

		}
	}

	return this;
}

std::string ExpressionFrontList::getTag() {
	return "Car";
}

std::string ExpressionFrontList::toString() {
	std::string response;

	if (values.size() != 1)
		response = "(";

	std::list<Element*>::const_iterator end = values.end();
	for (std::list<Element*>::const_iterator elementIterator = values.begin() ; elementIterator != end;) {
		response += (**elementIterator);

		if (++elementIterator != end)
			response += " ";
	}

	if (values.size() != 1)
		response += ")";

	return response;
}
