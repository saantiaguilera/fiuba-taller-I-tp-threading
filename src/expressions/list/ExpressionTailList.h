/*
 * ExpressionListTail.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_LIST_EXPRESSIONTAILLIST_H_
#define EXPRESSIONS_LIST_EXPRESSIONTAILLIST_H_

class ExpressionTailList : public ExpressionCommon {
	private:
		ExpressionTailList(const ExpressionTailList&);
		ExpressionTailList& operator=(const ExpressionTailList&);

	public:
		ExpressionTailList(ParserUtils *parserUtils);
		virtual ~ExpressionTailList();
		virtual std::string getTag(); //known method ? NULL : runtime name tag
		virtual Expression * evaluate();
};

#endif /* EXPRESSIONS_LIST_EXPRESSIONTAILLIST_H_ */
