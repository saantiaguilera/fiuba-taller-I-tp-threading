/*
 * Expression.h
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include "string"
#include <list>

/**
 * My elements will always be strings.
 * This means if you create
 * (list 1 2 3 4) and evaluate this expression
 * return will be (eg) : new ArrayList<String>({ "1", "2", "3", "4" })
 *
 * If later we need to make the Element more complex, we will have to change it into
 * an own class
 */
typedef std::string Element;

class Expression {
	private:
		std::list<Expression*> environment;
		std::list<Element> values;
		std::list<Expression*> runtimeExpressions;

	public:
		Expression(std::list<Expression*> &runtimeExpressions);
		virtual ~Expression() = 0;
		virtual std::string getTag() = 0; //known method ? NULL : runtime name tag
		std::list<Element> getValues();
		virtual void parse(std::string line, void *params) = 0;
		virtual Expression * evaluate() = 0;
		void setEnvironment(std::list<Expression*> environment);
		/**
		 * if we have
		 * defunc func1 (list) (+ list) //Sum the list
		 * Evaluate() will create a new expression (This "new expression" should be some GenericRuntimeExpression class)
		 * and from the line he will get the tag func1 and as second param the "variable" (in this case "list")
		 * Then, he will create a SumExpression, and in the parse he will pass the variable "list"
		 * This way our sum will know that if list appears he shouldnt add it and leave it.
		 *
		 *
		 * print (func1 (list 1 2 3)) // "6"
		 * Taking the print expression aside.
		 * Inside the parser:
		 * He wont find func1 in the known ones, so he will look in the interface list.
		 * He will find it
		 * As it is a runtime expression, the parser will create the GenericRuntimeExpression
		 * And another one for the param (list 1 2 3), which he will find it in the known ones (its ListExpression lets say)
		 * Then he will get the GenericRuntimeException and .setEnvironment(ListExpression as List of size 1)
		 * And finally evaluate that, getting the 6 and PrintExpression will print it from the return of evaluate().getValues().get(0)
		 */
};

#endif /* EXPRESSION_H_ */
