#pragma once

#include "Usuario.h"
#include "Tarjeta.h"
#include "SQueue.h"
#include "Transaccion.h"
#include "MQuejas.h"
#include "IRandomizable.h"
#include "AVLTree.h"
#include "IInteractive.h"

class UCliente : public Usuario, IRandomizable, IInteractive
{
private:
	Fecha fechaActual;              // Fecha actual en la cuenta

	Tarjeta tarjeta;    // Tarjeta de débito asociada
	SQueue<Transaccion> historial;  // Historial de transacciones (ahora con punteros)
	MQuejas quejas;

public:
	UCliente();
	UCliente(const Fecha& fechaActual, const Identidad& identidad, const Contacto& contacto);
	UCliente(const Fecha& fechaActual, const string& datos);
	~UCliente();

	bool _addDeposito(const Fecha& fecha, const float& monto);
	bool _addRetiro(const Fecha& fecha, const float& monto);
	float _totalRecursivoDepositos(const SQueue<Transaccion>& depositos, SQueue<Transaccion>::Iterator it) const;
	float _totalRecursivoRetiros(const SQueue<Transaccion>& retiros, SQueue<Transaccion>::Iterator it) const;
	Monto _totalDepositos(size_t& numeroDepositos) const;
	Monto _totalRetiros(size_t& numeroRetiros) const;


	void _showDatos() const;
	void _showHistorial() const;
	void _showReporte() const;

	void _interactDepositar();
	void _interactRetirar();
	void _interactRegistrarQueja();

	string toShow() const override;
	string toSave() const override;
	void load(const string& datos) override;
	void generateRandom() override;
	void interact() override;
};

UCliente::UCliente()
	: fechaActual(Fecha()), tarjeta(Tarjeta()), historial(SQueue<Transaccion>()),
	quejas(MQuejas(fechaActual, TipoUsuario::Cliente)),
	Usuario(Identidad(), Contacto())
{}

UCliente::UCliente(const Fecha& fechaActual, const Identidad& identidad, const Contacto& contacto)
	: historial(SQueue<Transaccion>()), quejas(MQuejas(fechaActual, TipoUsuario::Cliente)), Usuario(Identidad(), Contacto())
{
	tarjeta.generateRandom();
	tarjeta.setSaldo(0);
}

UCliente::UCliente(const Fecha& fechaActual, const string& datos) : fechaActual(fechaActual),
historial(SQueue<Transaccion>()), quejas(MQuejas(fechaActual, TipoUsuario::Cliente))
{
	load(datos);
}

UCliente::~UCliente()
{
}

bool UCliente::_addDeposito(const Fecha& fecha, const float& monto)
{
	if (monto <= 0) return false;
	historial.push(Transaccion(monto, fecha, TipoTransaccion::Deposito));
	tarjeta.depositar(monto);
	return true;
}

bool UCliente::_addRetiro(const Fecha& fecha, const float& monto)
{
	if (monto <= 0 || monto > tarjeta.getSaldoFloat()) return false;
	historial.push(Transaccion(monto, fecha, TipoTransaccion::Retiro));
	tarjeta.retirar(monto);
	return true;
}

float UCliente::_totalRecursivoDepositos(const SQueue<Transaccion>& depositos, SQueue<Transaccion>::Iterator it) const {
	return (it != depositos.end()) ? (*it).getMontoFloat() + _totalRecursivoDepositos(depositos, ++it) : 0;
}

float UCliente::_totalRecursivoRetiros(const SQueue<Transaccion>& retiros, SQueue<Transaccion>::Iterator it) const {
	return (it != retiros.end()) ? (*it).getMontoFloat() + _totalRecursivoRetiros(retiros, ++it) : 0;
}

Monto UCliente::_totalDepositos(size_t& numeroDepositos) const {
	auto depositos = historial.filter([](const Transaccion& t) { return t.getTipo() == TipoTransaccion::Deposito; });
	numeroDepositos = depositos.size();
	return Monto(_totalRecursivoDepositos(depositos, depositos.begin()));
}

Monto UCliente::_totalRetiros(size_t& numeroRetiros) const {
	auto retiros = historial.filter([](const Transaccion& t) { return t.getTipo() == TipoTransaccion::Retiro; });
	numeroRetiros = retiros.size();
	return Monto(_totalRecursivoRetiros(retiros, retiros.begin()));
}


void UCliente::_showDatos() const
{
	cout << toShow() << endl;
}

void UCliente::_showHistorial() const
{
	for (auto &transaccion : historial) {
		cout << transaccion.toShow() << endl;
	}
}

void UCliente::_showReporte() const {
	size_t numeroDepositos, numeroRetiros;
	cout << "=== Reporte de Cuenta ===\n";
	cout << "Total Depositos: " << _totalDepositos(numeroDepositos).toString() << '\n';
	cout << "Total Retiros: " << _totalRetiros(numeroRetiros).toString() << '\n';
	cout << "Numero Depositos: " << numeroDepositos << '\n';
	cout << "Numero Retiros: " << numeroRetiros << '\n';
	cout << "Saldo Actual: " << tarjeta.getSaldoMonto().toString() << '\n';
}

void UCliente::_interactDepositar() {
	float monto;
	cout << "Ingrese monto a depositar: ";
	cin >> monto;
	if (_addDeposito(fechaActual, monto))
		cout << "Deposito exitoso.\n";
	else
		cout << "Deposito fallido.\n";
}

