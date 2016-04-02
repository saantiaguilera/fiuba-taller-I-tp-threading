/*
 * LispParser.h
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#ifndef LISPPARSER_H_
#define LISPPARSER_H_

#include "Expression.h"
#include <iostream>
#include <sstream>

//Not to sure if it has to be private. Because from outside people shouldnt be able to call getUserExpressions. But if someone
//Has the interface they should be able to retrieve them, but its weird since the user can just cast it and get them....
class LispParser {
	private:
		std::istringstream buffer;
		std::list<Expression*> runtimeExpressions; //This will be all the expressions created in runtime
		Expression * parseLine();

	public:
		LispParser(std::string &fileName);
		~LispParser();
		void run();
};

#endif /* LISPPARSER_H_ */
