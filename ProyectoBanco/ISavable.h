#pragma once

#include "Serialization.h"
#include <string>
#include <sstream>

using namespace std;

// Interfaz para serializar y deserializar objetos
class ISavable
{
public:
    // Destructor virtual por defecto
    virtual ~ISavable() = default;

    // Serializa el objeto en un string
    virtual string toSave() const = 0;
    // Deserializa el objeto desde un string
    virtual void load(const string& data) = 0;
};