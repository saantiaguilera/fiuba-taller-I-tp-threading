/*
 * UserRuntimeExpressionsInterface.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#include <map>

class UserRuntimeExpressionsInterface {
	public:
		virtual std::map<std::string, Expression> getUserExpressions();
		virtual ~UserRuntimeExpressionsInterface() {};

    private:
		UserRuntimeExpressionsInterface(const UserRuntimeExpressionsInterface&);
		UserRuntimeExpressionsInterface& operator=(const UserRuntimeExpressionsInterface&);
};

