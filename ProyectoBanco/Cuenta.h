#pragma once

#include "IInteractive.h"
#include "SQueue.h"
#include "AVLTree.h"
#include "Tarjeta.h"
#include "Transaccion.h"

class Cuenta : public IDebugable, ISavable, IShowable, IRandomizable, IInteractive
{
private:
    Fecha fechaActual;              // Fecha actual en la cuenta
    string numeroCuenta;            // Número de la cuenta bancaria
    Tarjeta tarjeta;    // Tarjeta de débito asociada
    SQueue<Transaccion> historial;  // Historial de transacciones

    // Métodos privados de operaciones
    bool _addDeposito(const Fecha& fecha, const float& monto);
    bool _addRetiro(const Fecha& fecha, const float& monto);
    float _totalRecursivoDepositos(const SQueue<Transaccion>& depositos, SQueue<Transaccion>::Iterator it) const;
    float _totalRecursivoRetiros(const SQueue<Transaccion>& retiros, SQueue<Transaccion>::Iterator it) const;
    Monto _totalDepositos(size_t& numeroDepositos) const;
    Monto _totalRetiros(size_t& numeroRetiros) const;

    // Métodos de visualización privados
    void _showDatos() const;
    void _showHistorial() const;
    void _showReporte() const;

    // Métodos de interacción privados
    void _interactDepositar();
    void _interactRetirar();

public:
    // Constructores y destructor
    Cuenta(const Fecha& fechaActual, string& numeroCuenta, const Tarjeta& tarjeta);
    Cuenta(const Fecha& fechaActual, const string& datos);
    Cuenta();
    ~Cuenta() = default;

    // Getters
    Fecha getFechaActual() const;
    string getNumeroCuenta() const;
    Tarjeta getTarjeta() const;
    SQueue<Transaccion> getHistorial() const;

    // Setters
    bool setFechaActual(const Fecha& fecha);
    bool setNumeroCuenta(const string& numeroCuenta);
    bool setTarjeta(const Tarjeta& Tarjeta);
    bool setHistorial(const SQueue<Transaccion>& historial);

    // Métodos de interfaces
    string toDebug() const override;
    string toSave() const override;
    void load(const string& data) override;
    string toShow() const override;
    void generateRandom() override;
    void interact() override;
};
// Constructores
Cuenta::Cuenta(const Fecha& fechaActual, string& numeroCuenta, const Tarjeta& tarjeta)
    : fechaActual(fechaActual), numeroCuenta(numeroCuenta), tarjeta(tarjeta) {}

Cuenta::Cuenta(const Fecha& fechaActual, const string& datos) : fechaActual(fechaActual) {
    load(datos);
}

Cuenta::Cuenta()
    : numeroCuenta(""), tarjeta(Tarjeta()), fechaActual(Fecha()) {}

// Getters
Fecha Cuenta::getFechaActual() const {
    return fechaActual;
}

string Cuenta::getNumeroCuenta() const {
    return numeroCuenta;
}

Tarjeta Cuenta::getTarjeta() const {
    return tarjeta;
}

SQueue<Transaccion> Cuenta::getHistorial() const {
    return historial;
}

// Setters
bool Cuenta::setFechaActual(const Fecha& fecha) {
    this->fechaActual = fecha;
    return true;
}

bool Cuenta::setNumeroCuenta(const string& numeroCuenta) {
    if (numeroCuenta.size() != 12) {
        return false;
    }
    for (char c : numeroCuenta) {
        if (c < '0' || c > '9') return false; // Solo dígitos permitidos
    }
    this->numeroCuenta = numeroCuenta;
    return true;
}

bool Cuenta::setTarjeta(const Tarjeta& Tarjeta) {
    this->tarjeta = Tarjeta;
    return true;
}

bool Cuenta::setHistorial(const SQueue<Transaccion>& historial) {
    this->historial = historial;
    return true;
}

// Métodos de operaciones
bool Cuenta::_addDeposito(const Fecha& fecha, const float& monto) {
    if (monto <= 0) return false;
    historial.push(Transaccion(monto, fecha, TipoTransaccion::Deposito));
    tarjeta.depositar(monto);
    return true;
}

bool Cuenta::_addRetiro(const Fecha& fecha, const float& monto) {
    if (monto <= 0 || monto > tarjeta.getSaldoFloat()) return false;
    historial.push(Transaccion(monto, fecha, TipoTransaccion::Retiro));
    tarjeta.retirar(monto);
    return true;
}

float Cuenta::_totalRecursivoDepositos(const SQueue<Transaccion>& depositos, SQueue<Transaccion>::Iterator it) const {
    return (it != depositos.end()) ? (*it).getMontoFloat() + _totalRecursivoDepositos(depositos, ++it) : 0;
}

float Cuenta::_totalRecursivoRetiros(const SQueue<Transaccion>& retiros, SQueue<Transaccion>::Iterator it) const {
    return (it != retiros.end()) ? (*it).getMontoFloat() + _totalRecursivoRetiros(retiros, ++it) : 0;
}

Monto Cuenta::_totalDepositos(size_t& numeroDepositos) const {
    auto depositos = historial.filter([](const Transaccion& t) { return t.getTipo() == TipoTransaccion::Deposito; });
    numeroDepositos = depositos.size();
    return Monto(_totalRecursivoDepositos(depositos, depositos.begin()));
}

Monto Cuenta::_totalRetiros(size_t& numeroRetiros) const {
    auto retiros = historial.filter([](const Transaccion& t) { return t.getTipo() == TipoTransaccion::Retiro; });
    numeroRetiros = retiros.size();
    return Monto(_totalRecursivoRetiros(retiros, retiros.begin()));
}

