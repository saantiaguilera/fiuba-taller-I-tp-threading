/*
 * ExpressionListTail.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_LIST_EXPRESSIONTAILLIST_H_
#define EXPRESSIONS_LIST_EXPRESSIONTAILLIST_H_

#include <string>
#include <list>

class ExpressionTailList: public ExpressionCommon {
private:
	ExpressionTailList(const ExpressionTailList&);
	ExpressionTailList& operator=(const ExpressionTailList&);

	std::list<Expression*> flattenedEnvironment;

	void appendToValues();
	void parseEvaluation(Expression *expression);

public:
	explicit ExpressionTailList(ParserUtils *parserUtils);
	virtual ~ExpressionTailList();
	virtual std::string getTag(); //known method ? NULL : runtime name tag
	virtual Expression * evaluate();
	virtual std::string toString();
	virtual std::list<Expression*> * getEnvironment();
};

#endif /* EXPRESSIONS_LIST_EXPRESSIONTAILLIST_H_ */
