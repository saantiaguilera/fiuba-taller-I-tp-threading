/*
 * LispParser.h
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#ifndef LISPPARSER_H_
#define LISPPARSER_H_

#include "ExpressionSum.h"
#include "Expression.h"
#include "KnownFunctions.h"


//Not to sure if it has to be private. Because from outside people shouldnt be able to call getUserExpressions. But if someone
//Has the interface they should be able to retrieve them, but its weird since the user can just cast it and get them....
class LispParser : private RuntimeExpressionInterface {
	private:
		std::string buffer;
		std::list<Expression*> runtimeExpressions; //This will be all the expressions created in runtime

		Expression * getExpressionFor(std::string &function);
		Expression * expressionFromKnownStrings(std::string &string);
		Expression * parseLine(std::string &line);
		virtual std::list<Expression*> getRuntimeExpressions();

	public:
		LispParser(std::string &code);
		~LispParser();
		void run();
};

#endif /* LISPPARSER_H_ */
