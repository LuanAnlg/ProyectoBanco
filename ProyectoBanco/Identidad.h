#pragma once

#include "Fecha.h"

enum class Sexo { Masculino, Femenino, Desconocido };               // Enum para representar el sexo
enum class EstadoCivil { Soltero, Casado, Divorciado, Viudo, Desconocido }; // Enum para representar el estado civil

// Módulo Identidad
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

    // Métodos de acceso

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

    // Métodos de modificación

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

    // Métodos adicionales

    // Convierte el sexo a una cadena representativa
    string toStringSexo() const;
    // Convierte el estado civil a una cadena representativa
    string toStringEstadoCivil() const;

    // Métodos de depuración y guardado

    // Devuelve una cadena con la información de depuración
    string toDebug() const override;
    // Devuelve una cadena con los datos para guardar
    string toSave() const override;
    // Carga los datos desde una cadena de texto
    void load(const string& data) override;

    // Método para generar datos aleatorios
    void generateRandom() override;
};

// Implementación de Constructores
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
    load(datos); // Carga información desde la cadena
}

// Implementación de Getters
string Identidad::getDNI() const { return dni; }
string Identidad::getPrimerApellido() const { return primerApellido; }
string Identidad::getSegundoApellido() const { return segundoApellido; }
string Identidad::getNombres() const { return nombres; }
Fecha Identidad::getFechaNacimiento() const { return fechaNacimiento; }
Sexo Identidad::getSexo() const { return sexo; }
EstadoCivil Identidad::getEstadoCivil() const { return estadoCivil; }

// Implementación de Setters
bool Identidad::setDNI(const string& dni)
{
    // Verifica que el DNI tenga exactamente 8 caracteres y contenga solo dígitos
    if (dni.length() != 8) return false;
    for (char c : dni) {
        if (c < '0' || c > '9') return false; // Solo dígitos permitidos
    }
    this->dni = dni; // Asigna el DNI
    return true; // Éxito
}

bool Identidad::setPrimerApellido(const string& primerApellido)
{
    if (primerApellido.empty()) return false; // No se permite vacío
    this->primerApellido = primerApellido; // Asigna el primer apellido
    return true; // Éxito
}

bool Identidad::setSegundoApellido(const string& segundoApellido)
{
    if (segundoApellido.empty()) return false; // No se permite vacío
    this->segundoApellido = segundoApellido; // Asigna el segundo apellido
    return true; // Éxito
}

bool Identidad::setNombres(const string& nombres)
{
    if (nombres.empty()) return false; // No se permite vacío
    this->nombres = nombres; // Asigna los nombres
    return true; // Éxito
}

bool Identidad::setFechaNacimiento(const Fecha& fechaNacimiento)
{
    this->fechaNacimiento = fechaNacimiento; // Asigna la fecha de nacimiento
    return true; // Éxito
}

bool Identidad::setSexo(Sexo sexo)
{
    if (sexo != Sexo::Masculino && sexo != Sexo::Femenino)
    {
        return false;
    }
    this->sexo = sexo; // Asigna el sexo
    return true; // Éxito
}

bool Identidad::setEstadoCivil(EstadoCivil estadoCivil)
{
    if (estadoCivil != EstadoCivil::Soltero && estadoCivil != EstadoCivil::Casado &&
        estadoCivil != EstadoCivil::Divorciado && estadoCivil != EstadoCivil::Viudo)
    {
        return false;
    }
    this->estadoCivil = estadoCivil; // Asigna el estado civil
    return true; // Éxito
}

// Métodos de conversión
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

// Método para retornar una representación textual del objeto
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

// Método para guardar la información
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

// Método para cargar la información
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

    // Asigna los datos leídos utilizando los setters
    if (!setDNI(dni) || !setPrimerApellido(primerApellido) ||
        !setSegundoApellido(segundoApellido) || !setNombres(nombres))
    {
        throw runtime_error("Error al asignar datos a la identidad: formato inválido.");
    }

    // Asigna el sexo basado en la cadena leída
    sexo = (sexoString == "Masculino") ? Sexo::Masculino :
        (sexoString == "Femenino") ? Sexo::Femenino : Sexo::Desconocido;

    // Asigna el estado civil basado en la cadena leída
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

// Método para generar datos aleatorios
void Identidad::generateRandom() {
    // Generar un DNI aleatorio de 8 dígitos
    dni.clear();
    for (int i = 0; i < 8; ++i) {
        dni += '0' + (rand() % 10); // Generar un dígito aleatorio entre 0 y 9
    }

    // Generar apellidos aleatorios usando un array estático de apellidos
    const string apellidos[] = {
        "Gonzalez", "Perez", "Lopez", "Martinez", "Garcia", "Rodriguez",
        "Hernandez", "Diaz", "Fernandez", "Lima", "Sanchez", "Vasquez",
        "Romero", "Alvarez", "Morales", "Jimenez"
    };
    primerApellido = apellidos[rand() % (sizeof(apellidos) / sizeof(apellidos[0]))];
    segundoApellido = apellidos[rand() % (sizeof(apellidos) / sizeof(apellidos[0]))];

    // Generar nombres aleatorios usando un array estático de nombres
    const string nombresPosibles[] = {
        "Juan", "Maria", "Carlos", "Ana", "Luis", "Laura", "Jose", "Carmen",
        "Miguel", "Sofia", "Antonio", "Elena", "Pedro", "Isabel", "David",
        "Patricia", "Raul", "Marta", "Eduardo", "Beatriz"
    };
    nombres = nombresPosibles[rand() % (sizeof(nombresPosibles) / sizeof(nombresPosibles[0]))]
        + " "
        + nombresPosibles[rand() % (sizeof(nombresPosibles) / sizeof(nombresPosibles[0]))];

    // Generar fecha de nacimiento aleatoria (año entre 1970 y 2000)
    int dia = rand() % 31 + 1;      // Día entre 1 y 31
    int mes = rand() % 12 + 1;      // Mes entre 1 y 12
    int anio = rand() % 31 + 1970;  // Año entre 1970 y 2000
    fechaNacimiento = Fecha(dia, mes, anio);

    // Generar sexo aleatorio (Masculino o Femenino)
    sexo = (rand() % 2 == 0) ? Sexo::Masculino : Sexo::Femenino;

    // Generar estado civil aleatorio
    estadoCivil = static_cast<EstadoCivil>(rand() % 5); // Genera un número entre 0 y 4

    // Opcional: Asegurar que el estado civil sea uno válido
    // Puedes agregar validación si lo deseas, aunque el `rand() % 5` debería funcionar correctamente.
}