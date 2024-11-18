#pragma once

#include "SNode.h"
#include <iterator>
#include <functional>

template<class C>
class SQueue
{
private:
    SNode<C>* head;
    SNode<C>* tail;
    size_t length;

public:
    SQueue();
    ~SQueue();

    bool empty() const;
    size_t size() const;
    void push(const C& data);
    void pop();
    void clear();
    C& front() const;
    C& back() const;

    SNode<C>* getHead() const;
    SNode<C>* getTail() const;

    void apply(const std::function<void(C&)>& operation);
    SQueue<C> filter(const std::function<bool(C)>& predicate) const;

    class Iterator
    {
    private:
        SNode<C>* current;
    public:
        Iterator(SNode<C>* node) : current(node) {}

        Iterator& operator++();
        bool operator!=(const Iterator& other) const;
        C& operator*();
    };

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
};

template<class C>
SQueue<C>::SQueue() : head(nullptr), tail(nullptr), length(0) {}

template<class C>
SQueue<C>::~SQueue()
{
    clear();
}

template<class C>
bool SQueue<C>::empty() const
{
    return length == 0;
}

template<class C>
size_t SQueue<C>::size() const
{
    return length;
}

template<class C>
void SQueue<C>::push(const C& data)
{
    SNode<C>* newNode = new SNode<C>(data, nullptr);
    if (empty())
    {
        head = tail = newNode;
    }
    else
    {
        tail->setNext(newNode);
        tail = newNode;
    }
    length++;
}

template<class C>
void SQueue<C>::pop()
{
    if (empty())
    {
        throw std::runtime_error("Cannot pop from empty queue");
    }

    SNode<C>* aux = head;
    head = head->getNext();

    if (head == nullptr)
    {
        tail = nullptr;
    }

    delete aux;
    length--;
}

template<class C>
void SQueue<C>::clear()
{
    while (!empty())
    {
        pop();
    }
}

template<class C>
C& SQueue<C>::front() const
{
    if (empty())
    {
        throw std::runtime_error("Cannot access front of empty queue");
    }
    return head->getData();
}

template<class C>
C& SQueue<C>::back() const
{
    if (empty())
    {
        throw std::runtime_error("Cannot access back of empty queue");
    }
    return tail->getData();
}

template<class C>
SNode<C>* SQueue<C>::getHead() const
{
    return head;
}

template<class C>
SNode<C>* SQueue<C>::getTail() const
{
    return tail;
}

template<class C>
void SQueue<C>::apply(const std::function<void(C&)>& operation)
{
    for (auto& elem : *this)
    {
        operation(elem);
    }
}

template<class C>
SQueue<C> SQueue<C>::filter(const std::function<bool(C)>& predicate) const
{
    SQueue<C> filteredQueue;

    for (auto& elem : *this)
    {
        if (predicate(elem))
        {
            filteredQueue.push(elem);
        }
    }

    return filteredQueue;
}

// Iterator methods
template<class C>
typename SQueue<C>::Iterator& SQueue<C>::Iterator::operator++()
{
    if (current != nullptr)
        current = current->getNext();
    return *this;
}

template<class C>
bool SQueue<C>::Iterator::operator!=(const Iterator& other) const
{
    return current != other.current;
}

template<class C>
C& SQueue<C>::Iterator::operator*()
{
    if (current == nullptr) {
        throw std::runtime_error("Dereferencing a null iterator");
    }
    return current->getData();
}
