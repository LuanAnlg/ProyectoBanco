#pragma once

#include "Fecha.h"

enum class Sexo { Masculino, Femenino, Desconocido };               // Enum para representar el sexo
enum class EstadoCivil { Soltero, Casado, Divorciado, Viudo, Desconocido }; // Enum para representar el estado civil

// M�dulo Identidad
class Identidad : public IDebugable, ISavable, IRandomizable
{
private:
    string dni;                    // DNI de la persona
    string primerApellido;         // Primer apellido de la persona
    string segundoApellido;        // Segundo apellido de la persona
    string nombres;                // Nombres de la persona
    Fecha fechaNacimiento;              // Fecha de nacimiento de la persona
    Sexo sexo;                          // Sexo de la persona
    EstadoCivil estadoCivil;            // Estado civil de la persona

public:
    // Constructores

    // Constructor que inicializa todos los atributos
    Identidad(const string& dni, const string& primerApellido,
        const string& segundoApellido, const string& nombres,
        const Fecha& fechaNacimiento, Sexo sexo, EstadoCivil estadoCivil);
    // Constructor que inicializa los atributos a partir de una cadena de datos
    Identidad(const string& datos);
    // Constructor por defecto
    Identidad();
    // Destructor por defecto
    ~Identidad() = default;

    // M�todos de acceso

    // Retorna el DNI
    string getDNI() const;
    // Retorna el primer apellido
    string getPrimerApellido() const;
    // Retorna el segundo apellido
    string getSegundoApellido() const;
    // Retorna los nombres
    string getNombres() const;
    // Retorna la fecha de nacimiento
    Fecha getFechaNacimiento() const;
    // Retorna el sexo
    Sexo getSexo() const;
    // Retorna el estado civil
    EstadoCivil getEstadoCivil() const;

    // M�todos de modificaci�n

    // Establece el DNI
    bool setDNI(const string& dni);
    // Establece el primer apellido
    bool setPrimerApellido(const string& primerApellido);
    // Establece el segundo apellido
    bool setSegundoApellido(const string& segundoApellido);
    // Establece los nombres
    bool setNombres(const string& nombres);
    // Establece la fecha de nacimiento
    bool setFechaNacimiento(const Fecha& fechaNacimiento);
    // Establece el sexo
    bool setSexo(Sexo sexo);
    // Establece el estado civil
    bool setEstadoCivil(EstadoCivil estadoCivil);

    // M�todos adicionales

    // Convierte el sexo a una cadena representativa
    string toStringSexo() const;
    // Convierte el estado civil a una cadena representativa
    string toStringEstadoCivil() const;

    // M�todos de depuraci�n y guardado

    // Devuelve una cadena con la informaci�n de depuraci�n
    string toDebug() const override;
    // Devuelve una cadena con los datos para guardar
    string toSave() const override;
    // Carga los datos desde una cadena de texto
    void load(const string& data) override;

    // M�todo para generar datos aleatorios
    void generateRandom() override;
};

// Implementaci�n de Constructores
Identidad::Identidad(const string& dni, const string& primerApellido,
    const string& segundoApellido, const string& nombres,
    const Fecha& fechaNacimiento, Sexo sexo, EstadoCivil estadoCivil)
    : dni(dni), primerApellido(primerApellido), segundoApellido(segundoApellido),
    nombres(nombres), fechaNacimiento(fechaNacimiento), sexo(sexo), estadoCivil(estadoCivil)
{}

Identidad::Identidad()
    : dni(""), primerApellido(""), segundoApellido(""), nombres(""),
    fechaNacimiento(Fecha()), sexo(Sexo::Desconocido), estadoCivil(EstadoCivil::Desconocido)
{}

Identidad::Identidad(const string& datos)
{
    load(datos); // Carga informaci�n desde la cadena
}

// Implementaci�n de Getters
string Identidad::getDNI() const { return dni; }
string Identidad::getPrimerApellido() const { return primerApellido; }
string Identidad::getSegundoApellido() const { return segundoApellido; }
string Identidad::getNombres() const { return nombres; }
Fecha Identidad::getFechaNacimiento() const { return fechaNacimiento; }
Sexo Identidad::getSexo() const { return sexo; }
EstadoCivil Identidad::getEstadoCivil() const { return estadoCivil; }

