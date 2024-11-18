#pragma once

#pragma once

#include "Usuario.h"
#include "SList.h"
#include "Cuenta.h"
#include "MQuejas.h"

class Cliente : public Usuario, IRandomizable, IInteractive
{
private:
	Fecha fechaActual;         // Fecha actual del cuenta

	SList<Cuenta> cuentas;
	MQuejas quejas;

	bool _addCuenta();
	Cuenta _selectCuentaBancaria(size_t index);
	float _totalRecursivoDinero(const SList<Cuenta>& cuentas, SList<Cuenta>::Iterator it);
	Monto _totalDinero();

	void _showDatos();
	void _showCuentas();
	void _showReporte();
	void _interactNuevaCuenta();
	void _interactSeleccionarCuenta();
	void _interactRegistrarQueja();

public:
	Cliente(const Fecha& fechaActual, const Identidad& identidad, const Contacto& contacto);
	Cliente(const Fecha& fechaActual, const string& datos);
	Cliente();

	~Cliente() = default;

	string toDebug() const override;
	string toSave() const override;
	void load(const string& data) override;
	string toShow() const override;
	void generateRandom() override;
	void interact() override;
};

Cliente::Cliente(const Fecha& fechaActual, const Identidad& identidad, const Contacto& contacto)
	: fechaActual(fechaActual), Usuario(identidad, contacto), quejas(fechaActual, TipoUsuario::Cliente)
{}

Cliente::Cliente(const Fecha& fechaActual, const string& datos)
	: fechaActual(fechaActual), quejas(fechaActual, TipoUsuario::Cliente)
{
	auto compare = [](Cuenta a, Cuenta b) {
		return a.getTarjeta().getSaldoFloat() < b.getTarjeta().getSaldoFloat();
		};

	load(datos);
	cuentas.shellSort(compare);
}

Cliente::Cliente()
	: fechaActual(Fecha()), Usuario(Identidad(), Contacto()), quejas(Fecha(), TipoUsuario::Cliente)
{}

string Cliente::toDebug() const {
	ostringstream out;
	out << "Cliente(fechaActual=" << fechaActual.toStringDDMMAAAA()
		<< ", identidad=" << identidad.toDebug()
		<< ", contacto=" << contacto.toDebug() << ")";

	return out.str();
}

string Cliente::toSave() const
{
	ostringstream out;
	out << identidad.getDNI() << Serialization::DELIMITER_MAIN
		<< identidad.toSave() << Serialization::DELIMITER_MAIN
		<< contacto.toSave() << Serialization::DELIMITER_MAIN;

	for (const auto& cuenta : cuentas) {
		out << cuenta.toSave() << Serialization::DELIMITER_MAIN;
	}

	return out.str();
}

void Cliente::load(const string& data)
{
	istringstream in(data);
	string _, identidadStr, contactoStr, cuentaStr;

	// Leer y descartar el primer valor si es necesario
	if (!getline(in, _, Serialization::DELIMITER_MAIN) ||
		!getline(in, identidadStr, Serialization::DELIMITER_MAIN) ||
		!getline(in, contactoStr, Serialization::DELIMITER_MAIN))
	{
		throw runtime_error("Error al cargar los datos básicos (identidad y contacto).");
	}

	// Cargar la identidad y contacto
	identidad.load(identidadStr);
	contacto.load(contactoStr);

	// Leer todas las cuentas y agregar a la lista
	while (getline(in, cuentaStr, Serialization::DELIMITER_MAIN)) {
		Cuenta cb;
		cb.load(cuentaStr);
		cuentas.pushFront(cb);
	}
}

string Cliente::toShow() const
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

	show << "===================================\n";

	return show.str();
}

// Método de generación de datos aleatorios con manejo seguro
void Cliente::generateRandom()
{
	identidad.generateRandom();
	contacto.generateRandom();

	size_t n = rand() % 3 + 1; // Generar de 1 a 3 cuentas

	for (size_t i = 0; i < n; ++i) {
		Cuenta cb;
		cb.generateRandom();
		cout << "Generando cuenta bancaria: " << i + 1 << '\n';
		cout << cb.toDebug() << '\n'; // Verifica si imprime correctamente
		cuentas.pushBack(cb);
		cout << "Cuenta añadida al listado.\n";
	}
}

