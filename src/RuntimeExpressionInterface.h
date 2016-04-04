/*
 * RuntimeExpressionInterface.h
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#ifndef RUNTIMEEXPRESSIONINTERFACE_H_
#define RUNTIMEEXPRESSIONINTERFACE_H_

class RuntimeExpressionInterface {
	public:
		virtual std::list<Expression*> getRuntimeExpressions() = 0;
		virtual ~RuntimeExpressionInterface() {};
};

#endif /* RUNTIMEEXPRESSIONINTERFACE_H_ */
