/*
 * ExpressionSync.h
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_RUNTIME_EXPRESSIONSYNC_H_
#define EXPRESSIONS_RUNTIME_EXPRESSIONSYNC_H_

#include <string>

class ExpressionSync: public Expression {
private:
	ExpressionSync(const ExpressionSync&);
	ExpressionSync& operator=(const ExpressionSync&);

public:
	explicit ExpressionSync(ParserUtils *parserUtils);
	virtual ~ExpressionSync();

	virtual void parseBody(std::string line);
	virtual std::string getTag();
	virtual Expression * evaluate();
};

#endif /* EXPRESSIONS_RUNTIME_EXPRESSIONSYNC_H_ */