// Implementaci�n de Setters
bool Identidad::setDNI(const string& dni)
{
    // Verifica que el DNI tenga exactamente 8 caracteres y contenga solo d�gitos
    if (dni.length() != 8) return false;
    for (char c : dni) {
        if (c < '0' || c > '9') return false; // Solo d�gitos permitidos
    }
    this->dni = dni; // Asigna el DNI
    return true; // �xito
}

bool Identidad::setPrimerApellido(const string& primerApellido)
{
    if (primerApellido.empty()) return false; // No se permite vac�o
    this->primerApellido = primerApellido; // Asigna el primer apellido
    return true; // �xito
}

bool Identidad::setSegundoApellido(const string& segundoApellido)
{
    if (segundoApellido.empty()) return false; // No se permite vac�o
    this->segundoApellido = segundoApellido; // Asigna el segundo apellido
    return true; // �xito
}

bool Identidad::setNombres(const string& nombres)
{
    if (nombres.empty()) return false; // No se permite vac�o
    this->nombres = nombres; // Asigna los nombres
    return true; // �xito
}

bool Identidad::setFechaNacimiento(const Fecha& fechaNacimiento)
{
    this->fechaNacimiento = fechaNacimiento; // Asigna la fecha de nacimiento
    return true; // �xito
}

bool Identidad::setSexo(Sexo sexo)
{
    if (sexo != Sexo::Masculino && sexo != Sexo::Femenino)
    {
        return false;
    }
    this->sexo = sexo; // Asigna el sexo
    return true; // �xito
}

bool Identidad::setEstadoCivil(EstadoCivil estadoCivil)
{
    if (estadoCivil != EstadoCivil::Soltero && estadoCivil != EstadoCivil::Casado &&
        estadoCivil != EstadoCivil::Divorciado && estadoCivil != EstadoCivil::Viudo)
    {
        return false;
    }
    this->estadoCivil = estadoCivil; // Asigna el estado civil
    return true; // �xito
}

// M�todos de conversi�n
string Identidad::toStringSexo() const
{
    switch (sexo) {
    case Sexo::Masculino: return "Masculino";
    case Sexo::Femenino: return "Femenino";
    case Sexo::Desconocido: return "Desconocido";
    }
    return "Desconocido"; // Valor por defecto si no coincide
}

string Identidad::toStringEstadoCivil() const
{
    switch (estadoCivil) {
    case EstadoCivil::Soltero: return "Soltero";
    case EstadoCivil::Casado: return "Casado";
    case EstadoCivil::Divorciado: return "Divorciado";
    case EstadoCivil::Viudo: return "Viudo";
    case EstadoCivil::Desconocido: return "Desconocido";
    }
    return "Desconocido"; // Valor por defecto si no coincide
}

// M�todo para retornar una representaci�n textual del objeto
string Identidad::toDebug() const
{
    ostringstream debug;
    debug << "Identidad(DNI='" << dni
        << "', PrimerApellido='" << primerApellido
        << "', SegundoApellido='" << segundoApellido
        << "', Nombres='" << nombres
        << "', FechaNacimiento='" << fechaNacimiento.toStringDDMMAAAA()
        << "', Sexo='" << toStringSexo()
        << "', EstadoCivil='" << toStringEstadoCivil()
        << "')";
    return debug.str();
}

// M�todo para guardar la informaci�n
string Identidad::toSave() const
{
    ostringstream out; // Para construir el string de salida
    out << dni << Serialization::DELIMITER_SECTION
        << primerApellido << Serialization::DELIMITER_SECTION
        << segundoApellido << Serialization::DELIMITER_SECTION
        << nombres << Serialization::DELIMITER_SECTION
        << fechaNacimiento.toStringDDMMAAAA() << Serialization::DELIMITER_SECTION
        << toStringSexo() << Serialization::DELIMITER_SECTION
        << toStringEstadoCivil();
    return out.str(); // Retorna el string generado
}