void Cliente::interact()
{
	int opcion;
	do {
		cout << "=== Menu de Cliente ===\n";
		cout << "1. Mostrar datos\n2. Mostrar cuentas\n3. Mostrar reporte\n4. Añadir nueva cuenta\n";
		cout << "5. Seleccionar cuenta\n6. Registrar queja\n7. Salir\n";
		cout << "Seleccione una opción: ";
		cin >> opcion;

		// Validar la entrada
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "Entrada inválida. Intente nuevamente.\n";
			continue;
		}

		switch (opcion) {
		case 1: _showDatos(); break;
		case 2: _showCuentas(); break;
		case 3: _showReporte(); break;
		case 4: _interactNuevaCuenta(); break;
		case 5: _interactSeleccionarCuenta(); break;
		case 6: _interactRegistrarQueja(); break;
		case 7: cout << "Saliendo del menú.\n"; break;
		default: cout << "Opción inválida. Intente nuevamente.\n";
		}
	} while (opcion != 7);
}


bool Cliente::_addCuenta()
{
	Cuenta nuevaCuenta;
	nuevaCuenta.generateRandom();
	while (nuevaCuenta.getHistorial().empty())
	{
		nuevaCuenta.getHistorial().pop();
	}
	nuevaCuenta.getTarjeta().setSaldo(0);

	cuentas.pushBack(nuevaCuenta);
	auto compare = [](Cuenta a, Cuenta b) {
		return a.getTarjeta().getSaldoFloat() < b.getTarjeta().getSaldoFloat();
		};
	cuentas.shellSort(compare);
	return true;
}

Cuenta Cliente::_selectCuentaBancaria(size_t index)
{
	return cuentas.getAt(index);
}

float Cliente::_totalRecursivoDinero(const SList<Cuenta>& cuentas, SList<Cuenta>::Iterator it)
{
	return (it != cuentas.end()) ? (*it).getTarjeta().getSaldoFloat() + _totalRecursivoDinero(cuentas, ++it) : 0;
}

Monto Cliente::_totalDinero()
{
	return Monto(_totalRecursivoDinero(cuentas, cuentas.begin()));
}

void Cliente::_showDatos()
{
	cout << toShow() << '\n';
}

void Cliente::_showCuentas()
{
	for (const auto& cuenta : cuentas) {
		cout << cuenta.toShow() << endl;
	}
}

void Cliente::_showReporte()
{
	cout << "=== Reporte de Cliente ===\n";
	cout << "Numero de Cuentas: " << cuentas.size() << '\n';
	cout << "Saldo en cada Cuenta: \n";
	for (const auto& cuenta : cuentas) {
		cout << cuenta.getNumeroCuenta() << ": S/." << cuenta.getTarjeta().getSaldoMonto().toString() << '\n';
	}
	cout << "Saldo total: " << _totalDinero().toString() << '\n';
}

void Cliente::_interactNuevaCuenta()
{
	// Confirmar
	cout << "Desea aniadir una nueva cuenta? (S/N): ";
	char opcion;
	cin >> opcion;

	// Validar la entrada
	if (opcion == 'S' || opcion == 's')
	{
		if (_addCuenta())
		{
			cout << "La cuenta ha sido aniadida exitosamente.\n";
		}
		else
		{
			cout << "No se pudo aniadir la cuenta. Intente nuevamente.\n";
		}
	}
	else
	{
		cout << "La cuenta no fue aniadida.\n";
	}
}

void Cliente::_interactSeleccionarCuenta()
{
	if (cuentas.empty()) {
		cout << "No hay cuentas disponibles para seleccionar.\n";
		return;
	}

	cout << "=== Selección de Cuenta Bancaria ===\n";
	size_t index = 0;
	for (const auto& cuenta : cuentas) {
		cout << index << ". Cuenta: " << cuenta.getNumeroCuenta()
			<< " | Saldo: S/." << cuenta.getTarjeta().getSaldoMonto().toString() << '\n';
		++index;
	}

	cout << "Seleccione el índice de la cuenta que desea gestionar (0 - " << cuentas.size() - 1 << "): ";
	size_t seleccion;
	cin >> seleccion;

	if (cin.fail() || seleccion >= cuentas.size()) {
		cin.clear();
		cin.ignore();
		cout << "Índice inválido. No se seleccionó ninguna cuenta.\n";
		return;
	}

	auto cuentaSeleccionada = cuentas.getAt(seleccion);
	cout << "Has seleccionado la cuenta: " << cuentaSeleccionada.getNumeroCuenta() << '\n';
	cout << "Saldo actual: S/." << cuentaSeleccionada.getTarjeta().getSaldoMonto().toString() << '\n';

	cout << "¿Desea gestionar esta cuenta? (S/N): ";
	char opcion;
	cin >> opcion;

	if (opcion == 'S' || opcion == 's') {
		cout << "Iniciando interacción con la cuenta seleccionada...\n";
		cuentaSeleccionada.interact();
	}
	else {
		cout << "No se realizaron operaciones con la cuenta seleccionada.\n";
	}
}


void Cliente::_interactRegistrarQueja()
{
	quejas.loadFromFile();
	quejas.interact();
	quejas.saveToFile();
}