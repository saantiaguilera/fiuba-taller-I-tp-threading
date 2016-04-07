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
		std::map<std::string, Expression*> runtimeVariables;
		std::map<std::string, Expression*> runtimeFunctions;

		Expression * expressionFromKnownStrings(std::string &string);
		Expression * expressionFromFunction(std::string &line);
		Expression * expressionFromRuntime(std::string &line);
		std::string bodyToString(std::string &line);
		std::string functionToString(std::string line);

	public: //Should have like getFunction / getStuff / blabla
		ParserUtils();
		~ParserUtils();
		Expression * parseExpression(std::string &line);
		Expression * expressionFromConstant(std::string line);
		Expression * appendRuntimeVariable(std::string tag, Expression *expression);
		Expression * appendRuntimeFunction(std::string tag, Expression *expression);
		Expression * expressionFromVariable(std::string tag);
};



#endif /* PARSERUTILS_H_ */
