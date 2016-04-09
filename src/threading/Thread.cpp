/*
 * Thread.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#include <cstdio>
#include <pthread.h>

#include "Thread.h"

Thread::Thread() : thread() {
}

Thread::~Thread() {
}

void Thread::join() {
    pthread_join(thread, NULL);
}

void Thread::start() {
	pthread_create(&thread, NULL, Thread::runner, this);
}

void * Thread::runner(void *data) {
    Thread *self = (Thread*)data;
    self->run();
    return data;
}