// Visualización
void Cuenta::_showDatos() const {
    cout << toShow();
}

void Cuenta::_showHistorial() const {
    for (Transaccion transaccion : historial) {
        cout << transaccion.toShow() << endl;
    }
}

void Cuenta::_showReporte() const {
    size_t numeroDepositos, numeroRetiros;
    cout << "=== Reporte de Cuenta ===\n";
    cout << "Total Depositos: " << _totalDepositos(numeroDepositos).toString() << '\n';
    cout << "Total Retiros: " << _totalRetiros(numeroRetiros).toString() << '\n';
    cout << "Numero Depositos: " << numeroDepositos << '\n';
    cout << "Numero Retiros: " << numeroRetiros << '\n';
    cout << "Saldo Actual: " << tarjeta.getSaldoMonto().toString() << '\n';
}

// Interacción
void Cuenta::_interactDepositar() {
    float monto;
    cout << "Ingrese monto a depositar: ";
    cin >> monto;
    if (_addDeposito(fechaActual, monto))
        cout << "Deposito exitoso.\n";
    else
        cout << "Deposito fallido.\n";
}

void Cuenta::_interactRetirar() {
    float monto;
    cout << "Ingrese monto a retirar: ";
    cin >> monto;
    if (_addRetiro(fechaActual, monto))
        cout << "Retiro exitoso.\n";
    else
        cout << "Retiro fallido.\n";
}

// Interfaces
string Cuenta::toDebug() const {
    ostringstream out;
    out << "CuentaBancaria(numCuenta=" << numeroCuenta
        << ", fechaActual=" << fechaActual.toStringDDMMAAAA()
        << ", saldo=" << tarjeta.getSaldoMonto().toDebug() << ")";
    //    << ", historial=";

    //// Recorremos el historial con un bucle simplificado
    //for (const auto& transaccion : historial) {
    //    out << transaccion.toDebug() << ", ";
    //    cout << transaccion.toDebug();
    //}

    //// Eliminar la última coma si el historial no está vacío
    //string outStr = out.str();
    //if (!historial.empty()) {
    //    outStr.pop_back();
    //    outStr.pop_back();
    //}
    //outStr += ')';
    return out.str();
}

string Cuenta::toSave() const {
    ostringstream out;
    out << numeroCuenta << Serialization::DELIMITER_SECTION << tarjeta.toSave() << Serialization::DELIMITER_SECTION;
    for (Transaccion transaccion : historial) {
        out << transaccion.toSave() << Serialization::DELIMITER_SECTION;
    }
    return out.str();
}

void Cuenta::load(const string& data) {
    istringstream in(data);
    string cuentaStr, tarjetaData, transaccionData;

    if (!getline(in, cuentaStr, Serialization::DELIMITER_SECTION) ||
        !getline(in, tarjetaData, Serialization::DELIMITER_SECTION)) {
        throw runtime_error("Datos incompletos para cargar la cuenta bancaria.");
    }

    numeroCuenta = cuentaStr;
    tarjeta.load(tarjetaData);

    while (getline(in, transaccionData, Serialization::DELIMITER_SECTION)) {
        Transaccion t;
        t.load(transaccionData);
        historial.push(t);
    }
}

string Cuenta::toShow() const {
    ostringstream out;
    out << "Cuenta N°: " << numeroCuenta << "\nSaldo: " << tarjeta.getSaldoMonto().toString() << "\n";
    return out.str();
}

void Cuenta::generateRandom() {
    // Generar número de cuenta aleatorio de 12 dígitos
    numeroCuenta.clear();
    for (int i = 0; i < 12; ++i) {
        numeroCuenta += '0' + (rand() % 10);
    }

    // Generar datos aleatorios para la tarjeta de débito
    tarjeta.generateRandom();

    // Limpiar historial
    historial.clear();

    // Definir el comparador para ordenar las transacciones por fecha
    auto compare = [](Transaccion a, Transaccion b) {
        return a.getFechaEmision().toStringAAAAMMDD() > b.getFechaEmision().toStringAAAAMMDD();
        };

    // Usar un árbol AVL para almacenar las transacciones ordenadas por fecha
    AVLTree<Transaccion> historialTree(compare);

    // Generar entre 1 y 10 transacciones aleatorias
    size_t n = 1 + rand() % 10;
    for (size_t i = 0; i < n; ++i) {
        Transaccion t;
        t.generateRandom();
        historialTree.insert(t); // Insertar en el árbol AVL
    }

    // Transferir las transacciones ordenadas desde el árbol AVL al historial (deque o lista)
    while (!historialTree.empty()) {
        historial.push(historialTree.getBack());  // Obtener el último elemento (más antiguo)
        historialTree.popBack();                  // Eliminar el último elemento del árbol
    }
}

void Cuenta::interact() {
    int opcion;
    do {
        cout << "=== Menu de Cuenta ===\n";
        cout << "1. Mostrar datos\n2. Mostrar historial\n3. Mostrar reporte\n4. Depositar\n5. Retirar\n6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Entrada inválida. Intente nuevamente.\n";
            continue;
        }

        switch (opcion) {
        case 1: _showDatos(); break;
        case 2: _showHistorial(); break;
        case 3: _showReporte(); break;
        case 4: _interactDepositar(); break;
        case 5: _interactRetirar(); break;
        case 6: cout << "Saliendo del menú.\n"; break;
        default: cout << "Opción inválida. Intente nuevamente.\n";
        }
    } while (opcion != 6);
}

