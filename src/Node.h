/*
 * Node.h
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#ifndef NODE_H_
#define NODE_H_

#include <cstdio>

template<class T> class Node {
    private:
        T element;
        Node<T>* nextNode;

    public:
        Node(T data);
        T get();
        void setElement(T element);
        Node<T>* next();
        void setNext(Node<T>* node);
        virtual ~Node();
};

#endif /* NODO_H_ */
