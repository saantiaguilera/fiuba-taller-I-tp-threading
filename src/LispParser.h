/*
 * LispParser.h
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#ifndef LISPPARSER_H_
#define LISPPARSER_H_

#include "Expression.h"
#include "UserRuntimeExpressionsInterface.h"

class LispParser : public UserRuntimeExpressionsInterface {
	private:
		FILE *inputFile;
		std::map<std::string, Expression> userExpressions; //This will be all the expressions created in runtime

	public:
		LispParser(std::string fileName);
		virtual ~LispParser();
		Expression parseLine();
		virtual std::map<std::string, Expression> getUserExpressions() {
			return userExpressions;
		}
};

#endif /* LISPPARSER_H_ */
