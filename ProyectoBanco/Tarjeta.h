#pragma once

#include "Fecha.h"
#include "Monto.h"
#include "IRandomizable.h"
#include "IShowable.h"

class Tarjeta : public IDebugable, ISavable, IShowable, IRandomizable
{
public:
    enum class EstadoTarjeta { Activa, Inactiva, Bloqueada, Desconocido };

protected:
    string numero;            // Número de la tarjeta
    Fecha fechaVencimiento;   // Fecha de vencimiento de la tarjeta
    string cvv;               // Código de verificación de la tarjeta
    EstadoTarjeta estado;     // Estado de la tarjeta
    Monto saldo;              // Saldo de la tarjeta

public:
    // Constructores
    Tarjeta(const string& numero, const Fecha& fechaVencimiento,
        const string& cvv, const EstadoTarjeta& estado, const float& saldo);
    Tarjeta(const string& datos);  // Constructor que carga los datos desde una cadena
    Tarjeta();                     // Constructor por defecto

    // Destructor
    virtual ~Tarjeta() = default;

    // Métodos de acceso
    string getNumero() const;
    Fecha getFechaVencimiento() const;
    string getCVV() const;
    EstadoTarjeta getEstado() const;
    float getSaldoFloat() const;
    Monto getSaldoMonto() const;

    // Métodos de modificación
    bool setNumero(const string& numero);
    bool setFechaVencimiento(const Fecha& fecha);
    bool setCVV(const string& cvv);
    bool setEstado(const EstadoTarjeta& estado);
    bool setSaldo(const float& saldo);

    // Métodos de cambio de estado
    bool activar();
    bool inactivar();
    bool bloquear();

    // Métodos de representación
    string toStringEstado() const;
    virtual string toDebug() const override;
    string toSave() const override;
    void load(const string& data) override;
    virtual string toShow() const override;

    // Método para generar una tarjeta aleatoria
    void generateRandom() override;

    // Métodos específicos de la tarjeta de débito
    bool depositar(float monto);
    bool retirar(float monto);
};

// Constructor con parámetros
Tarjeta::Tarjeta(const string& numero, const Fecha& fechaVencimiento,
    const string& cvv, const EstadoTarjeta& estado, const float& saldo)
    : numero(numero), fechaVencimiento(fechaVencimiento), cvv(cvv),
    estado(estado), saldo(Monto(saldo))
{}

// Constructor por defecto
Tarjeta::Tarjeta()
    : numero(""), fechaVencimiento(Fecha()), cvv(""), estado(EstadoTarjeta::Desconocido)
{}

// Constructor que recibe una cadena
Tarjeta::Tarjeta(const string& datos)
{
    load(datos);
}

// Getters
string Tarjeta::getNumero() const {
    return numero;
}

Fecha Tarjeta::getFechaVencimiento() const {
    return fechaVencimiento;
}

string Tarjeta::getCVV() const {
    return cvv;
}

Tarjeta::EstadoTarjeta Tarjeta::getEstado() const
{
    return estado;
}

float Tarjeta::getSaldoFloat() const
{
    return saldo.getMonto();
}

Monto Tarjeta::getSaldoMonto() const
{
    return saldo;
}

// Setters
bool Tarjeta::setNumero(const string& numero)
{
    if (numero.size() != 16)
    {
        return false;
    }
    for (char c : numero)
    {
        if (c < '0' || c > '9')
        {
            return false;
        }
    }
    this->numero = numero;
    return true; // Retorna falso si el número no es válido
}

bool Tarjeta::setFechaVencimiento(const Fecha& fecha)
{
    this->fechaVencimiento = fecha;
    return true;
}

bool Tarjeta::setCVV(const string& cvv) {
    if (cvv.size() != 3)
    {
        return false;
    }
    for (char c : cvv)
    {
        if (c < '0' || c > '9')
        {
            return false;
        }
    }
    this->cvv = cvv;
    return true; // Retorna falso si el CVV no es válido
}

bool Tarjeta::setEstado(const EstadoTarjeta& estado) {
    if (estado != EstadoTarjeta::Activa && estado != EstadoTarjeta::Inactiva &&
        estado != EstadoTarjeta::Bloqueada) {
        return false;
    }
    this->estado = estado;
    return true; // Retorna falso si el estado no es válido
}

bool Tarjeta::setSaldo(const float& saldo)
{
    return this->saldo.setMonto(saldo);
}

