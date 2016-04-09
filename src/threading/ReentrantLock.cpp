/*
 * ReentrantLock.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#include "Mutex.h"
#include "ReentrantLock.h"

ReentrantLock::ReentrantLock(Mutex &m) : m(m) {
    m.lock();
}

ReentrantLock::~ReentrantLock() {
    m.unlock();
}
