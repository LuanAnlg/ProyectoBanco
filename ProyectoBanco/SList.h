#pragma once

#include "SNode.h"
#include <functional>
#include <iterator>

template<class C>
class SList {
private:
    SNode<C>* head;   // Puntero al primer nodo
    SNode<C>* tail;   // Puntero al último nodo
    size_t length;    // Número de elementos

public:
    // Constructores y destructores

    // Constructor por defecto, inicializa una lista vacía
    SList();

    // Destructor, limpia la lista liberando la memoria
    ~SList();

    // Métodos de estado y tamaño

    // Retorna true si la lista está vacía
    bool empty() const;
    // Retorna el número de elementos en la lista
    size_t size() const;

    // Métodos de inserción y eliminación

    // Inserta un elemento al principio de la lista
    void pushFront(const C& data);
    // Inserta un elemento al final de la lista
    void pushBack(const C& data);
    // Elimina el primer elemento de la lista
    void popFront();
    // Elimina el último elemento de la lista
    void popBack();
    // Retorna el elemento en la posición indicada
    C& getAt(size_t pos) const;
    // Elimina todos los elementos de la lista
    void clear();

    // Métodos de operaciones

    // Aplica una operación a todos los elementos de la lista
    void apply(const std::function<void(C&)>& operation);
    // Filtra los elementos de la lista según un predicado
    SList<C> filter(const std::function<bool(C)>& predicate) const;
    // Mezcla aleatoriamente los elementos de la lista
    void shuffle();
    // Ordena la lista utilizando el algoritmo de burbuja
    void bubbleSort(const std::function<bool(const C&, const C&)>& compare);
    // Ordena la lista utilizando el algoritmo de selección
    void selectionSort(const std::function<bool(const C&, const C&)>& compare);
    // Ordena la lista utilizando el algoritmo de inserción
    void insertionSort(const std::function<bool(const C&, const C&)>& compare);
    // Ordena la lista utilizando el algoritmo de Shell Sort
    void shellSort(const std::function<bool(const C&, const C&)>& compare);

    // Clase interna Iterator

    class Iterator {
    private:
        SNode<C>* current;  // Nodo actual del iterador

    public:
        // Constructor del iterador que inicializa con un nodo
        explicit Iterator(SNode<C>* node);
        // Incrementa el iterador para apuntar al siguiente nodo
        Iterator& operator++();
        // Compara dos iteradores para ver si son diferentes
        bool operator!=(const Iterator& other) const;
        // Dereferencia el iterador para acceder al valor del nodo
        C& operator*();
    };

    // Métodos para obtener los iteradores de la lista

    // Retorna un iterador al primer nodo de la lista
    Iterator begin() const;
    // Retorna un iterador al nodo después del último nodo
    Iterator end() const;
};

template<class C>
SList<C>::SList() : head(nullptr), tail(nullptr), length(0) {}

template<class C>
SList<C>::~SList() {
    clear();
}

template<class C>
bool SList<C>::empty() const {
    return length == 0;
}

template<class C>
size_t SList<C>::size() const {
    return length;
}

template<class C>
void SList<C>::pushFront(const C& data) {
    // Crear el nuevo nodo con el siguiente nodo apuntando a la cabeza actual
    SNode<C>* newNode = new SNode<C>(data, head);

    // Actualizar la cabeza de la lista para que apunte al nuevo nodo
    head = newNode;

    // Si la lista estaba vacía, el nuevo nodo también es el tail
    if (tail == nullptr) {
        tail = newNode;
    }

    // Incrementar el tamaño de la lista
    ++length;
}

template<class C>
void SList<C>::pushBack(const C& data) {
    // Crear el nuevo nodo con el siguiente nodo apuntando a nullptr (será el último)
    SNode<C>* newNode = new SNode<C>(data, nullptr);

    // Si la lista está vacía, tanto head como tail deben apuntar al nuevo nodo
    if (empty()) {
        head = tail = newNode;
    }
    else {
        // Si no está vacía, agregar el nuevo nodo al final y actualizar el tail
        tail->setNext(newNode);
        tail = newNode;
    }

    // Incrementar el tamaño de la lista
    ++length;
}

template<class C>
void SList<C>::popFront() {
    if (empty()) {
        throw std::runtime_error("Cannot pop from empty list");
    }

    SNode<C>* temp = head;
    head = head->getNext();
    delete temp;

    if (head == nullptr) {
        tail = nullptr;
    }
    --length;
}

template<class C>
void SList<C>::popBack() {
    if (empty()) {
        throw std::runtime_error("Cannot pop from empty list");
    }

    if (head == tail) {
        delete head;
        head = tail = nullptr;
    }
    else {
        SNode<C>* current = head;
        while (current->getNext() != tail) {
            current = current->getNext();
        }
        delete tail;
        tail = current;
        tail->setNext(nullptr);
    }
    --length;
}

template<class C>
C& SList<C>::getAt(size_t pos) const {
    if (pos >= length) {
        throw std::runtime_error("Index out of bounds");
    }

    SNode<C>* current = head;
    for (size_t i = 0; i < pos; ++i) {
        current = current->getNext();
    }
    return current->getData();
}

