#pragma once

#include "IDebugable.h"
#include "ISavable.h"
#include "IRandomizable.h"

// Componente Monto
class Monto : public IDebugable, ISavable, IRandomizable
{
private:
    int soles;    // Parte entera del monto en soles
    int centimos; // Parte decimal del monto en c�ntimos

public:
    // Constructores

    // Constructor que establece el monto a partir de un valor float
    Monto(float monto);
    // Constructor que inicializa el monto a partir de una cadena de texto
    Monto(const string& datos);
    // Constructor por defecto, inicializa el monto a 0.00
    Monto();

    // M�todos de acceso

    // Retorna el monto total como un float
    float getMonto() const;
    //

    // M�todos de modificaci�n

    // Establece el monto con un float
    bool setMonto(const float& monto);

    // M�todos de conversi�n a string

    // Retorna el monto en formato de cadena
    string toString() const;

    // M�todo para depuraci�n

    // Retorna una representaci�n detallada del monto para prop�sitos de depuraci�n
    string toDebug() const override;

    // M�todos para guardar y cargar

    // Retorna el monto en un formato que puede ser guardado
    string toSave() const override;
    // M�todo para cargar el monto desde un string
    void load(const string& data) override;

    // M�todo para generar un monto aleatorio
    void generateRandom() override;
};

// Constructor que recibe un float
Monto::Monto(float monto) {
    if (monto < 0) {
        throw invalid_argument("El monto no puede ser negativo."); // Excepci�n si el monto es negativo
    }
    int montoInt = static_cast<int>(monto * 100 + 0.5f);
    soles = montoInt / 100;
    centimos = montoInt % 100;

    // Validaci�n de centimos
    if (centimos < 0 || centimos >= 100) {
        throw runtime_error("Valor de centimos fuera de rango (0-99).");
    }
}

// Constructor que inicializa el monto a partir de una cadena de texto
Monto::Monto(const string& datos) {
    load(datos);
}

// Constructor por defecto
Monto::Monto() : soles(0), centimos(0) {}

// Retorna el monto total como un float
float Monto::getMonto() const {
    return soles + centimos / 100.0f;
}

// Establece el monto con un float
bool Monto::setMonto(const float& monto) {
    if (monto < 0) {
        return false;
    }
    int montoInt = static_cast<int>(monto * 100 + 0.5f);
    soles = montoInt / 100;
    centimos = montoInt % 100;

    // Validaci�n de centimos
    if (centimos < 0 || centimos >= 100) {
        return false;
    }

    return true;
}

// Representaci�n en string del monto
string Monto::toString() const {
    ostringstream out;
    out << soles << "." << (centimos < 10 ? "0" : "") << centimos;
    return out.str();
}

// M�todo de depuraci�n
string Monto::toDebug() const {
    ostringstream debug;
    debug << "Monto(soles=" << soles << ", centimos='" << centimos << "')";
    return debug.str();
}

// Representaci�n para guardar
string Monto::toSave() const {
    ostringstream out;
    out << soles << Serialization::DELIMITER_DETAIL << (centimos < 10 ? "0" : "") << centimos;
    return out.str();
}

// Carga los datos desde una cadena
void Monto::load(const string& data) {
    istringstream in(data);
    string solesString, centimosString;

    if (!getline(in, solesString, Serialization::DELIMITER_DETAIL) ||
        !getline(in, centimosString)) {
        throw runtime_error("Error al cargar los datos: datos insuficientes o mal formateados.");
    }

    soles = stoi(solesString);
    centimos = stoi(centimosString);

    // Validaci�n de centimos
    if (centimos < 0 || centimos >= 100) {
        throw runtime_error("Valor de centimos fuera de rango (0-99).");
    }
}

// Genera un monto aleatorio
void Monto::generateRandom() {
    soles = rand() % 101;
    centimos = rand() % 100; // Asegura un rango de 0 a 99
}