bool Tarjeta::activar()
{
    estado = EstadoTarjeta::Activa;
    return true;
}

bool Tarjeta::inactivar()
{
    estado = EstadoTarjeta::Inactiva;
    return true;
}

bool Tarjeta::bloquear()
{
    estado = EstadoTarjeta::Bloqueada;
    return true;
}

// Retorna una representación en cadena del estado
string Tarjeta::toStringEstado() const
{
    switch (estado) {
    case EstadoTarjeta::Activa: return "Activa";
    case EstadoTarjeta::Inactiva: return "Inactiva";
    case EstadoTarjeta::Bloqueada: return "Bloqueada";
    }
    return "Desconocido";
}

// Muestra la información de la tarjeta en un formato simple
string Tarjeta::toDebug() const {
    ostringstream debug;
    debug << "Tarjeta(numero='" << numero
        << "', fechaVencimiento='" << fechaVencimiento.toDebug()
        << "', cvv='" << cvv
        << "', estado='" << toStringEstado() << "')";
    return debug.str();
}

// Método para guardar la información de la tarjeta
string Tarjeta::toSave() const {
    ostringstream out;
    out << numero << Serialization::DELIMITER_FIELD
        << fechaVencimiento.toStringDDMMAAAA() << Serialization::DELIMITER_FIELD
        << cvv << Serialization::DELIMITER_FIELD
        << toStringEstado() << Serialization::DELIMITER_FIELD
        << saldo.toSave();
    return out.str();
}

void Tarjeta::load(const string& data)
{
    istringstream in(data);
    string fechaString;
    string estadoString;

    if (!getline(in, numero, Serialization::DELIMITER_FIELD) ||
        !getline(in, fechaString, Serialization::DELIMITER_FIELD) ||
        !getline(in, cvv, Serialization::DELIMITER_FIELD) ||
        !getline(in, estadoString, Serialization::DELIMITER_FIELD))
    {
        throw runtime_error("Error al cargar los datos: datos insuficientes o mal formateados.");
    }

    if (!setNumero(numero) || !setCVV(cvv))
    {
        throw runtime_error("Datos de tarjeta inválidos");
    }

    fechaVencimiento = Fecha(fechaString);

    // Asignación del estado basado en el valor de estadoString
    if (estadoString == "Activa") {
        estado = EstadoTarjeta::Activa;
    }
    else if (estadoString == "Inactiva") {
        estado = EstadoTarjeta::Inactiva;
    }
    else if (estadoString == "Bloqueada") {
        estado = EstadoTarjeta::Bloqueada;
    }
    else {
        estado = EstadoTarjeta::Desconocido;
    }
}

string Tarjeta::toShow() const
{
    ostringstream show;
    show << "\n";
    show << "/-------------------------\n";
    show << "| Tarjeta                \n";
    show << "|-------------------------\n";
    show << "| Número: " << numero << "\n";
    show << "| Vencimiento: " << fechaVencimiento.toStringMMAA() << "\n";
    show << "| Estado: " << toStringEstado() << "\n";
    show << "\\-------------------------";
    return show.str();
}

void Tarjeta::generateRandom()
{
    ostringstream numTarjeta;
    // Generar número de tarjeta (16 dígitos en grupos de 4)
    for (int i = 0; i < 16; i++) {
        numTarjeta << rand() % 10;
    }

    // CVV (3 dígitos)
    ostringstream cvvTarjeta;
    for (int i = 0; i < 3; i++) {
        cvvTarjeta << rand() % 10;
    }

    Fecha fecha;
    fecha.generateRandom();
    fecha.setAnio(2024 + (rand() % 4 + 2));

    float saldoTarjeta(rand() % 10000);

    setNumero(numTarjeta.str());
    setCVV(cvvTarjeta.str());
    setFechaVencimiento(fecha);
    setEstado(Tarjeta::EstadoTarjeta::Activa);
    setSaldo(saldoTarjeta);
}

// Métodos específicos de la tarjeta de débito
bool Tarjeta::depositar(float monto)
{
    if (estado != EstadoTarjeta::Activa || monto <= 0)
    {
        return false;
    }
    saldo.setMonto(saldo.getMonto() + monto);
    return true;
}

bool Tarjeta::retirar(float monto)
{
    if (estado != EstadoTarjeta::Activa || monto <= 0 || saldo.getMonto() < monto)
    {
        return false;
    }
    saldo.setMonto(saldo.getMonto() - monto);
    return true;
}
