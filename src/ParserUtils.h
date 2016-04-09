/*
 * ParserUtils.h
 *
 *  Created on: Apr 3, 2016
 *      Author: santiago
 */

#ifndef PARSERUTILS_H_
#define PARSERUTILS_H_

//This should be objects. But I lack of time :D
const std::string EXCEPTION_BAD_FUNCTION = "BadFunction";
const std::string EXCEPTION_NO_BODY = "NoBody";

#include <map>
#include <string>
#include <list>

class ParserUtils {
private:
	Mutex mutex;

	std::map<std::string, Expression*> runtimeVariables;
	std::map<std::string, Expression*> runtimeFunctions;
	std::list<Expression*> history;

	std::string bodyToString(std::string &line);
	std::string functionToString(std::string line);

public:
	ParserUtils();
	~ParserUtils();

	void run(std::string &line);

	Expression * parseExpression(std::string &line);

	Expression * expressionFromConstant(std::string line);
	Expression * expressionFromVariable(std::string tag);
	Expression * expressionFromKnownStrings(std::string &string);
	Expression * expressionFromFunction(std::string &line);
	Expression * expressionFromRuntime(std::string &line);

	Expression * appendRuntimeVariable(std::string tag, Expression *expression);
	Expression * appendRuntimeFunction(std::string tag, Expression *expression);
};

#endif /* PARSERUTILS_H_ */
