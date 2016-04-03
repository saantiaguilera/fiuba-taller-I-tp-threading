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

		virtual void parse(std::string &line, void *params) {
			int count = 0;
			int start = -1;
			int end = -1;
			bool stop = false;

			for (std::string::size_type i = 1; i < line.size() && !stop; ++i) {
				if (line[i] == '('){
					if (count == 0)
						start = i;
					count++;
				}
					if (line[i] == ')') {
						count--;
						if (count == 0) {
							end = i;
							stop = true;
						}
					}
				}
			if (end != -1 && start != -1) {
				std::string stuff = line.substr(start, end - start + 1);
				std::cout << "Params are: " << stuff << std::endl;
				parse(stuff, params);
			} else {
				int start = 0;
				int end = line.find_last_of(")") - start;
				std::cout << "Cut reached, stuff to join with func is " << line.substr(start, end) << std::endl;
				std::cout << "Checking if second params are available" << std::endl;
				return;
				//No more parenthesis. Cut condition here
			}
			//Since max params are 2, enter recursivness here again.
			if (line.find("(", end) != std::string::npos) {
				int newStart = end + 1;
				count = 0;
				start = -1;
				end = -1;
				stop = false;

				for (std::string::size_type i = newStart; i < line.size() && !stop; ++i) {
					if (line[i] == '('){
						if (count == 0)
							start = i;
						count++;
					}

					if (line[i] == ')') {
						count--;
						if (count == 0) {
							end = i;
							stop = true;
						}
					}
				}

				if (end != -1 && start != -1) {
					std::string stuff = line.substr(start, end - start + 1);
					std::cout << "Params are: " << stuff << std::endl;
					parse(stuff, params);
				} else {
					//No more parenthesis. Cut condition here for second one
				}
			} else std::cout << "No second params found" << std::endl;

		}

		virtual std::string getTag() {
			return "+";
		}

};

#endif /* EXPRESSIONSUM_H_ */
