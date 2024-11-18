#pragma once

#include <string>
#include <stdexcept>

using namespace std;

// Interfaz para obtener representaciones en string de objetos para depuración.
class IDebugable
{
public:
    // Destructor virtual por defecto
    virtual ~IDebugable() = default;

    // Obtiene una representación en string del objeto
    virtual string toDebug() const = 0;
};