/*
 * Expression.h
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

/**
 * My elements will always be strings.
 * This means if you create
 * (list 1 2 3 4) and evaluate this expression
 * return will be (eg) : new ArrayList<String>({ "1", "2", "3", "4" })
 *
 * If later we need to make the Element more complex, we will have to change it into
 * an own class
 */

#include <string>
#include <list>

const std::string EXPRESSION_SUM = "+";
const std::string EXPRESSION_SUBSTRACTION = "-";
const std::string EXPRESSION_MULTIPLY = "*";
const std::string EXPRESSION_DIVIDE = "/";
const std::string EXPRESSION_EQUALS = "=";
const std::string EXPRESSION_HIGHER = ">";
const std::string EXPRESSION_LOWER = "<";
const std::string EXPRESSION_LIST = "list";
const std::string EXPRESSION_CAR = "car";
const std::string EXPRESSION_CDR = "cdr";
const std::string EXPRESSION_APPEND = "append";
const std::string EXPRESSION_IF = "if";
const std::string EXPRESSION_DEFUN = "defun";
const std::string EXPRESSION_PRINT = "print";
const std::string EXPRESSION_SETQ = "setq";
const std::string EXPRESSION_SYNC = "sync";
const std::string EXPRESSION_CONST = "const";

typedef std::string Element;

class Expression {
private:
	Expression(const Expression&);
	Expression& operator=(const Expression&);

protected:
	std::list<Expression*> environment;
	ParserUtils *parserUtils;
	std::list<Element*> values;

	void clearEnvironment();
	void clearValues();
	void setEnvironment(std::list<Expression*> environment);

public:
	explicit Expression(ParserUtils *parserUtils);
	virtual ~Expression();

	virtual std::string getTag() = 0;
	std::list<Element*> &getValues();
	virtual std::list<Expression*> * getEnvironment();
	//TODO CHANGE THIS TO BE LIKE GETVALUES ?

	virtual void parseBody(std::string line) = 0;
	virtual Expression * evaluate() = 0;
	virtual std::string toString();
};

#endif /* EXPRESSION_H_ */