// M�todo para cargar la informaci�n
void Identidad::load(const string& data)
{
    istringstream in(data); // Flujo para leer datos
    string fechaString, sexoString, estadoCivilString;

    // Lee los datos separados por delimitadores
    if (!getline(in, dni, Serialization::DELIMITER_SECTION) ||
        !getline(in, primerApellido, Serialization::DELIMITER_SECTION) ||
        !getline(in, segundoApellido, Serialization::DELIMITER_SECTION) ||
        !getline(in, nombres, Serialization::DELIMITER_SECTION) ||
        !getline(in, fechaString, Serialization::DELIMITER_SECTION) ||
        !getline(in, sexoString, Serialization::DELIMITER_SECTION) ||
        !getline(in, estadoCivilString, Serialization::DELIMITER_SECTION))
    {
        throw runtime_error("Error al cargar los datos: datos insuficientes o mal formateados.");
    }

    // Asigna los datos le�dos utilizando los setters
    if (!setDNI(dni) || !setPrimerApellido(primerApellido) ||
        !setSegundoApellido(segundoApellido) || !setNombres(nombres))
    {
        throw runtime_error("Error al asignar datos a la identidad: formato inv�lido.");
    }

    // Asigna el sexo basado en la cadena le�da
    sexo = (sexoString == "Masculino") ? Sexo::Masculino :
        (sexoString == "Femenino") ? Sexo::Femenino : Sexo::Desconocido;

    // Asigna el estado civil basado en la cadena le�da
    if (estadoCivilString == "Soltero")
        estadoCivil = EstadoCivil::Soltero;
    else if (estadoCivilString == "Casado")
        estadoCivil = EstadoCivil::Casado;
    else if (estadoCivilString == "Divorciado")
        estadoCivil = EstadoCivil::Divorciado;
    else if (estadoCivilString == "Viudo")
        estadoCivil = EstadoCivil::Viudo;
    else
        estadoCivil = EstadoCivil::Desconocido;
}

// M�todo para generar datos aleatorios
void Identidad::generateRandom() {
    // Generar un DNI aleatorio de 8 d�gitos
    dni.clear();
    for (int i = 0; i < 8; ++i) {
        dni += '0' + (rand() % 10); // Generar un d�gito aleatorio entre 0 y 9
    }

    // Generar apellidos aleatorios usando un array est�tico de apellidos
    const string apellidos[] = {
        "Gonzalez", "Perez", "Lopez", "Martinez", "Garcia", "Rodriguez",
        "Hernandez", "Diaz", "Fernandez", "Lima", "Sanchez", "Vasquez",
        "Romero", "Alvarez", "Morales", "Jimenez"
    };
    primerApellido = apellidos[rand() % (sizeof(apellidos) / sizeof(apellidos[0]))];
    segundoApellido = apellidos[rand() % (sizeof(apellidos) / sizeof(apellidos[0]))];

    // Generar nombres aleatorios usando un array est�tico de nombres
    const string nombresPosibles[] = {
        "Juan", "Maria", "Carlos", "Ana", "Luis", "Laura", "Jose", "Carmen",
        "Miguel", "Sofia", "Antonio", "Elena", "Pedro", "Isabel", "David",
        "Patricia", "Raul", "Marta", "Eduardo", "Beatriz"
    };
    nombres = nombresPosibles[rand() % (sizeof(nombresPosibles) / sizeof(nombresPosibles[0]))]
        + " "
        + nombresPosibles[rand() % (sizeof(nombresPosibles) / sizeof(nombresPosibles[0]))];

    // Generar fecha de nacimiento aleatoria (a�o entre 1970 y 2000)
    int dia = rand() % 31 + 1;      // D�a entre 1 y 31
    int mes = rand() % 12 + 1;      // Mes entre 1 y 12
    int anio = rand() % 31 + 1970;  // A�o entre 1970 y 2000
    fechaNacimiento = Fecha(dia, mes, anio);

    // Generar sexo aleatorio (Masculino o Femenino)
    sexo = (rand() % 2 == 0) ? Sexo::Masculino : Sexo::Femenino;

    // Generar estado civil aleatorio
    estadoCivil = static_cast<EstadoCivil>(rand() % 5); // Genera un n�mero entre 0 y 4

    // Opcional: Asegurar que el estado civil sea uno v�lido
    // Puedes agregar validaci�n si lo deseas, aunque el `rand() % 5` deber�a funcionar correctamente.
}