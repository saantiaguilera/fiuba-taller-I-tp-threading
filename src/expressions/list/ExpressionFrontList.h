/*
 * ExpressionFrontList.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_LIST_EXPRESSIONFRONTLIST_H_
#define EXPRESSIONS_LIST_EXPRESSIONFRONTLIST_H_

class ExpressionFrontList : public ExpressionCommon {
	private:
		ExpressionFrontList(const ExpressionFrontList&);
		ExpressionFrontList& operator=(const ExpressionFrontList&);

		std::list<Expression*> flattenedEnvironment;

		void appendToValues();

	public:
		ExpressionFrontList(ParserUtils *parserUtils);
		virtual ~ExpressionFrontList();
		virtual std::string getTag(); //known method ? NULL : runtime name tag
		virtual Expression * evaluate();
		virtual std::list<Expression*> * getEnvironment();
		virtual std::string toString();
};

#endif /* EXPRESSIONS_LIST_EXPRESSIONFRONTLIST_H_ */
