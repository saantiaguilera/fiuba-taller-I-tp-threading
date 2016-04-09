/*
 * ExpressionPrint.h
 *
 *  Created on: Apr 6, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_EXPRESSIONPRINT_H_
#define EXPRESSIONS_EXPRESSIONPRINT_H_

#include <string>

class ExpressionPrint: public ExpressionCommon {
private:
	ExpressionPrint(const ExpressionPrint&);
	ExpressionPrint& operator=(const ExpressionPrint&);

	Mutex mutex;

public:
	explicit ExpressionPrint(ParserUtils *parserUtils);
	virtual ~ExpressionPrint();

	virtual Expression * evaluate();

	virtual std::string getTag();
};

#endif /* EXPRESSIONS_EXPRESSIONPRINT_H_ */
