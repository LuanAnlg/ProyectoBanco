#pragma once

#include <cstdlib>
#include <ctime>

using namespace std;

// Interfaz para clases que pueden generar sus atributos de forma aleatoria.
class IRandomizable {
public:
    // Destructor virtual
    virtual ~IRandomizable() = default;

    // Método que debe implementarse para generar valores aleatorios.
    virtual void generateRandom() = 0;
};