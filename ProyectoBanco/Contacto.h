#pragma once

#include "ISavable.h"
#include "IDebugable.h"
#include "IRandomizable.h"

class Contacto : public IDebugable, ISavable, IRandomizable
{
private:
    string telefono;                 // N�mero de tel�fono de contacto
    string correoElectronico;        // Direcci�n de correo electr�nico de contacto
    string departamento;             // Departamento de residencia
    string provincia;                // Provincia de residencia
    string distrito;                 // Distrito de residencia
    string direccion;                // Direcci�n espec�fica de residencia

public:
    // Constructores

    // Constructor que inicializa todos los datos de contacto
    Contacto(const string& telefono, const string& correoElectronico,
        const string& departamento, const string& provincia,
        const string& distrito, const string& direccion);

    // Constructor por defecto
    Contacto();

    // Constructor que carga los datos desde una cadena de datos
    Contacto(const string& data);

    // Destructor por defecto
    ~Contacto() = default;

    // M�todos de acceso

    // Retorna el n�mero de tel�fono
    string getTelefono() const;

    // Retorna el correo electr�nico
    string getCorreoElectronico() const;

    // Retorna el departamento
    string getDepartamento() const;

    // Retorna la provincia
    string getProvincia() const;

    // Retorna el distrito
    string getDistrito() const;

    // Retorna la direcci�n completa
    string getDireccion() const;

    // M�todos de modificaci�n

    // Establece el n�mero de tel�fono
    bool setTelefono(const string& telefono);

    // Establece el correo electr�nico
    bool setCorreoElectronico(const string& correoElectronico);

    // Establece el departamento
    bool setDepartamento(const string& departamento);

    // Establece la provincia
    bool setProvincia(const string& provincia);

    // Establece el distrito
    bool setDistrito(const string& distrito);

    // Establece la direcci�n completa
    bool setDireccion(const string& direccion);

    // M�todos de depuraci�n y guardado

    // Retorna una representaci�n de depuraci�n del objeto
    inline string toDebug() const override;

    // Retorna una representaci�n en cadena para guardar los datos del objeto
    inline string toSave() const override;

    // Carga los datos desde una cadena en formato espec�fico
    void load(const string& datos) override;

    void generateRandom() override;
};

// Constructor que inicializa los atributos con los valores proporcionados
Contacto::Contacto(const std::string& telefono, const std::string& correoElectronico,
    const std::string& departamento, const std::string& provincia,
    const std::string& distrito, const std::string& direccion)
    : telefono(telefono), correoElectronico(correoElectronico),
    departamento(departamento), provincia(provincia),
    distrito(distrito), direccion(direccion) {}

// Constructor por defecto que inicializa atributos vac�os
Contacto::Contacto()
    : telefono(""), correoElectronico(""),
    departamento(""), provincia(""),
    distrito(""), direccion("") {}

// Constructor que carga informaci�n desde un string
Contacto::Contacto(const std::string& datos)
{
    load(datos); // Carga los datos desde el string proporcionado
}

// Getters
std::string Contacto::getTelefono() const { return telefono; }
std::string Contacto::getCorreoElectronico() const { return correoElectronico; }
std::string Contacto::getDepartamento() const { return departamento; }
std::string Contacto::getProvincia() const { return provincia; }
std::string Contacto::getDistrito() const { return distrito; }
std::string Contacto::getDireccion() const { return direccion; }

// Setter para el tel�fono, debe tener 9 d�gitos
bool Contacto::setTelefono(const std::string& telefono)
{
    if (telefono.size() != 9) return false; // Debe tener 9 caracteres
    for (char c : telefono)
    {
        if (c < '0' || c > '9') return false; // Solo d�gitos permitidos
    }
    this->telefono = telefono; // Establece el tel�fono si es v�lido
    return true; // Retorna true si se establece con �xito
}

// Setter para el correo electr�nico, debe contener '@' y '.'
bool Contacto::setCorreoElectronico(const std::string& correoElectronico)
{
    if (correoElectronico.empty()) return false; // No debe estar vac�o

    bool tieneArroba = false; // Indica si hay '@'
    bool tienePunto = false;  // Indica si hay '.'

    for (size_t i = 0; i < correoElectronico.length(); ++i)
    {
        if (correoElectronico[i] == '@')
        {
            tieneArroba = true; // Se encontr� '@'
        }
        else if (tieneArroba && correoElectronico[i] == '.')
        {
            tienePunto = true; // '.' debe venir despu�s de '@'
        }
    }

    if (tieneArroba && tienePunto)
    {
        this->correoElectronico = correoElectronico; // Establecer el correo si es v�lido
        return true; // Retorna true si ambos est�n presentes
    }
    return false; // Retorna false si el formato es inv�lido
}

// Setter para el departamento
bool Contacto::setDepartamento(const std::string& departamento)
{
    if (departamento.empty()) return false; // No debe estar vac�o
    this->departamento = departamento; // Establece el departamento
    return true; // Retorna true si se establece con �xito
}

// Setter para la provincia
bool Contacto::setProvincia(const std::string& provincia)
{
    if (provincia.empty()) return false; // No debe estar vac�o
    this->provincia = provincia; // Establece la provincia
    return true; // Retorna true si se establece con �xito
}

// Setter para el distrito
bool Contacto::setDistrito(const std::string& distrito)
{
    if (distrito.empty()) return false; // No debe estar vac�o
    this->distrito = distrito; // Establece el distrito
    return true; // Retorna true si se establece con �xito
}

