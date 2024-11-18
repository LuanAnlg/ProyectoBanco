#pragma once

#include <string>
#include "Format.h"

using namespace std;

// Interfaz para obtener representaciones en string de objetos para visualizaci�n.
class IShowable
{
public:
    // Obtiene una representaci�n en string del objeto
    virtual string toShow() const = 0;

    // Destructor virtual por defecto
    virtual ~IShowable() = default;
};