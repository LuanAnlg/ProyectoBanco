#pragma once


#include "Fecha.h"
#include "Monto.h"
#include "IShowable.h"
#include "IRandomizable.h"

// Enumeraci�n para el tipo de transacci�n
enum class TipoTransaccion { Deposito, Retiro, Desconocido };

// Clase Transaccion
class Transaccion : public IDebugable, ISavable, IShowable, IRandomizable
{
private:
    TipoTransaccion tipo;             // Tipo de transacci�n
    Fecha fechaEmision;    // Fecha en que se realiz� la transacci�n
    Monto monto;            // Monto de la transacci�n


public:
    // Constructores

    // Constructor que establece el monto, fecha de emisi�n y tipo de transacci�n
    Transaccion(const float& monto, const Fecha& fechaEmision, const TipoTransaccion& tipo);
    // Constructor que establece el monto como un objeto Monto, fecha de emisi�n y tipo de transacci�n
    Transaccion(const Monto& monto, const Fecha& fechaEmision, const TipoTransaccion& tipo);
    // Constructor que inicializa la transacci�n a partir de una cadena de texto
    Transaccion(const string& datos);
    // Constructor por defecto
    Transaccion();
    // Destructor por defecto
    ~Transaccion() = default;

    // M�todos de acceso

    // Retorna el monto como un float
    float getMontoFloat() const;
    // Retorna el monto como un objeto Monto
    Monto getMontoMonto() const;
    // Retorna la fecha de emisi�n de la transacci�n
    Fecha getFechaEmision() const;
    // Retorna el tipo de transacci�n
    TipoTransaccion getTipo() const;

    // M�todos de modificaci�n

    // Establece el monto a partir de un valor float, devuelve false si es inv�lido
    bool setMontoFloat(const float& monto);
    // Establece el monto a partir de un objeto Monto, devuelve false si es inv�lido
    bool setMontoMonto(const Monto& monto);
    // Establece la fecha de emisi�n de la transacci�n, devuelve false si es inv�lida
    bool setFechaEmision(const Fecha& fechaEmision);
    // Establece el tipo de transacci�n, devuelve false si es inv�lido
    bool setTipo(const TipoTransaccion& tipo);

    // M�todos de conversi�n a string

    // Retorna el tipo de transacci�n como una cadena
    string toStringTipo() const;

    // M�todo para depuraci�n

    // Retorna una representaci�n detallada de la transacci�n para prop�sitos de depuraci�n
    string toDebug() const override;

    // M�todos para guardar y cargar

    // Retorna la transacci�n en un formato que puede ser guardado
    string toSave() const override;
    // M�todo para cargar la transacci�n desde un string
    void load(const string& data) override;

    // M�todo para mostrar

    // Retorna una representaci�n de la transacci�n para ser mostrada
    string toShow() const override;

    // M�todo que genera una transacci�n aletoria
    void generateRandom() override;
};

// Constructor que recibe el monto como float, fecha de emisi�n y tipo
Transaccion::Transaccion(const float& monto, const Fecha& fechaEmision, const TipoTransaccion& tipo)
    : monto(Monto(monto)), fechaEmision(fechaEmision), tipo(tipo) {}

// Constructor que recibe el monto como Monto, fecha de emisi�n y tipo
Transaccion::Transaccion(const Monto& monto, const Fecha& fechaEmision, const TipoTransaccion& tipo)
    : monto(monto), fechaEmision(fechaEmision), tipo(tipo) {}

// Constructor que inicializa la transacci�n a partir de una cadena de texto
Transaccion::Transaccion(const string& datos) {
    load(datos);
}

// Constructor por defecto
Transaccion::Transaccion() : monto(0), fechaEmision(Fecha()), tipo(TipoTransaccion::Desconocido) {}

// Retorna el monto total como un float
float Transaccion::getMontoFloat() const {
    return monto.getMonto();
}

