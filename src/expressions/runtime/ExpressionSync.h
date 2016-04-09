/*
 * ExpressionSync.h
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONS_RUNTIME_EXPRESSIONSYNC_H_
#define EXPRESSIONS_RUNTIME_EXPRESSIONSYNC_H_

class ExpressionSync: public Expression {
private:
	ExpressionSync(const ExpressionSync&);
	ExpressionSync& operator=(const ExpressionSync&);

public:
	ExpressionSync(ParserUtils *parserUtils);
	virtual ~ExpressionSync();
	virtual void parseBody(std::string line);
	virtual std::string getTag(); //known method ? NULL : runtime name tag
	virtual Expression * evaluate();
};

#endif /* EXPRESSIONS_RUNTIME_EXPRESSIONSYNC_H_ */