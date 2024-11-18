#pragma once

template <class C>
class BNode
{
private:
    C data;             // Datos almacenados en el nodo
    BNode<C>* left;     // Apuntador al hijo izquierdo
    BNode<C>* right;    // Apuntador al hijo derecho
    int height;         // Altura del nodo

public:
    // Constructor con inicialización de datos y punteros a nullptr por defecto
    BNode(const C& value = C(), BNode<C>* left = nullptr, BNode<C>* right = nullptr);

    // Destructor predeterminado
    ~BNode() = default;

    // Getters
    C& getData();
    const C& getData() const;
    BNode<C>* getLeft() const;
    BNode<C>* getRight() const;
    int getHeight() const;

    // Setters
    void setData(const C& value);
    void setLeft(BNode<C>* leftNode);
    void setRight(BNode<C>* rightNode);
    void setHeight(int h);
};

// Implementación del constructor
template <class C>
BNode<C>::BNode(const C& value, BNode<C>* left, BNode<C>* right)
    : data(value), left(left), right(right), height(0) {
}

// Implementación de los getters
template <class C>
C& BNode<C>::getData() {
    return data;
}

template <class C>
const C& BNode<C>::getData() const {
    return data;
}

template <class C>
BNode<C>* BNode<C>::getLeft() const {
    return left;
}

template <class C>
BNode<C>* BNode<C>::getRight() const {
    return right;
}

template <class C>
int BNode<C>::getHeight() const {
    return height;
}

// Implementación de los setters
template <class C>
void BNode<C>::setData(const C& value) {
    data = value;
}

template <class C>
void BNode<C>::setLeft(BNode<C>* leftNode) {
    left = leftNode;
}

template <class C>
void BNode<C>::setRight(BNode<C>* rightNode) {
    right = rightNode;
}

template <class C>
void BNode<C>::setHeight(int h) {
    height = h;
}