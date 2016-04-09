/*
 * ParserWorkerThread.h
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#ifndef PARSERWORKERTHREAD_H_
#define PARSERWORKERTHREAD_H_

#include <pthread.h>

class ParserWorker: public Thread {
private:
	Expression *expression;

protected:
	virtual void run();

public:
	ParserWorker(Expression *expression);
};

#endif /* PARSERWORKERTHREAD_H_ */
