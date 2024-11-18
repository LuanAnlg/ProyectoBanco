#pragma once
#include "Identidad.h"
#include "Contacto.h"
#include "IShowable.h"

class Usuario : public IDebugable, public ISavable, public IShowable
{
protected:
    Identidad identidad;   // Informaci�n de identidad del usuario
    Contacto contacto;     // Informaci�n de contacto del usuario

public:
    // Constructores

    // Constructor por defecto
    Usuario();

    // Constructor que inicializa la identidad y contacto del usuario
    Usuario(const Identidad& identidad, const Contacto& contacto);
    // Constructor que carga los datos desde una cadena de datos
    Usuario(const string& datos);
    // Destructor
    ~Usuario();

    // M�todos de acceso

    // Retorna la identidad del usuario
    Identidad getIdentidad() const;
    // Retorna el contacto del usuario
    Contacto getContacto() const;

    // M�todos de modificaci�n

    // Establece la identidad del usuario
    bool setIdentidad(const Identidad& identidad);
    // Establece el contacto del usuario
    bool setContacto(const Contacto& contacto);

    // M�todos de depuraci�n, guardado, carga y visualizaci�n

    // Retorna una representaci�n de depuraci�n del objeto
    virtual string toDebug() const override;
    // Retorna una representaci�n en cadena para guardar los datos del objeto
    virtual string toSave() const override;
    // Carga los datos desde una cadena en formato espec�fico
    virtual void load(const string& data) override;
    // Retorna una representaci�n en cadena para mostrar informaci�n del usuario
    virtual string toShow() const override;
};

Usuario::Usuario() :
    identidad(Identidad()), contacto(Contacto())
{}

// Constructor
Usuario::Usuario(const Identidad& identidad, const Contacto& contacto)
    : identidad(identidad), contacto(contacto) {}

Usuario::Usuario(const string& datos)
{
    load(datos); // Carga datos desde el string proporcionado
}

// Destructor
Usuario::~Usuario() = default;

// Getters
Identidad Usuario::getIdentidad() const
{
    return identidad; // Retorna la identidad del usuario
}

Contacto Usuario::getContacto() const
{
    return contacto; // Retorna la informaci�n de contacto del usuario
}

// Setters
bool Usuario::setIdentidad(const Identidad& identidad)
{
    this->identidad = identidad; // Establece la nueva identidad
    return true; // Indica que se ha realizado con �xito
}

bool Usuario::setContacto(const Contacto& contacto)
{
    this->contacto = contacto; // Establece la nueva informaci�n de contacto
    return true; // Indica que se ha realizado con �xito
}

string Usuario::toDebug() const
{
    ostringstream debug; // Para construir la representaci�n de depuraci�n
    debug << "Usuario(Identidad='" << identidad.toDebug()
        << "', Contacto='" << contacto.toDebug()
        << "')";
    return debug.str(); // Devuelve la representaci�n de depuraci�n
}

string Usuario::toSave() const
{
    ostringstream out; // Para construir la cadena de salida
    out << identidad.toSave() << Serialization::DELIMITER_MAIN
        << contacto.toSave() << Serialization::DELIMITER_MAIN;
    return out.str(); // Devuelve la cadena generada
}

void Usuario::load(const string& data)
{
    istringstream in(data);
    string identidadData, contactoData;

    // Intenta cargar datos de identidad y contacto desde el string
    if (!getline(in, identidadData, Serialization::DELIMITER_MAIN) ||
        !getline(in, contactoData, Serialization::DELIMITER_MAIN))
    {
        throw runtime_error("Error al cargar los datos: datos insuficientes o mal formateados.");
    }
    identidad = Identidad(identidadData); // Inicializa identidad
    contacto = Contacto(contactoData); // Inicializa contacto
}

string Usuario::toShow() const
{
    ostringstream show; // Para mostrar detalles del usuario

    show << "=== Detalles del Usuario ===\n";
    show << "Identidad:\n";
    show << "DNI: " << identidad.getDNI() << '\n';
    show << "Primer Apellido: " << identidad.getPrimerApellido() << '\n';
    show << "Segundo Apellido: " << identidad.getSegundoApellido() << '\n';
    show << "Nombre(s): " << identidad.getNombres() << '\n';
    show << "Sexo: " << identidad.toStringSexo() << '\n';
    show << "Estado Civil: " << identidad.toStringEstadoCivil() << '\n';
    show << "Contacto:\n";
    show << "Tel�fono: " << contacto.getTelefono() << '\n';
    show << "Correo Electr�nico: " << contacto.getCorreoElectronico() << '\n';
    show << "Departamento: " << contacto.getDepartamento() << '\n';
    show << "Provincia: " << contacto.getProvincia() << '\n';
    show << "Distrito: " << contacto.getDistrito() << '\n';
    show << "Direcci�n: " << contacto.getDireccion() << '\n';

    return show.str(); // Devuelve la cadena de detalles
}
