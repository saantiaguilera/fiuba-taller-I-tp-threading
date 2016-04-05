/*
 * ExpressionsCommon.cpp
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
#include <cctype>
#include <list>

class Expression;

#include "../RuntimeExpressionInterface.h"
#include "../ParserUtils.h"
#include "../Expression.h"
#include "ExpressionCommon.h"

enum MODE { INNER_EXPRESSION, VALUE, UNDEFINED, DEFINED };

ExpressionCommon::ExpressionCommon(ParserUtils *parserUtils) : Expression(parserUtils) { }

ExpressionCommon::~ExpressionCommon() {}

void ExpressionCommon::parseBody(std::string &line, void *params) {
	std::cout << "BODY:: " << line << std::endl;
	std::string temp = line;

	//+. Iterate while there are data in the line
	while (temp.size() > 0) {
		int count = 0;
		int start = -1;
		int end = -1;

		MODE mode = UNDEFINED;

		for (std::string::size_type i = 0; i < temp.size() && mode != DEFINED; ++i) {
			switch (mode) {
				case UNDEFINED:
					if (temp[i] == '('){
						if (count == 0)
							start = i;
						count++;

						mode = INNER_EXPRESSION;
					}

					if (isdigit(temp[i]) || isalpha(temp[i])) {
						start = i;
						mode = VALUE;
					}

					break;

				case INNER_EXPRESSION:
					if (temp[i] == '('){
						if (count == 0)
							start = i;
						count++;
					}
					if (temp[i] == ')') {
						count--;
						if (count == 0) {
							end = i;

							//Get recursive and continue for this new expression
							std::string stuff = temp.substr(start, end - start + 1);
							std::cout << "INNER EXPRESSION:: " << stuff << std::endl;
							environment.push_back(parserUtils->parseExpression(stuff));

							//Remove the expression and start again
							temp.replace(start, stuff.length(), "");

							mode = DEFINED;
						}
					}
					break;

				case VALUE:
					if (!isdigit(temp[i]) && !isalpha(temp[i])) {
						end = i;

						//Get recursive and continue for this value
						std::string value = temp.substr(start, end - start + 1);
						std::cout << "CONSTANT:: " << value << std::endl;
						environment.push_back(parserUtils->expressionFromConstant(value));

						//Remove the expression and start again
						temp.replace(start, value.length(), "");

						mode = DEFINED;
					}
					break;

				case DEFINED: //To avoid -W
					break;
			}
		}

		if (mode != DEFINED) {
			if (start != -1) {
				//There was a last char at the end. Parse it as value
				std::string value = temp.substr(start, temp.size());

				switch (mode) {
					case UNDEFINED: //1 char or lots of spaces
					case VALUE:
						environment.push_back(parserUtils->expressionFromConstant(value));
						std::cout << "CONSTANT:: " << value << std::endl;
						break;

					case INNER_EXPRESSION:
						environment.push_back(parserUtils->parseExpression(value));
						std::cout << "INNER EXPRESSION:: " << value << std::endl;
						break;

					case DEFINED:
						break;
				}

				mode = UNDEFINED;
				temp = "";
			} else {
				if (temp.length() > 0)
					temp = "";
			}
		}
	}

}
