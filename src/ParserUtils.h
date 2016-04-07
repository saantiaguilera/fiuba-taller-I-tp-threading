/*
 * ParserUtils.h
 *
 *  Created on: Apr 3, 2016
 *      Author: santiago
 */

#ifndef PARSERUTILS_H_
#define PARSERUTILS_H_

class ParserUtils {
	private:
		RuntimeExpressionInterface *listener;
		std::map<std::string, Expression*> runtimeVariables;

		Expression * expressionFromKnownStrings(std::string &string);
		Expression * expressionFromFunction(std::string &line);
		std::string bodyToString(std::string &line);
		std::string functionToString(std::string line);

	public: //Should have like getFunction / getStuff / blabla
		ParserUtils(RuntimeExpressionInterface *listener);
		~ParserUtils();
		Expression * parseExpression(std::string &line);
		Expression * expressionFromConstant(std::string line);
		Expression * variableFromRuntime(std::string tag, std::string line);
		Expression * expressionFromVariable(std::string tag);
};



#endif /* PARSERUTILS_H_ */