// Retorna el monto como un objeto Monto
Monto Transaccion::getMontoMonto() const {
    return monto;
}

// Retorna la fecha de emisi�n de la transacci�n
Fecha Transaccion::getFechaEmision() const {
    return fechaEmision;
}

// Retorna el tipo de transacci�n
TipoTransaccion Transaccion::getTipo() const {
    return tipo;
}

// Establece el monto a partir de un float, con validaci�n
bool Transaccion::setMontoFloat(const float& monto) {
    if (monto < 0) {
        return false;
    }
    this->monto = Monto(monto);
    return true;
}

// Establece el monto a partir de un objeto Monto, con validaci�n
bool Transaccion::setMontoMonto(const Monto& monto) {
    if (monto.getMonto() < 0) {
        return false;
    }
    this->monto = monto;
    return true;
}

// Establece la fecha de emisi�n
bool Transaccion::setFechaEmision(const Fecha& fecha) {
    this->fechaEmision = fecha;
    return true;
}

// Establece el tipo de transacci�n con validaci�n
bool Transaccion::setTipo(const TipoTransaccion& tipo) {
    if (tipo == TipoTransaccion::Deposito || tipo == TipoTransaccion::Retiro) {
        this->tipo = tipo;
        return true;
    }
    return false; // Tipo inv�lido
}

// Retorna el tipo de transacci�n como cadena
string Transaccion::toStringTipo() const {
    switch (tipo) {
    case TipoTransaccion::Deposito:
        return "Deposito";
    case TipoTransaccion::Retiro:
        return "Retiro";
    default:
        return "Desconocido";
    }
}

// M�todo de depuraci�n
string Transaccion::toDebug() const {
    ostringstream debug;
    debug << "Transaccion(Tipo=" << toStringTipo()
        << ", FechaEmision='" << fechaEmision.toStringDDMMAAAA()
        << "', Monto='" << monto.toDebug() << "')";
    return debug.str();
}

// M�todo de guardado
string Transaccion::toSave() const {
    ostringstream out;
    out << toStringTipo() << Serialization::DELIMITER_FIELD
        << fechaEmision.toStringDDMMAAAA() << Serialization::DELIMITER_FIELD
        << monto.toSave();
    return out.str();
}

// M�todo para cargar los datos desde una cadena
void Transaccion::load(const string& data) {
    istringstream in(data);
    string tipoString, fechaString, montoString;

    if (!getline(in, tipoString, Serialization::DELIMITER_FIELD) ||
        !getline(in, fechaString, Serialization::DELIMITER_FIELD) ||
        !getline(in, montoString)) {
        throw runtime_error("Error al cargar los datos: datos insuficientes o mal formateados.");
    }

    fechaEmision = Fecha(fechaString);
    monto = Monto(montoString);

    if (!setMontoMonto(monto)) {
        throw runtime_error("Error al asignar monto");
    }

    if (tipoString == "Deposito") {
        tipo = TipoTransaccion::Deposito;
    }
    else if (tipoString == "Retiro") {
        tipo = TipoTransaccion::Retiro;
    }
    else {
        tipo = TipoTransaccion::Desconocido;
    }
}

// M�todo para mostrar la transacci�n
string Transaccion::toShow() const {
    ostringstream show;
    show << "\n/-------------------------\n"
        << "| " << toStringTipo() << "\n"
        << "|-------------------------\n"
        << "| Fecha de Emision: " << fechaEmision.toStringDDMMAAAA() << "\n"
        << "| Monto: S/" << monto.toString() << '\n'
        << "\\-------------------------";
    return show.str();
}

// M�todo para generar una transacci�n aleatoria
void Transaccion::generateRandom() {
    short option = rand() % 2;
    fechaEmision.generateRandom();
    monto.generateRandom();

    tipo = (option == 0) ? TipoTransaccion::Deposito : TipoTransaccion::Retiro;
}