// Setter para la direcci�n
bool Contacto::setDireccion(const std::string& direccion)
{
    if (direccion.empty()) return false; // No debe estar vac�o
    this->direccion = direccion; // Establece la direcci�n
    return true; // Retorna true si se establece con �xito
}

// M�todo para retornar una representaci�n textual del objeto
inline std::string Contacto::toDebug() const
{
    std::ostringstream debug; // Flujo para construir la representaci�n textual
    debug << "Contacto(telefono='" << telefono << "'"
        << ", correoElectronico='" << correoElectronico << "'"
        << ", departamento='" << departamento << "'"
        << ", provincia='" << provincia << "'"
        << ", distrito='" << distrito << "'"
        << ", direccion='" << direccion << "')"; // Construcci�n de la cadena de salida
    return debug.str(); // Retorna la representaci�n textual
}

// M�todo para guardar la informaci�n en un formato espec�fico
std::string Contacto::toSave() const
{
    std::ostringstream out; // Flujo de salida para guardar datos
    out << telefono << Serialization::DELIMITER_SECTION
        << correoElectronico << Serialization::DELIMITER_SECTION
        << departamento << Serialization::DELIMITER_SECTION
        << provincia << Serialization::DELIMITER_SECTION
        << distrito << Serialization::DELIMITER_SECTION
        << direccion; // Guardar los atributos separados por el delimitador
    return out.str(); // Retorna la cadena en formato de guardado
}

// M�todo para cargar informaci�n desde un string
void Contacto::load(const std::string& data)
{
    std::istringstream in(data); // Flujo de entrada para cargar datos
    if (!std::getline(in, telefono, Serialization::DELIMITER_SECTION) ||
        !std::getline(in, correoElectronico, Serialization::DELIMITER_SECTION) ||
        !std::getline(in, departamento, Serialization::DELIMITER_SECTION) ||
        !std::getline(in, provincia, Serialization::DELIMITER_SECTION) ||
        !std::getline(in, distrito, Serialization::DELIMITER_SECTION) ||
        !std::getline(in, direccion, Serialization::DELIMITER_SECTION))
    {
        throw std::runtime_error("Error al cargar los datos: datos insuficientes o mal formateados.");
    }

    // Validar y asignar los atributos usando los setters
    if (!setTelefono(telefono) ||
        !setCorreoElectronico(correoElectronico) ||
        !setDepartamento(departamento) ||
        !setProvincia(provincia) ||
        !setDistrito(distrito) ||
        !setDireccion(direccion))
    {
        throw std::runtime_error("Error al asignar datos al contacto: formato inv�lido.");
    }
}

// M�todo para generar correo electr�nico aleatorio
void Contacto::generateRandom() {
    // Generar un tel�fono m�vil aleatorio (empezando con 9, seguido de 8 d�gitos aleatorios)
    telefono.clear();
    telefono += "9"; // El primer d�gito de un n�mero celular en Per� siempre es 9
    for (int i = 0; i < 8; ++i) {
        telefono += '0' + (rand() % 10); // Genera un d�gito aleatorio entre 0 y 9
    }

    // Generar un correo electr�nico aleatorio usando palabras y n�meros
    const string palabras[] = {
        "sol", "luna", "estrella", "flor", "cielo", "montana", "rayo", "agua", "fuego", "viento",
        "noche", "dia", "piedra", "estrella", "oceano", "florecer", "sombra", "luz", "fuerza", "amor"
    };

    // Elegir dos palabras aleatorias de las que ya no contienen caracteres especiales
    string palabra1 = palabras[rand() % (sizeof(palabras) / sizeof(palabras[0]))];
    string palabra2 = palabras[rand() % (sizeof(palabras) / sizeof(palabras[0]))];

    // Generar un n�mero aleatorio para agregar al correo
    int numero = rand() % 10000; // N�mero aleatorio de 4 d�gitos

    // Crear el correo electr�nico
    correoElectronico = palabra1 + palabra2 + std::to_string(numero) + "@gmail.com";

    // Generar datos geogr�ficos aleatorios: Departamento, Provincia, Distrito
    const string departamentos[] = {
        "Lima", "Arequipa", "Cusco", "Piura", "La Libertad", "Loreto", "Callao", "Junin", "Ancash", "Ica"
    };
    const string provincias[] = {
        "Lima", "Arequipa", "Trujillo", "Cusco", "Piura", "Tacna", "Chiclayo", "Puno", "Huancayo", "Chimbote"
    };
    const string distritos[] = {
        "Miraflores", "San Isidro", "Barranco", "Surco", "San Juan de Lurigancho", "San Martin de Porres",
        "Callao", "Arequipa", "Piura", "Cusco"
    };

    // Generamos aleatoriamente un departamento, una provincia y un distrito
    departamento = departamentos[rand() % (sizeof(departamentos) / sizeof(departamentos[0]))];
    provincia = provincias[rand() % (sizeof(provincias) / sizeof(provincias[0]))];
    distrito = distritos[rand() % (sizeof(distritos) / sizeof(distritos[0]))];

    // Generar una direcci�n aleatoria, puede incluir un n�mero de casa
    stringstream direccionStream;
    direccionStream << "Calle " << rand() % 100 + 1 << " (" << (rand() % 3 == 0 ? "Avenida" : "Jiron") << ")";
    direccion = direccionStream.str();
}