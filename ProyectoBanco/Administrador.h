#pragma once

#include "Usuario.h"
#include "MQuejas.h"
#include "IFileable.h"

class Administrador : public Usuario, IFileable
{
private:

    Fecha fechaActual;

    MQuejas quejas;

    void _addAdmintrador();

    void _interactRegistrarAdministrador();

public:

    Administrador(const Fecha& fechaActual, const Identidad& identidad, const Contacto& contacto);
    Administrador(const Fecha& fechaActual, const string& datos);
    Administrador();

    ~Administrador();

    string toDebug() const override;
    string toSave() const override;
    string toShow() const override;
    bool saveToFile() const override;
};

//
//// Implementacion de los metodos
//
//Administrador::Administrador(const FechaCompleta& fechaActual)
//    : Usuario("", "", "", FechaCompleta(), "", TUsuario::Adminitrador), fechaActual(fechaActual) {}
//
//Administrador::Administrador(const string& nombreCompleto,
//                             const string& dni,
//                             const string& telefono,
//                             const FechaCompleta& fechaNacimiento,
//                             const string& direccion,
//                             const FechaCompleta& fechaActual)
//    : Usuario(nombreCompleto, dni, telefono, fechaNacimiento, direccion, TUsuario::Adminitrador), fechaActual(fechaActual) {}
//
//Administrador::~Administrador() = default;
//
//// Mostrar el Administrador
//string Administrador::toString() const
//{
//    ostringstream ss;
//    ss << '\n';
//    ss << "/---------------------------------------------\n";
//    ss << "| Nombre Completo: " << nombreCompleto << "\n";
//    ss << "| DNI: " << dni << "\n";
//    ss << "| Telefono: " << telefono << "\n";
//    ss << "| Fecha de Nacimiento: " << fechaNacimiento.toString() << "\n";
//    ss << "| Direccion: " << direccion << "\n";
//    ss << "\\---------------------------------------------\n";
//
//    return ss.str();
//}
//
//// Itereamos las quejas
//void Administrador::mostrarQuejas() const
//{
//    cout << "\nTodas las Quejas:\n";
//    if (quejas.empty())
//    {
//        cout << "No hay quejas registradas.\n";
//    }
//    else
//    {
//        for (const auto& queja : quejas)
//        {
//            cout << queja->toString() << "\n";
//        }
//    }
//}
//
//// Hacemos top a la pila
//void Administrador::mostrarUltimaQueja() const
//{
//    cout << "\nUltima Queja:\n";
//    if (quejas.empty())
//    {
//        cout << "No hay quejas registradas.\n";
//    }
//    else
//    {
//        cout << quejas.top()->toString() << "\n";
//    }
//}
//
//void Administrador::resolverUltimaQueja()
//{
//    if (quejas.empty())
//    {
//        cout << "No hay quejas para resolver.\n";
//    }
//    else
//    {
//        cout << "Resolviendo queja: " << quejas.top()->toString() << "\n";
//        quejas.pop(); // Eliminar la queja resuelta
//    }
//}
//
//void Administrador::registrarAdministrador() const
//{
//    std::cout << "\n=== Registrar nuevo Administrador ===\n";
//    std::string nombreCompleto;
//    std::string	dni;
//    std::string telefono;
//    std::string direccion;
//    std::string fechaNacimientoStr;
//
//    // Solicitar informacion del administrador
//    std::cout << "|> Nombre Completo: ";
//    std::cin.ignore();
//    std::getline(std::cin, nombreCompleto);
//
//    std::cout << "|> DNI: ";
//    std::cin >> dni;
//
//    std::cout << "|> Telefono: ";
//    std::cin >> telefono;
//
//    std::cout << "|> Fecha de Nacimiento (DD/MM/YYYY): ";
//    std::cin >> fechaNacimientoStr;
//
//    std::cout << "|> Direccion: ";
//    std::cin.ignore();
//    std::getline(std::cin, direccion);
//
//    FechaCompleta fechaNacimiento(fechaNacimientoStr);
//
//    // Crear un nuevo administrador
//    Administrador nuevoAdministrador(nombreCompleto, dni, telefono, fechaNacimiento, direccion, fechaActual);
//    nuevoAdministrador.guardar();
//    std::cout << "Cliente registrado con exito: \n" << nuevoAdministrador.toString() << '\n';
//}
//
//
//
//// Interfaz controladora del Admin
//void Administrador::interfaz()
//{
//    int opcion;
//
//    do
//    {
//        system("pause");
//        system("cls");
//        std::cout << " _  _    ___   ___ _____ _  _  _  _  _ \n";
//        std::cout << "|_|| \\|V| | |\\| | (_  | |_)|_|| \\/ \\|_)\n";
//        std::cout << "| ||_/| |_|_| |_|___) | | \\| ||_/\\_/| \\\n";
//        cout << "1. Ver informacion del administrador\n";
//        cout << "2. Ver todas las quejas\n";
//        cout << "3. Ver ultima queja\n";
//        cout << "4. Resolver ultima queja\n";
//        cout << "5. Registrar a un nuevo administrador\n";
//        cout << "6. Salir y guardar\n";
//        cout << "|> Selecciona una opcion: ";
//        cin >> opcion;
//        system("cls");
//
//        switch (opcion)
//        {
//        case 1:
//            cout << toString() << '\n';
//            break;
//
//        case 2:
//            mostrarQuejas();
//            break;
//
//        case 3:
//            mostrarUltimaQueja();
//            break;
//
//        case 4:
//            resolverUltimaQueja();
//            break;
//
//        case 5:
//            registrarAdministrador();
//            break;
//
//        case 6:
//            guardar();
//            cout << "Saliendo y guardando...\n";
//            break;
//
//        default:
//            cout << "Opcion no valida. Intenta de nuevo.\n";
//        }
//
//    } while (opcion != 6);
//}
//
//// Guardar los datos de Administrador y de las Quejas
//void Administrador::guardar() const
//{
//    ofstream archivo(dni + ".txt");
//    if (archivo.is_open())
//    {
//        // Guardar informacion del administrador
//        archivo << static_cast<int>(tipo) << ":" << nombreCompleto << ":" << dni << ":" << telefono << ":"
//                << fechaNacimiento.toString() << ":" << direccion << "\n";
//
//        archivo.close();
//
//        ofstream archivoQuejas("Quejas.txt");
//        if (archivoQuejas.is_open())
//        {
//            for (const auto& queja : quejas)
//            {
//                archivoQuejas << queja->toSave() << '\n';
//            }
//
//            archivoQuejas.close();
//        }
//        else
//        {
//            cout << "Error al abrir el archivo Quejas.txt para guardar las quejas.\n";
//        }
//    }
//    else
//    {
//        cout << "Error al abrir el archivo para guardar.\n";
//    }
//}
//
//// Abrir y verificar si se puede abrir el archivo
//bool Administrador::abrir(const string& nombreArchivo)
//{
//    // Primero abrimos el Administrador
//    ifstream archivo(nombreArchivo);
//    if (archivo.is_open())
//    {
//        string linea;
//        getline(archivo, linea);
//        istringstream ss(linea);
//        std::string tipoStr;
//        getline(ss, tipoStr, ':');
//        tipo = static_cast<TUsuario>(std::stoi(tipoStr));
//
//        if (tipo != TUsuario::Adminitrador) return false;
//        getline(ss, nombreCompleto, ':');
//        getline(ss, dni, ':');
//        getline(ss, telefono, ':');
//
//        string fechaStr;
//        getline(ss, fechaStr, ':');
//        fechaNacimiento = FechaCompleta(fechaStr);
//
//        getline(ss, direccion);
//
//        // Luego las quejas
//        ifstream archivoQuejas("Quejas.txt");
//        while (getline(archivoQuejas, linea))
//        {
//            if (linea.empty()) continue;
//
//            Queja* nuevaQueja = new Queja(linea);
//            if (nuevaQueja != nullptr)
//            {
//                quejas.push(nuevaQueja);
//            }
//            else
//            {
//                cout << "Error al crear una nueva queja.\n";
//            }
//        }
//        archivoQuejas.close();
//        archivo.close();
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
//
//