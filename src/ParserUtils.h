/*
 * ParserUtils.h
 *
 *  Created on: Apr 3, 2016
 *      Author: santiago
 */

#ifndef PARSERUTILS_H_
#define PARSERUTILS_H_

#include <list>

class ParserUtils {
	private:
		RuntimeExpressionInterface *listener;

	public: //Should have like getFunction / getStuff / blabla
		ParserUtils(RuntimeExpressionInterface *listener) : listener(listener) { }

		Expression * expressionFromKnownStrings(std::string &string) {
			if (string == "+")
				return new ExpressionSum(listener);
			if (string == "-")
				return 0;
			if (string == "*")
				return 0;
			if (string == "/")
				return 0;
			if (string == "=")
				return 0;
			if (string == ">")
				return 0;
			if (string == "<")
				return 0;
			if (string == "car")
				return 0;
			if (string == "cdr")
				return 0;
			if (string == "append")
				return 0;
			if (string == "if")
				return 0;
			if (string == "defun")
				return 0;
			if (string == "print")
				return 0;
			if (string == "setq")
				return 0;
			if (string == "list")
				return 0;
			if (string == "sync")
				return 0;

			return 0; //constant, lets say 4 or "hello"
		}

		Expression * expressionFromFunction(std::string &line) {
			std::cout << "Function to parse is: " << line << std::endl;

			std::list<Expression*> runtimeExpressions = listener->getRuntimeExpressions();

			for (std::list<Expression*>::const_iterator iterator = runtimeExpressions.begin(); iterator != runtimeExpressions.end(); ++iterator) {
				std::string tag = (*iterator)->getTag();
				if(line == tag)
					return (*iterator);
			}

			return expressionFromKnownStrings(line);
		}

		std::string bodyToString(std::string &line) {
			std::string function = functionToString(line);
			return line.substr(line.find(function) + function.length() + 1, line.find_last_of(")") - line.find(function) - function.length());
		}

		std::string functionToString(std::string &line) {
			return line.substr(line.find("(") + 1, line.find(" ") - line.find("(") - 1);
		}

		Expression * parseExpression(std::string &line) {
			//Get the expression according to the symbol (+)
			std::string function = functionToString(line);

			Expression *expression = expressionFromFunction(function);

			std::string stuff = bodyToString(line);

			std::cout << "Stuff that receives is: " << stuff << std::endl;
			if (expression != 0)
				expression->parseBody(stuff, 0); //0 Should be a virtual method of expression. That overrides only the ones interested

			return expression;
		}
};



#endif /* PARSERUTILS_H_ */
