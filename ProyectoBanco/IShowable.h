#pragma once

#include <string>
#include "Format.h"

using namespace std;

// Interfaz para obtener representaciones en string de objetos para visualización.
class IShowable
{
public:
    // Obtiene una representación en string del objeto
    virtual string toShow() const = 0;

    // Destructor virtual por defecto
    virtual ~IShowable() = default;
};