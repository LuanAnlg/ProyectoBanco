#pragma once

#include <stdexcept>

template<class C>
class SNode
{
private:
    C data;               // Dato almacenado en el nodo
    SNode<C>* next;       // Puntero al siguiente nodo

public:
    // Constructores

    // Constructor que inicializa el nodo con un valor de dato y puntero al siguiente
    SNode(const C& data = C(), SNode<C>* next = nullptr);
    // Destructor del nodo
    ~SNode();

    // Métodos de acceso

    // Retorna una referencia al dato almacenado en el nodo
    C& getData();
    // Retorna una referencia constante al dato almacenado en el nodo
    const C& getData() const;
    // Retorna el puntero al siguiente nodo
    SNode<C>* getNext() const;

    // Métodos de modificación

    // Establece el dato almacenado en el nodo
    void setData(const C& data);
    // Establece el puntero al siguiente nodo
    void setNext(SNode<C>* next);
};


// Implementacion del constructor
template<class C>
SNode<C>::SNode(const C& data, SNode<C>* next) :
    data(data), next(next) {}

// Implementacion del destructor
template<class C>
SNode<C>::~SNode() = default;

// Implementacion de los getters

template<class C>
C& SNode<C>::getData()
{
    return data;
}

template<class C>
const C& SNode<C>::getData() const
{
    return data;
}

template<class C>
SNode<C>* SNode<C>::getNext() const
{
    return next;
}

// Implementacion de los setters

template<class C>
void SNode<C>::setData(const C& data)
{
    this->data = data;
}

template<class C>
void SNode<C>::setNext(SNode<C>* next)
{
    if (next == this)
    {
        throw std::runtime_error("Node can't point to themself");
    }
    this->next = next;
}