/*
 * ReentrantLock.h
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#ifndef THREADING_REENTRANTLOCK_H_
#define THREADING_REENTRANTLOCK_H_

/**
 * Simple class that resembles a ReentrantLock
 *
 * This class allows only one thread at a time
 * to move over the same scope where this was
 * created
 */
class ReentrantLock {
    private:
        Mutex &m;

    public:
        explicit ReentrantLock(Mutex &m);
        ~ReentrantLock();

    private:
        ReentrantLock(const ReentrantLock&);
        ReentrantLock& operator=(const ReentrantLock&);
};

#endif /* THREADING_REENTRANTLOCK_H_ */
