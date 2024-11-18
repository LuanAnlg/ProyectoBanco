#pragma once

#include "Format.h"

#include "iostream"

using namespace std;

// Interfaz para clases que permiten interactuar con el usuario.
class IInteractive {
public:
    // Destructor virtual
    virtual ~IInteractive() = default;

    // Método que debe implementarse para interactuar con el usuario.
    virtual void interact() = 0;
};