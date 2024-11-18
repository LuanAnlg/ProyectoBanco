#pragma once

#include "IShowable.h"
#include "Fecha.h"

class Queja : public IDebugable, ISavable, IShowable, IRandomizable
{
private:
	Fecha fechaEmision;
	string cliente;
	string descripcion;

public:
	Queja(const Fecha& fechaEmision, const string& cliente, const string& descripcion);
	Queja(const string& datos);
	Queja();
	~Queja() = default;

	//setters y getters
	Fecha getFecha() const;
	string getCliente() const;
	string getDescripcion() const;

	bool setFechaEmision(const Fecha& fechaEmision);
	bool setCliente(const string& cliente);
	bool setDescripcion(const string& descripcion);


	//metodos
	string toDebug() const override;
	string toSave() const override;
	void load(const string& data) override;
	string toShow() const override;
	void generateRandom() override;
};

Queja::Queja(const Fecha& fechaEmision, const string& cliente, const string& descripcion)
	:fechaEmision(fechaEmision), cliente(cliente), descripcion(descripcion)
{}

Queja::Queja(const string& datos)
{
	load(datos);
}

Queja::Queja()
	: fechaEmision(Fecha()), cliente(""), descripcion("")
{}


Fecha Queja::getFecha() const {
	return fechaEmision;
};
string Queja::getCliente() const {
	return cliente;
};
string Queja::getDescripcion() const {
	return descripcion;
};


bool Queja::setFechaEmision(const Fecha& fecha)
{
	this->fechaEmision = fecha;
	return true;
};

bool Queja::setCliente(const string& cliente) {
	this->cliente = cliente;
	return true;
};

bool Queja::setDescripcion(const string& descripcion) {
	if (descripcion.empty())
	{
		return false;
	}
	this->descripcion = descripcion;
	return true;
}

string Queja::toDebug() const
{
	ostringstream debug;
	debug << "Queja(FechaEmision='" << fechaEmision.toStringDDMMAAAA()
		<< "', Cliente='" << cliente
		<< "', Descripcion='" << descripcion
		<< "')";
	return debug.str();
}

string Queja::toSave() const
{
	ostringstream out; // Para construir el string de salida
	out << fechaEmision.toStringDDMMAAAA() << Serialization::DELIMITER_MAIN
		<< cliente << Serialization::DELIMITER_MAIN
		<< descripcion;
	return out.str(); // Retorna el string generado
}

void Queja::load(const string& data)
{
	istringstream in(data); // Flujo para leer los datos
	string fechaString, sexoString, estadoCivilString;

	// Lee los datos separados por los delimitadores
	if (!getline(in, fechaString, Serialization::DELIMITER_MAIN) ||
		!getline(in, cliente, Serialization::DELIMITER_MAIN) ||
		!getline(in, descripcion))
	{
		throw runtime_error("Error al cargar los datos: datos insuficientes o mal formateados.");
	}

	// Asigna los datos leídos utilizando los setters
	// Asumiendo que `fechaEmision` tiene un setter que recibe un string con la fecha
	fechaEmision = Fecha(fechaString);

	// Si necesitas más lógica de validación o conversión para `cliente` y `descripcion`, añádelo aquí
}

string Queja::toShow() const
{
	ostringstream show;
	show << "\n\n";
	show << "/-------------------------\n";
	show << "| Queja\n";
	show << "|-------------------------\n";
	show << "| Fecha de Emision: " << fechaEmision.toStringDDMMAAAA() << "\n";
	show << "| Cliente: " << cliente << "\n";
	show << "| Descripcion: " << descripcion << "\n";
	show << "\\-------------------------"; // Cierra el formato de salida
	return show.str(); // Retorna la representación legible
}

void Queja::generateRandom()
{
	// Generar fecha aleatoria
	fechaEmision.generateRandom();

	// Arrays de apellidos y nombres
	const string apellidos[] = {
		"Gonzalez", "Perez", "Lopez", "Martinez", "Garcia", "Rodriguez",
		"Hernandez", "Diaz", "Fernandez", "Lima", "Sanchez", "Vasquez",
		"Romero", "Alvarez", "Morales", "Jimenez"
	};

	const string nombres[] = {
		"Juan", "Maria", "Carlos", "Ana", "Luis", "Laura", "Jose", "Carmen",
		"Miguel", "Sofia", "Antonio", "Elena", "Pedro", "Isabel", "David",
		"Patricia", "Raul", "Marta", "Eduardo", "Beatriz"
	};

	// Generar cliente aleatorio (primer apellido, primer nombre)
	cliente = apellidos[rand() % (sizeof(apellidos) / sizeof(apellidos[0]))] + ", " + nombres[rand() % (sizeof(nombres) / sizeof(nombres[0]))];

	// Arrays de queja
	static const string disgustos[] = {
		"Siento disguto", "Estoy decepcionado", "Estoy molesto", "Siento un fastidio", "Estoy insatisfecho"
	};

	static const string temas[] = {
		"el servicio", "la calidad del producto", "la atencion recibida", "el precio", "el tiempo de espera",
		"la facturacion", "la falta de soporte", "la falta de informacion", "el estado del producto", "la entrega"
	};

	static const string compensaciones[] = {
		"una solucion rapida", "una explicacion clara", "que me devuelvan mi dinero", "una compensacion",
		"una disculpa formal", "una respuesta inmediata", "una mejora en el servicio", "que se me trate mejor",
		"que se resuelva mi problema", "que me ofrezcan un descuento"
	};

	// Constantes para el tamaño de los arrays
	const int NUM_DISGUSTOS = sizeof(disgustos) / sizeof(disgustos[0]);
	const int NUM_COSAS = sizeof(temas) / sizeof(temas[0]);
	const int NUM_RAZONES = sizeof(compensaciones) / sizeof(compensaciones[0]);

	// Combinar aleatoriamente las partes para formar una queja
	descripcion = disgustos[rand() % NUM_DISGUSTOS] + " con " + temas[rand() % NUM_COSAS] + " quiero " + compensaciones[rand() % NUM_RAZONES];
}
