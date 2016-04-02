/*
 * List.h
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#ifndef LISTA_H_
#define LISTA_H_

#include "Node.h"

/**
 * Trying to imitate the java.util.List interface
 */
template<class T> class List {
    private:
        Node<T>* first;
        unsigned int count;
        Node<T>* c;

    public:
        List();
        bool isEmpty();
        unsigned int size();
        void add(T element);
        void add(T element, unsigned int pos);
        T get(unsigned int pos);
        void set(T element, unsigned int pos);
        void remove(unsigned int pos);
        void cursorReset();
        bool cursorNext();
        T getCursor();
        void clear();
        virtual ~List();

    private:
        Node<T>* getNode(unsigned int pos);
};

#endif /* LISTA_H_ */
