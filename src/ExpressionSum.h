/*
 * ExpressionSum.h
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#ifndef EXPRESSIONSUM_H_
#define EXPRESSIONSUM_H_

#include "Expression.h"

class ExpressionSum : public Expression {
	private:
		ExpressionSum(const ExpressionSum&);
		ExpressionSum& operator=(const ExpressionSum&);

	public:
		ExpressionSum(RuntimeExpressionInterface *listener) : Expression(listener) { }

		virtual ~ExpressionSum() {};

		virtual Expression * evaluate() {
			int result = 0;
			for (std::list<Expression*>::const_iterator expressionIterator = environment.begin(); expressionIterator != environment.end(); ++expressionIterator) {
				std::list<Element> values = ((*expressionIterator)->evaluate())->getValues();
				for (std::list<Element>::const_iterator elementIterator = values.begin(); elementIterator != values.end(); ++elementIterator) {
					result += atoi((*elementIterator).c_str());
				}
			}

			std::cout << "Function of tag " + getTag() << " has value: " << result << std::endl;
			return 0;
		}

		virtual void parseBody(std::string &line, void *params) {
			std::cout << "PARSEBODY:: " << line << std::endl;


		}

		virtual std::string getTag() {
			return "+";
		}

};

#endif /* EXPRESSIONSUM_H_ */
