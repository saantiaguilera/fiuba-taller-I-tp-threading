/*
 * ParserWorker.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#include <string>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cctype>
#include <list>
#include <map>
#include <stdexcept>

class Expression;

#include "Mutex.h"

#include "../ParserUtils.h"
#include "../Expression.h"

#include <pthread.h>
#include "Thread.h"
#include "ParserWorker.h"

ParserWorker::ParserWorker(Expression *expression) :
		expression(expression) {
}

void ParserWorker::run() {
	expression->evaluate();
}
