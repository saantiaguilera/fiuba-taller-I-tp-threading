/*
 * ExpressionEquals.h
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_EXPRESSIONEQUALS_H_
#define EXPRESSIONS_EXPRESSIONEQUALS_H_

class ExpressionEquals : public ExpressionCommon {
	private:
		ExpressionEquals(const ExpressionEquals&);
		ExpressionEquals& operator=(const ExpressionEquals&);

	public:
		ExpressionEquals(ParserUtils *parserUtils);
		virtual ~ExpressionEquals();
		virtual Expression * evaluate();
		virtual std::string getTag();

};

#endif /* EXPRESSIONS_EXPRESSIONEQUALS_H_ */
