/*
 * ReentrantLock.h
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#ifndef THREADING_REENTRANTLOCK_H_
#define THREADING_REENTRANTLOCK_H_

class ReentrantLock {
    private:
        Mutex &m;

    public:
        ReentrantLock(Mutex &m);
        ~ReentrantLock();

    private:
        ReentrantLock(const ReentrantLock&);
        ReentrantLock& operator=(const ReentrantLock&);
};

#endif /* THREADING_REENTRANTLOCK_H_ */
