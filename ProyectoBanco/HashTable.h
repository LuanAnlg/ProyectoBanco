#pragma once

#include "HashEntity.h"

template <typename C>
class HashTable {
private:
    size_t capacity;               // capacidad
    size_t length;                 // cantidad de elementos dentro
    HashEntity<C>** table;         // puntero a un arreglo de punteros a entidades hash

    size_t hash(const string& key) {
        size_t hashValue = 0;
        for (char ch : key) {
            hashValue = hashValue * 31 + ch; // simple hash usando la suma ponderada de caracteres
        }
        return hashValue % capacity;
    }

    void expand() {
        size_t oldCapacity = capacity;
        capacity *= 2;
        HashEntity<C>** newTable = new HashEntity<C>*[capacity];

        for (size_t i = 0; i < capacity; ++i) {
            newTable[i] = nullptr;
        }

        for (size_t i = 0; i < oldCapacity; ++i) {
            if (table[i] != nullptr) {
                size_t newIndex = hash(table[i]->key);
                while (newTable[newIndex] != nullptr) {
                    newIndex = (newIndex + 1) % capacity;
                }
                newTable[newIndex] = table[i];
            }
        }

        delete[] table;
        table = newTable;
    }

public:
    HashTable(size_t initialCapacity) : capacity(initialCapacity), length(0) {
        table = new HashEntity<C>*[capacity];
        for (size_t i = 0; i < capacity; ++i) {
            table[i] = nullptr;
        }
    }

    bool addElement(const string& key, const C& element) {
        if (length >= capacity * 0.7) { // Si se supera el 70% de la capacidad, expandir
            expand();
        }

        size_t index = hash(key);
        while (table[index] != nullptr && table[index]->key != key) {
            index = (index + 1) % capacity; // Manejar colisiones mediante sondeo lineal
        }

        if (table[index] == nullptr) {
            // Si la posición está vacía, crear un nuevo elemento
            table[index] = new HashEntity<C>(key, element);
            length++;
            return true;
        }
        else {
            // Si ya existe un elemento con la misma clave, sobrescribir el valor
            table[index]->element = element;
            return false; // Devuelve falso indicando que se actualizó
        }
    }

    C getElement(const string& key) {
        size_t index = hash(key);
        while (table[index] != nullptr) {
            if (table[index]->key == key) {
                return table[index]->element;
            }
            index = (index + 1) % capacity;
        }
        throw std::runtime_error("Clave no encontrada en la tabla hash.");
    }

    bool empty() { return length == 0; }

    void clear() {
        for (size_t i = 0; i < capacity; ++i) {
            if (table[i] != nullptr) {
                delete table[i];
                table[i] = nullptr;
            }
        }
        length = 0;
    }

    ~HashTable() {
        clear();
        delete[] table;
    }
};
