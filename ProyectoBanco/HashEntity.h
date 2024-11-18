#pragma once

#include <stdexcept>
#include <string>

using namespace std;

template <typename C>
class HashEntity {
public:
    string key;
    C element;

    // Constructor
    HashEntity(const string& k, const C& e) : key(k), element(e) {}
};