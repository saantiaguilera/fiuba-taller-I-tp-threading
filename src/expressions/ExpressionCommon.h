/*
 * ExpressionsCommon.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_EXPRESSIONCOMMON_H_
#define EXPRESSIONS_EXPRESSIONCOMMON_H_

class ExpressionCommon : public Expression {
	private:
		ExpressionCommon(const ExpressionCommon&);
		ExpressionCommon& operator=(const ExpressionCommon&);

	public:
		ExpressionCommon(ParserUtils *parserUtils);
		virtual ~ExpressionCommon();
		virtual std::string getTag() = 0; //known method ? NULL : runtime name tag
		virtual void parseBody(std::string &line, void *params);
		virtual Expression * evaluate() = 0;
};

#endif /* EXPRESSIONS_EXPRESSIONCOMMON_H_ */
