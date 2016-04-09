/*
 * ExpressionList.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_LIST_EXPRESSIONLIST_H_
#define EXPRESSIONS_LIST_EXPRESSIONLIST_H_

class ExpressionList: public ExpressionCommon {
private:
	ExpressionList(const ExpressionList&);
	ExpressionList& operator=(const ExpressionList&);

public:
	ExpressionList(ParserUtils *parserUtils);
	virtual ~ExpressionList();
	virtual std::string getTag(); //known method ? NULL : runtime name tag
	virtual Expression * evaluate();
	virtual std::string toString();
};

#endif /* EXPRESSIONS_LIST_EXPRESSIONLIST_H_ */
