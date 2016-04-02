/*
 * List.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#include "List.h"

template<class T> List<T>::List() {
    this->first = NULL;
    this->count = 0;
    this->c = NULL;
}

template<class T> bool List<T>::isEmpty() {
    return (this->count == 0);
}

template<class T> unsigned int List<T>::size() {
    return this->count;
}

template<class T> void List<T>::add(T element) {
    this->add(element, this->count + 1);
}

template<class T> void List<T>::add(T element, unsigned int pos) {
    if ((pos > 0) && (pos <= this->count + 1)) {
        Node<T>* nuevo = new Node<T>(element);

        if (pos == 1) {
            nuevo->setNext(this->first);
            this->first = nuevo;
        } else {
            Node<T>* anterior = this->getNode(pos - 1);
            nuevo->setNext(anterior->next());
            anterior->setNext(nuevo);
        }

        this->count++;

        this->cursorReset();
    }
}

template<class T> T List<T>::get(unsigned int pos) {
    T element;

    if ((pos > 0) && (pos <= this->count))
    	element = this->getNode(pos)->get();

    return element;
}

template<class T> void List<T>::set(T element, unsigned int pos) {
    if ((pos > 0) && (pos <= this->count))
        this->getNode(pos)->setElement(element);
}

template<class T> void List<T>::remove(unsigned int pos) {
    if ((pos > 0) && (pos <= this->count)) {
        Node<T>* nodeToRemove;

        if (pos == 1) {
        	nodeToRemove = this->first;
            this->first = nodeToRemove->next();
        } else {
            Node<T>* anterior = this->getNode(pos - 1);
            nodeToRemove = anterior->next();
            anterior->cambiarSiguiente(nodeToRemove->next());
        }

        delete nodeToRemove;
        this->count--;

        this->cursorReset();
    }
}

template<class T> void List<T>::cursorReset() {
    this->c = NULL;
}

template<class T> bool List<T>::cursorNext() {
    if (this->c == NULL)
        this->c = this->first;
    else
        this->c = this->c->next();

    return (this->c != NULL);
}

template<class T> T List<T>::getCursor() {
    T element;

    if (this->c != NULL)
    	element = this->c->get();

    return element;
}

template<class T> void List<T>::clear(){
    while (this->first != NULL)
        this->remove(1);
}

template<class T> List<T>::~List() {
    while (this->first != NULL) {
        Node<T>* nodeToRemove = this->first;
        this->first = this->first->next();

        delete nodeToRemove;
    }
}

template<class T> Node<T>* List<T>::getNode(unsigned int pos) {
    Node<T>* currentNode = this->first;
    for (unsigned int i = 1; i < pos; i++)
    	currentNode = currentNode->next();

    return currentNode;
}


