/*
 * Node.cc
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#include "Node.h"

template<class T> Node<T>::Node(T data) {
    this->element = data;
    this->nextNode = NULL;
}

template<class T> T Node<T>::get() {
    return this->element;
}

template<class T> void Node<T>::setElement(T element) {
	this->element = element;
}

template<class T> Node<T> * Node<T>::next() {
	return this->nextNode;
}

template<class T> void Node<T>::setNext(Node<T> *node) {
    this->nextNode = node;
}
