/*
 * ExpressionAppend.h
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_LIST_EXPRESSIONAPPEND_H_
#define EXPRESSIONS_LIST_EXPRESSIONAPPEND_H_

#include <string>

class ExpressionAppend: public ExpressionCommon {
private:
	ExpressionAppend(const ExpressionAppend&);
	ExpressionAppend& operator=(const ExpressionAppend&);

public:
	explicit ExpressionAppend(ParserUtils *parserUtils);
	virtual ~ExpressionAppend();
	virtual std::string getTag(); //known method ? NULL : runtime name tag
	virtual Expression * evaluate();
	virtual std::string toString();
};

#endif /* EXPRESSIONS_LIST_EXPRESSIONAPPEND_H_ */
