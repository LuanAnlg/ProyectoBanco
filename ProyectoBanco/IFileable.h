#pragma once

#include <string>
#include <fstream>

using namespace std;

// Interfaz para manipular archivos.
class IFileable
{
public:
    virtual ~IFileable() = default;

    // Guarda el objeto en un archivo
    virtual bool saveToFile() const = 0;

    // Carga el objeto desde un archivo
    virtual bool loadFromFile() = 0;
};