#pragma once

#include "SNode.h"
#include <iterator>
#include <functional>

template<class C>
class SStack
{
private:
    SNode<C>* head;
    size_t length;

public:
    SStack();
    SStack(const SStack<C>& other);
    ~SStack();

    bool empty() const;
    size_t size() const;
    void push(const C& data);
    void pop();
    void clear();
    void invert();
    const C& top() const;

    void apply(const std::function<void(C&)>& operation);
    SStack<C> filter(const std::function<bool(C)>& predicate) const;

    class Iterator
    {
    private:
        SNode<C>* current;

    public:
        Iterator(SNode<C>* node) : current(node) {}

        Iterator& operator++();
        bool operator!=(const Iterator& other) const;
        C& operator*() const;
    };

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
};

template<class C>
SStack<C>::SStack() : head(nullptr), length(0) {}

template<class C>
SStack<C>::SStack(const SStack<C>& other) : head(nullptr), length(0) {
    SNode<C>* current = other.head;
    SNode<C>* prev = nullptr;

    while (current != nullptr) {
        SNode<C>* newNode = new SNode<C>(current->getData());
        if (prev == nullptr) {
            head = newNode;
        }
        else {
            prev->setNext(newNode);
        }
        prev = newNode;
        current = current->getNext();
    }

    length = other.length;
}


template<class C>
SStack<C>::~SStack()
{
    clear();
}

template<class C>
bool SStack<C>::empty() const
{
    return length == 0;
}

template<class C>
size_t SStack<C>::size() const
{
    return length;
}

template<class C>
void SStack<C>::push(const C& data)
{
    head = new SNode<C>(data, head);
    ++length;
}

template<class C>
void SStack<C>::pop()
{
    if (empty())
    {
        throw std::runtime_error("Cannot pop from empty stack");
    }

    SNode<C>* nodeToDelete = head;
    head = head->getNext();
    delete nodeToDelete;
    --length;
}

template<class C>
const C& SStack<C>::top() const {
    if (empty()) {
        throw std::runtime_error("Cannot access top of an empty stack");
    }
    return head->getData();
}


template<class C>
void SStack<C>::clear()
{
    while (!empty())
    {
        pop();
    }
}

template<class C>
void SStack<C>::invert()
{
    if (empty() || length == 1) {
        // No es necesario invertir si la pila está vacía o tiene un solo elemento
        return;
    }

    SNode<C>* prev = nullptr;
    SNode<C>* current = head;
    SNode<C>* next = nullptr;

    while (current != nullptr) {
        next = current->getNext();  // Guarda el siguiente nodo
        current->setNext(prev);     // Invierte el enlace
        prev = current;             // Mueve 'prev' a 'current'
        current = next;             // Mueve 'current' a 'next'
    }

    head = prev;  // 'prev' es el nuevo 'head' después de la inversión
}

template<class C>
void SStack<C>::apply(const std::function<void(C&)>& operation)
{
    for (auto& elem : *this)
    {
        operation(elem);
    }
}

template<class C>
SStack<C> SStack<C>::filter(const std::function<bool(C)>& predicate) const
{
    SStack<C> filteredStack;

    for (auto& elem : *this)
    {
        if (predicate(elem))
        {
            filteredStack.push(elem);
        }
    }

    return filteredStack;
}

// Iterator methods
template<class C>
typename SStack<C>::Iterator& SStack<C>::Iterator::operator++()
{
    if (current != nullptr)
    {
        current = current->getNext();
    }
    return *this;
}

template<class C>
bool SStack<C>::Iterator::operator!=(const Iterator& other) const
{
    return current != other.current;
}

template<class C>
C& SStack<C>::Iterator::operator*() const {
    if (current == nullptr) {
        throw std::runtime_error("Attempt to dereference an end() iterator");
    }
    return current->getData();
}