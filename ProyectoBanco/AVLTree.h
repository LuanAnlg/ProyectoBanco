#pragma once

#include "BNode.h"
#include <functional>

template <class C>
class AVLTree {
private:
    BNode<C>* root; // Nodo ra�z del �rbol
    function<bool(C, C)> compare; // Funci�n de comparaci�n para los elementos

    // M�todos privados de balanceo y rotaci�n
    int _height(BNode<C>* node) const;
    int _balanceFactor(BNode<C>* node) const;
    BNode<C>* _rightRotate(BNode<C>* node);
    BNode<C>* _leftRotate(BNode<C>* node);
    BNode<C>* _balance(BNode<C>* node);
    void _updateHeight(BNode<C>* node);

    // M�todos privados de inserci�n, eliminaci�n y recorrido
    BNode<C>* _insert(BNode<C>* node, const C& value);
    BNode<C>* _remove(BNode<C>* node, const C& value);
    void _destroyTree(BNode<C>* node);
    void _inOrder(BNode<C>* node, function<void(const C&)> func) const;
    void _preOrder(BNode<C>* node, function<void(const C&)> func) const;
    void _postOrder(BNode<C>* node, function<void(const C&)> func) const;
    BNode<C>* _minorNode(BNode<C>* node);

public:
    // Constructor y destructor
    AVLTree(const function<bool(C, C)>& compare);
    ~AVLTree();

    // M�todos de estado y limpieza
    bool empty() const;
    void clear();

    // M�todos de inserci�n y eliminaci�n
    void insert(const C& value);
    void remove(const C& value);

    // M�todos de recorrido
    void inOrder(function<void(const C&)> func) const;
    void preOrder(function<void(const C&)> func) const;
    void postOrder(function<void(const C&)> func) const;

    // M�todos de acceso al �ltimo elemento
    C getBack() const;
    void popBack();
};

// Implementaci�n del constructor
template <class C>
AVLTree<C>::AVLTree(const function<bool(C, C)>& compare)
    : root(nullptr), compare(compare) {}

// Implementaci�n del destructor
template <class C>
AVLTree<C>::~AVLTree() {
    _destroyTree(root);
}

// M�todo para obtener la altura de un nodo
template <class C>
int AVLTree<C>::_height(BNode<C>* node) const {
    return node ? node->getHeight() : 0;
}

// M�todo para actualizar la altura de un nodo
template <class C>
void AVLTree<C>::_updateHeight(BNode<C>* node) {
    if (node) {
        int leftHeight = _height(node->getLeft());
        int rightHeight = _height(node->getRight());
        node->setHeight(1 + max(leftHeight, rightHeight));
    }
}

// M�todo para calcular el factor de balance de un nodo
template <class C>
int AVLTree<C>::_balanceFactor(BNode<C>* node) const {
    return node ? _height(node->getLeft()) - _height(node->getRight()) : 0;
}

// Rotaci�n a la derecha
template <class C>
BNode<C>* AVLTree<C>::_rightRotate(BNode<C>* y) {
    BNode<C>* x = y->getLeft();
    BNode<C>* T2 = x->getRight();

    // Realizar la rotaci�n
    x->setRight(y);
    y->setLeft(T2);

    // Actualizar alturas
    _updateHeight(y);
    _updateHeight(x);

    return x;
}

// Rotaci�n a la izquierda
template <class C>
BNode<C>* AVLTree<C>::_leftRotate(BNode<C>* x) {
    BNode<C>* y = x->getRight();
    BNode<C>* T2 = y->getLeft();

    // Realizar la rotaci�n
    y->setLeft(x);
    x->setRight(T2);

    // Actualizar alturas
    _updateHeight(x);
    _updateHeight(y);

    return y;
}

// Balancear un nodo
template <class C>
BNode<C>* AVLTree<C>::_balance(BNode<C>* node) {
    int balance = _balanceFactor(node);

    // Caso Izquierda Izquierda
    if (balance > 1 && _balanceFactor(node->getLeft()) >= 0) {
        return _rightRotate(node);
    }

    // Caso Izquierda Derecha
    if (balance > 1 && _balanceFactor(node->getLeft()) < 0) {
        node->setLeft(_leftRotate(node->getLeft()));
        return _rightRotate(node);
    }

    // Caso Derecha Derecha
    if (balance < -1 && _balanceFactor(node->getRight()) <= 0) {
        return _leftRotate(node);
    }

    // Caso Derecha Izquierda
    if (balance < -1 && _balanceFactor(node->getRight()) > 0) {
        node->setRight(_rightRotate(node->getRight()));
        return _leftRotate(node);
    }

    return node; // Nodo balanceado
}