template<class C>
void SList<C>::clear() {
    while (!empty()) {
        popFront();
    }
}

template<class C>
void SList<C>::apply(const std::function<void(C&)>& operation) {
    for (auto& elem : *this) {
        operation(elem);
    }
}

template<class C>
SList<C> SList<C>::filter(const std::function<bool(C)>& predicate) const {
    SList<C> filteredList;
    for (const auto& elem : *this) {
        if (predicate(elem)) {
            filteredList.pushBack(elem);
        }
    }
    return filteredList;
}

template<class C>
void SList<C>::shuffle() {
    if (length < 2) return;

    for (size_t i = length - 1; i > 0; --i) {
        // Encontrar nodo en posición i
        SNode<C>* iNode = head;
        for (size_t k = 0; k < i; ++k) {
            iNode = iNode->getNext();
        }

        // Generar posición aleatoria j
        size_t j = rand() % (i + 1);

        // Encontrar nodo en posición j
        SNode<C>* jNode = head;
        for (size_t k = 0; k < j; ++k) {
            jNode = jNode->getNext();
        }

        // Intercambiar datos
        C temp = iNode->getData();
        iNode->setData(jNode->getData());
        jNode->setData(temp);
    }
}

template<class C>
void SList<C>::bubbleSort(const std::function<bool(const C&, const C&)>& compare) {
    if (length < 2) return;

    bool swapped;
    SNode<C>* current;
    SNode<C>* lastSorted = nullptr;

    do {
        swapped = false;
        current = head;

        while (current->getNext() != lastSorted) {
            if (!compare(current->getData(), current->getNext()->getData())) {
                C temp = current->getData();
                current->setData(current->getNext()->getData());
                current->getNext()->setData(temp);
                swapped = true;
            }
            current = current->getNext();
        }
        lastSorted = current;
    } while (swapped);
}

template<class C>
void SList<C>::selectionSort(const std::function<bool(const C&, const C&)>& compare) {
    if (length < 2) return;

    SNode<C>* current = head;
    while (current != nullptr) {
        SNode<C>* minNode = current;
        SNode<C>* searchNode = current->getNext();

        while (searchNode != nullptr) {
            if (!compare(minNode->getData(), searchNode->getData())) {
                minNode = searchNode;
            }
            searchNode = searchNode->getNext();
        }

        if (minNode != current) {
            C temp = current->getData();
            current->setData(minNode->getData());
            minNode->setData(temp);
        }

        current = current->getNext();
    }
}

template<class C>
void SList<C>::insertionSort(const std::function<bool(const C&, const C&)>& compare) {
    if (length < 2) return;

    SNode<C>* sorted = head;
    SNode<C>* unsorted = head->getNext();

    while (unsorted != nullptr) {
        C key = unsorted->getData();
        SNode<C>* current = head;

        while (current != unsorted && compare(current->getData(), key)) {
            current = current->getNext();
        }

        if (current != unsorted) {
            // Mover el nodo a su posición correcta
            C temp = key;
            SNode<C>* moveNode = unsorted;
            while (moveNode != current) {
                SNode<C>* prev = head;
                while (prev->getNext() != moveNode) {
                    prev = prev->getNext();
                }
                moveNode->setData(prev->getData());
                moveNode = prev;
            }
            current->setData(temp);
        }

        unsorted = unsorted->getNext();
    }
}

template<class C>
void SList<C>::shellSort(const std::function<bool(const C&, const C&)>& compare) {
    if (length < 2) return;

    size_t gap = length / 2;
    while (gap > 0) {
        for (size_t i = gap; i < length; ++i) {
            // Obtener el nodo en posición i
            SNode<C>* iNode = head;
            for (size_t k = 0; k < i; ++k) {
                iNode = iNode->getNext();
            }
            C temp = iNode->getData();

            // Comparar y mover nodos
            size_t j = i;
            SNode<C>* jNode = iNode;
            SNode<C>* gapNode = head;
            for (size_t k = 0; k < j - gap; ++k) {
                gapNode = gapNode->getNext();
            }

            while (j >= gap && !compare(gapNode->getData(), temp)) {
                jNode->setData(gapNode->getData());
                jNode = gapNode;
                j -= gap;

                if (j >= gap) {
                    gapNode = head;
                    for (size_t k = 0; k < j - gap; ++k) {
                        gapNode = gapNode->getNext();
                    }
                }
            }
            jNode->setData(temp);
        }
        gap /= 2;
    }
}

template<class C>
SList<C>::Iterator::Iterator(SNode<C>* node) : current(node) {}

template<class C>
typename SList<C>::Iterator& SList<C>::Iterator::operator++() {
    if (current != nullptr)
        current = current->getNext();
    return *this;
}

template<class C>
bool SList<C>::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

template<class C>
C& SList<C>::Iterator::operator*() {
    if (current == nullptr) {
        throw std::runtime_error("Dereferencing a null iterator");
    }
    return current->getData();
}

template<class C>
typename SList<C>::Iterator SList<C>::begin() const {
    return Iterator(head);
}

template<class C>
typename SList<C>::Iterator SList<C>::end() const {
    return Iterator(nullptr);
}
