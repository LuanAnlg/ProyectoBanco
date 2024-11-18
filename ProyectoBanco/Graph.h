#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <class C, C empty = -1>
class Arc {
public:
    C data;
    size_t arrive;

    Arc(size_t arrive, C data = empty) : data(data), arrive(arrive) {}
};

template <class C, C empty = -1>
class Vertex {
public:
    C data;
    vector<Arc<C, empty>> adjacency;

    Vertex(C data = empty) : data(data) {}
};

template <class C, C empty = -1>
class Graph {
private:
    vector<Vertex<C, empty>> vertices;

public:
    Graph() = default;

    size_t size() const {
        return vertices.size();
    }

    size_t addVertex(const C& data) {
        vertices.emplace_back(data);
        return vertices.size() - 1;
    }

    C getVertex(size_t index) const {
        if (index >= vertices.size()) {
            throw out_of_range("Index out of range");
        }
        return vertices[index].data;
    }

    void setVertex(size_t index, C data) {
        if (index >= vertices.size()) {
            throw out_of_range("Index out of range");
        }
        vertices[index].data = data;
    }

    size_t addArc(size_t index, size_t arrive, C data = empty) {
        if (index >= vertices.size()) {
            throw out_of_range("Index out of range");
        }
        vertices[index].adjacency.emplace_back(arrive, data);
        return vertices[index].adjacency.size() - 1;
    }

    size_t vertexSize(size_t index) const {
        if (index >= vertices.size()) {
            throw out_of_range("Index out of range");
        }
        return vertices[index].adjacency.size();
    }

    C getArc(size_t vertexIndex, size_t arcIndex) const {
        if (vertexIndex >= vertices.size()) {
            throw out_of_range("Vertex index out of range");
        }
        const Vertex<C, empty>& vertex = vertices[vertexIndex];
        if (arcIndex >= vertex.adjacency.size()) {
            throw out_of_range("Arc index out of range");
        }
        return vertex.adjacency[arcIndex].data;
    }

    void setArc(size_t vertexIndex, size_t arcIndex, C data) {
        if (vertexIndex >= vertices.size()) {
            throw out_of_range("Vertex index out of range");
        }
        Vertex<C, empty>& vertex = vertices[vertexIndex];
        if (arcIndex >= vertex.adjacency.size()) {
            throw out_of_range("Arc index out of range");
        }
        vertex.adjacency[arcIndex].data = data;
    }

    size_t getArriveVertex(size_t vertexIndex, size_t arcIndex) const {
        if (vertexIndex >= vertices.size()) {
            throw out_of_range("Vertex index out of range");
        }
        const Vertex<C, empty>& vertex = vertices[vertexIndex];
        if (arcIndex >= vertex.adjacency.size()) {
            throw out_of_range("Arc index out of range");
        }
        return vertex.adjacency[arcIndex].arrive;
    }
};