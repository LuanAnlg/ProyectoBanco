#pragma once

#include <string>
#include <stdexcept>

using namespace std;

// Interfaz para obtener representaciones en string de objetos para depuraci�n.
class IDebugable
{
public:
    // Destructor virtual por defecto
    virtual ~IDebugable() = default;

    // Obtiene una representaci�n en string del objeto
    virtual string toDebug() const = 0;
};