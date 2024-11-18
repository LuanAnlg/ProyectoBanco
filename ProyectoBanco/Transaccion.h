#pragma once


#include "Fecha.h"
#include "Monto.h"
#include "IShowable.h"
#include "IRandomizable.h"

// Enumeración para el tipo de transacción
enum class TipoTransaccion { Deposito, Retiro, Desconocido };

// Clase Transaccion
class Transaccion : public IDebugable, ISavable, IShowable, IRandomizable
{
private:
    TipoTransaccion tipo;             // Tipo de transacción
    Fecha fechaEmision;    // Fecha en que se realizó la transacción
    Monto monto;            // Monto de la transacción


public:
    // Constructores

    // Constructor que establece el monto, fecha de emisión y tipo de transacción
    Transaccion(const float& monto, const Fecha& fechaEmision, const TipoTransaccion& tipo);
    // Constructor que establece el monto como un objeto Monto, fecha de emisión y tipo de transacción
    Transaccion(const Monto& monto, const Fecha& fechaEmision, const TipoTransaccion& tipo);
    // Constructor que inicializa la transacción a partir de una cadena de texto
    Transaccion(const string& datos);
    // Constructor por defecto
    Transaccion();
    // Destructor por defecto
    ~Transaccion() = default;

    // Métodos de acceso

    // Retorna el monto como un float
    float getMontoFloat() const;
    // Retorna el monto como un objeto Monto
    Monto getMontoMonto() const;
    // Retorna la fecha de emisión de la transacción
    Fecha getFechaEmision() const;
    // Retorna el tipo de transacción
    TipoTransaccion getTipo() const;

    // Métodos de modificación

    // Establece el monto a partir de un valor float, devuelve false si es inválido
    bool setMontoFloat(const float& monto);
    // Establece el monto a partir de un objeto Monto, devuelve false si es inválido
    bool setMontoMonto(const Monto& monto);
    // Establece la fecha de emisión de la transacción, devuelve false si es inválida
    bool setFechaEmision(const Fecha& fechaEmision);
    // Establece el tipo de transacción, devuelve false si es inválido
    bool setTipo(const TipoTransaccion& tipo);

    // Métodos de conversión a string

    // Retorna el tipo de transacción como una cadena
    string toStringTipo() const;

    // Método para depuración

    // Retorna una representación detallada de la transacción para propósitos de depuración
    string toDebug() const override;

    // Métodos para guardar y cargar

    // Retorna la transacción en un formato que puede ser guardado
    string toSave() const override;
    // Método para cargar la transacción desde un string
    void load(const string& data) override;

    // Método para mostrar

    // Retorna una representación de la transacción para ser mostrada
    string toShow() const override;

    // Método que genera una transacción aletoria
    void generateRandom() override;
};

// Constructor que recibe el monto como float, fecha de emisión y tipo
Transaccion::Transaccion(const float& monto, const Fecha& fechaEmision, const TipoTransaccion& tipo)
    : monto(Monto(monto)), fechaEmision(fechaEmision), tipo(tipo) {}

// Constructor que recibe el monto como Monto, fecha de emisión y tipo
Transaccion::Transaccion(const Monto& monto, const Fecha& fechaEmision, const TipoTransaccion& tipo)
    : monto(monto), fechaEmision(fechaEmision), tipo(tipo) {}

// Constructor que inicializa la transacción a partir de una cadena de texto
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

// Retorna la fecha de emisión de la transacción
Fecha Transaccion::getFechaEmision() const {
    return fechaEmision;
}

// Retorna el tipo de transacción
TipoTransaccion Transaccion::getTipo() const {
    return tipo;
}

// Establece el monto a partir de un float, con validación
bool Transaccion::setMontoFloat(const float& monto) {
    if (monto < 0) {
        return false;
    }
    this->monto = Monto(monto);
    return true;
}

// Establece el monto a partir de un objeto Monto, con validación
bool Transaccion::setMontoMonto(const Monto& monto) {
    if (monto.getMonto() < 0) {
        return false;
    }
    this->monto = monto;
    return true;
}

// Establece la fecha de emisión
bool Transaccion::setFechaEmision(const Fecha& fecha) {
    this->fechaEmision = fecha;
    return true;
}

// Establece el tipo de transacción con validación
bool Transaccion::setTipo(const TipoTransaccion& tipo) {
    if (tipo == TipoTransaccion::Deposito || tipo == TipoTransaccion::Retiro) {
        this->tipo = tipo;
        return true;
    }
    return false; // Tipo inválido
}

// Retorna el tipo de transacción como cadena
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

// Método de depuración
string Transaccion::toDebug() const {
    ostringstream debug;
    debug << "Transaccion(Tipo=" << toStringTipo()
        << ", FechaEmision='" << fechaEmision.toStringDDMMAAAA()
        << "', Monto='" << monto.toDebug() << "')";
    return debug.str();
}

// Método de guardado
string Transaccion::toSave() const {
    ostringstream out;
    out << toStringTipo() << Serialization::DELIMITER_FIELD
        << fechaEmision.toStringDDMMAAAA() << Serialization::DELIMITER_FIELD
        << monto.toSave();
    return out.str();
}

// Método para cargar los datos desde una cadena
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

// Método para mostrar la transacción
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

// Método para generar una transacción aleatoria
void Transaccion::generateRandom() {
    short option = rand() % 2;
    fechaEmision.generateRandom();
    monto.generateRandom();

    tipo = (option == 0) ? TipoTransaccion::Deposito : TipoTransaccion::Retiro;
}