void UCliente::_interactRetirar() {
	float monto;
	cout << "Ingrese monto a retirar: ";
	cin >> monto;
	if (_addRetiro(fechaActual, monto))
		cout << "Retiro exitoso.\n";
	else
		cout << "Retiro fallido.\n";
}

void UCliente::_interactRegistrarQueja()
{
	quejas.loadFromFile();
	quejas.interact();
	quejas.saveToFile();
}

string UCliente::toShow() const
{
	ostringstream show;

	show << "===================================\n";
	show << "           Detalles del Cliente    \n";
	show << "===================================\n";

	show << "\n--- Identidad ---\n";
	show << "DNI: " << (identidad.getDNI().empty() ? "No especificado" : identidad.getDNI()) << '\n';
	show << "Primer Apellido: " << (identidad.getPrimerApellido().empty() ? "No especificado" : identidad.getPrimerApellido()) << '\n';
	show << "Segundo Apellido: " << (identidad.getSegundoApellido().empty() ? "No especificado" : identidad.getSegundoApellido()) << '\n';
	show << "Nombre(s): " << (identidad.getNombres().empty() ? "No especificado" : identidad.getNombres()) << '\n';
	show << "Sexo: " << identidad.toStringSexo() << '\n';
	show << "Estado Civil: " << identidad.toStringEstadoCivil() << '\n';

	show << "\n--- Contacto ---\n";
	show << "Teléfono: " << (contacto.getTelefono().empty() ? "No especificado" : contacto.getTelefono()) << '\n';
	show << "Correo Electrónico: " << (contacto.getCorreoElectronico().empty() ? "No especificado" : contacto.getCorreoElectronico()) << '\n';
	show << "Departamento: " << (contacto.getDepartamento().empty() ? "No especificado" : contacto.getDepartamento()) << '\n';
	show << "Provincia: " << (contacto.getProvincia().empty() ? "No especificado" : contacto.getProvincia()) << '\n';
	show << "Distrito: " << (contacto.getDistrito().empty() ? "No especificado" : contacto.getDistrito()) << '\n';
	show << "Dirección: " << (contacto.getDireccion().empty() ? "No especificado" : contacto.getDireccion()) << '\n';

	show << "\n--- Tarjeta ---\n";
	show << tarjeta.toShow();

	show << "\n\n===================================\n";

	return show.str();
}

string UCliente::toSave() const
{
	ostringstream out;
	out << identidad.getDNI() << Serialization::DELIMITER_MAIN
		<< identidad.toSave() << Serialization::DELIMITER_MAIN
		<< contacto.toSave() << Serialization::DELIMITER_MAIN
		<< tarjeta.toSave() << Serialization::DELIMITER_MAIN;

	for (const auto& trasaccion : historial) {
		out << trasaccion.toSave() << Serialization::DELIMITER_MAIN;
	}

	return out.str();
}

void UCliente::load(const string& datos) {
	istringstream in(datos); // Flujo para leer los datos
	string _, identidadStr, contactoStr, tarjetaStr, transaccionStr;
	getline(in, _, Serialization::DELIMITER_MAIN);
	// Leer y cargar los datos básicos
	if (!getline(in, identidadStr, Serialization::DELIMITER_MAIN) ||
		!getline(in, contactoStr, Serialization::DELIMITER_MAIN) ||
		!getline(in, tarjetaStr, Serialization::DELIMITER_MAIN)) {
		throw runtime_error("Error al cargar los datos básicos: datos insuficientes o mal formateados.");
	}

	// Cargar identidad, contacto y tarjeta desde las cadenas leídas
	identidad.load(identidadStr);
	contacto.load(contactoStr);
	tarjeta.load(tarjetaStr);

	// Leer las transacciones del historial
	while (getline(in, transaccionStr, Serialization::DELIMITER_MAIN)) {
		Transaccion nuevaTransaccion; // Crear una nueva transacción
		nuevaTransaccion.load(transaccionStr);            // Cargar los datos de la transacción
		historial.push(nuevaTransaccion);                 // Agregar al historial
	}
}

void UCliente::generateRandom()
{
	identidad.generateRandom();
	contacto.generateRandom();
	tarjeta.generateRandom();

	size_t n = rand() % 3 + 1; // Generar de 1 a 3 cuentas

	// Limpiar historial
	historial.clear();

	// Definir el comparador para ordenar las transacciones por fecha
	auto compare = [](Transaccion a, Transaccion b) {
		return a.getFechaEmision().toStringAAAAMMDD() > b.getFechaEmision().toStringAAAAMMDD();
		};

	// Usar un árbol AVL para almacenar las transacciones ordenadas por fecha
	AVLTree<Transaccion> historialTree(compare);

	// Generar entre 1 y 10 transacciones aleatorias
	size_t num = 1 + rand() % 10;
	for (size_t i = 0; i < num; ++i) {
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

void UCliente::interact()
{
	int opcion;
	do {
		cout << "=== Menu de Cliente ===\n"
			<< "1. Mostrar datos\n"
			<< "2. Mostrar historial\n"
			<< "3. Mostrar reporte\n"
			<< "4. Depositar\n"
			<< "5. Retirar\n"
			<< "6. Registrar queja\n"
			<< "7. Salir\n"
			<< "Seleccione una opción: ";
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
		case 6: _interactRegistrarQueja(); break;
		case 7: cout << "Saliendo del menú.\n"; break;
		default: cout << "Opción inválida. Intente nuevamente.\n";
		}
	} while (opcion != 7);
}