// M�todo recursivo para destruir el �rbol
template <class C>
void AVLTree<C>::_destroyTree(BNode<C>* node) {
    if (node) {
        _destroyTree(node->getLeft());
        _destroyTree(node->getRight());
        delete node;
    }
}

// M�todo p�blico para insertar un valor
template <class C>
void AVLTree<C>::insert(const C& value) {
    root = _insert(root, value);
}

// M�todo recursivo para insertar un valor
template <class C>
BNode<C>* AVLTree<C>::_insert(BNode<C>* node, const C& value) {
    if (!node) {
        return new BNode<C>(value);
    }

    if (compare(value, node->getData())) {
        node->setLeft(_insert(node->getLeft(), value));
    }
    else if (compare(node->getData(), value)) {
        node->setRight(_insert(node->getRight(), value));
    }
    else {
        return node; // Valor duplicado, no se inserta
    }

    _updateHeight(node);
    return _balance(node);
}

// M�todo p�blico para eliminar un valor
template <class C>
void AVLTree<C>::remove(const C& value) {
    root = _remove(root, value);
}

// M�todo recursivo para eliminar un valor
template <class C>
BNode<C>* AVLTree<C>::_remove(BNode<C>* node, const C& value) {
    if (!node) return node;

    if (compare(value, node->getData())) {
        node->setLeft(_remove(node->getLeft(), value));
    }
    else if (compare(node->getData(), value)) {
        node->setRight(_remove(node->getRight(), value));
    }
    else {
        if (!node->getLeft() || !node->getRight()) {
            BNode<C>* temp = node->getLeft() ? node->getLeft() : node->getRight();
            delete node;
            return temp;
        }
        else {
            BNode<C>* temp = _minorNode(node->getRight());
            node->setData(temp->getData());
            node->setRight(_remove(node->getRight(), temp->getData()));
        }
    }

    _updateHeight(node);
    return _balance(node);
}

// Encuentra el nodo con el valor m�nimo
template <class C>
BNode<C>* AVLTree<C>::_minorNode(BNode<C>* node) {
    while (node && node->getLeft() != nullptr) {
        node = node->getLeft();
    }
    return node;
}

// M�todos de recorrido
template <class C>
void AVLTree<C>::_inOrder(BNode<C>* node, function<void(const C&)> func) const {
    if (!node) return;
    _inOrder(node->getLeft(), func);
    func(node->getData());
    _inOrder(node->getRight(), func);
}

template <class C>
void AVLTree<C>::inOrder(function<void(const C&)> func) const {
    _inOrder(root, func);
}

template <class C>
void AVLTree<C>::_preOrder(BNode<C>* node, function<void(const C&)> func) const {
    if (!node) return;
    func(node->getData());
    _preOrder(node->getLeft(), func);
    _preOrder(node->getRight(), func);
}

template <class C>
void AVLTree<C>::preOrder(function<void(const C&)> func) const {
    _preOrder(root, func);
}

template <class C>
void AVLTree<C>::_postOrder(BNode<C>* node, function<void(const C&)> func) const {
    if (!node) return;
    _postOrder(node->getLeft(), func);
    _postOrder(node->getRight(), func);
    func(node->getData());
}

template <class C>
void AVLTree<C>::postOrder(function<void(const C&)> func) const {
    _postOrder(root, func);
}

// Obtener el �ltimo elemento en orden
template <class C>
C AVLTree<C>::getBack() const {
    if (!root) throw runtime_error("Empty tree");
    BNode<C>* current = root;
    while (current->getRight() != nullptr) {
        current = current->getRight();
    }
    return current->getData();
}

// Eliminar el �ltimo elemento en orden
template <class C>
void AVLTree<C>::popBack() {
    if (!root) throw runtime_error("Empty tree");
    C maxValue = getBack();
    remove(maxValue);
}

// M�todo para verificar si el �rbol est� vac�o
template <class C>
bool AVLTree<C>::empty() const {
    return root == nullptr;
}

// M�todo para eliminar todos los nodos del �rbol
template <class C>
void AVLTree<C>::clear() {
    _destroyTree(root);
    root = nullptr;
}