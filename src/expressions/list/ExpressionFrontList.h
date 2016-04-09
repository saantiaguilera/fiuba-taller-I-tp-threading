/*
 * ExpressionFrontList.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_LIST_EXPRESSIONFRONTLIST_H_
#define EXPRESSIONS_LIST_EXPRESSIONFRONTLIST_H_

#include <string>
#include <list>

/**
 * Expression that resembles the CAR
 */
class ExpressionFrontList: public ExpressionCommon {
private:
	ExpressionFrontList(const ExpressionFrontList&);
	ExpressionFrontList& operator=(const ExpressionFrontList&);

	std::list<Expression*> flattenedEnvironment;

	void appendToValues();
	void parseEvaluation(Expression *expression);

public:
	explicit ExpressionFrontList(ParserUtils *parserUtils);
	virtual ~ExpressionFrontList();

	virtual std::string getTag();
	virtual std::list<Expression*> * getEnvironment();

	virtual Expression * evaluate();
	virtual std::string toString();
};

#endif /* EXPRESSIONS_LIST_EXPRESSIONFRONTLIST_H_ */
