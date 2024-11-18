#pragma once

#include "IFileable.h"
#include "IInteractive.h"
#include "SStack.h"
#include "AVLTree.h"
#include "Queja.h"

enum class TipoUsuario { Cliente, Administrador, Desconocido };

class MQuejas : public IDebugable, IFileable, IRandomizable, IInteractive
{
private:
    Fecha fechaActual;
    TipoUsuario tipo;
    SStack<Queja*> quejas;  // Cambiar de SStack<Queja> a SStack<Queja*>

    bool _addQueja(const string& cliente, const string& descripcion);
    bool _removeQueja();
    void _showQuejas();
    void _interactQuejarse();
    void _interactResolver();

public:
    MQuejas(const Fecha& fechaActual, const TipoUsuario& tipo);
    ~MQuejas();  // Destructor para liberar memoria

    Fecha getFechaActual() const;
    TipoUsuario getTipo() const;
    SStack<Queja*> getQuejas() const;

    bool setFechaActual(const Fecha& fechaActual);
    bool setTipo(const TipoUsuario& tipo);
    bool setQuejas(const SStack<Queja*>& quejas);

    string toDebug() const override;
    bool saveToFile() const override;
    bool loadFromFile() override;
    void generateRandom() override;
    void interact() override;
};

bool MQuejas::_addQueja(const string& cliente, const string& descripcion)
{
    if (cliente.empty() || descripcion.empty())
    {
        return false;
    }
    quejas.push(new Queja(fechaActual, cliente, descripcion));  // Asignar dinámicamente
    return true;
}

bool MQuejas::_removeQueja()
{
    if (quejas.empty())
    {
        return false;
    }
    delete quejas.top();  // Liberar la memoria de la queja
    quejas.pop();
    return true;
}

void MQuejas::_showQuejas()
{
    for (const auto& queja : quejas) {
        cout << queja->toShow() << '\n';
    }
}

void MQuejas::_interactQuejarse()
{
    string cliente;
    string descripcion;

    // Solicitar nombre del cliente
    cout << "Ingrese su primer apellido y su primer nombre (maximo 100 caracteres): ";
    getline(cin, cliente);

    // Validar entrada del cliente
    if (cliente.empty() || cliente.size() > 100) {
        cout << "El nombre no debe estar vacio ni exceder los 100 caracteres. Intente nuevamente.\n";
        return;
    }

    // Solicitar descripcion de la queja
    cout << "Ingrese su queja (maximo 300 caracteres): ";
    getline(cin, descripcion);

    // Validar entrada de la descripcion
    if (descripcion.empty() || descripcion.size() > 300) {
        cout << "La queja no debe estar vacia ni exceder los 300 caracteres. Intente nuevamente.\n";
        return;
    }

    // Intentar registrar la queja
    if (_addQueja(cliente, descripcion)) {
        cout << "Queja registrada exitosamente.\n";
    }
    else {
        cout << "No se pudo registrar la queja. Por favor intente nuevamente.\n";
    }
}

void MQuejas::_interactResolver()
{
    // Verificar si hay quejas pendientes
    if (quejas.empty())
    {
        cout << "No hay quejas pendientes para resolver.\n";
        return;
    }

    // Mostrar la queja más reciente
    cout << "Queja actual para resolver:\n";
    cout << quejas.top()->toShow() << "\n";

    // Confirmar resolución
    cout << "Desea resolver esta queja? (S/N): ";
    char opcion;
    cin >> opcion;

    // Validar la entrada
    if (opcion == 'S' || opcion == 's')
    {
        if (_removeQueja())
        {
            cout << "La queja ha sido resuelta exitosamente.\n";
        }
        else
        {
            cout << "No se pudo resolver la queja. Intente nuevamente.\n";
        }
    }
    else
    {
        cout << "La queja no fue resuelta.\n";
    }
}

MQuejas::MQuejas(const Fecha& fechaActual, const TipoUsuario& tipo)
    : fechaActual(fechaActual), tipo(tipo)
{}

MQuejas::~MQuejas()
{
    // Liberar la memoria de las quejas
    while (!quejas.empty()) {
        delete quejas.top();  // Liberar cada puntero
        quejas.pop();
    }
}

Fecha MQuejas::getFechaActual() const
{
    return fechaActual;
}

TipoUsuario MQuejas::getTipo() const
{
    return tipo;
}

SStack<Queja*> MQuejas::getQuejas() const
{
    return quejas;
}

bool MQuejas::setFechaActual(const Fecha& fechaActual)
{
    this->fechaActual = fechaActual;
    return true;
}

bool MQuejas::setTipo(const TipoUsuario& tipo)
{
    if (tipo != TipoUsuario::Administrador && tipo != TipoUsuario::Cliente)
    {
        return false;
    }
    this->tipo = tipo;
    return true; // Éxito
}

bool MQuejas::setQuejas(const SStack<Queja*>& quejas)
{
    this->quejas = quejas;
    return true;
}

string MQuejas::toDebug() const
{
    ostringstream out;
    out << "MQuejas(tipo=" << (tipo == TipoUsuario::Administrador ? "Administrador" : "Cliente");
    out << ", fechaActual=" << fechaActual.toStringDDMMAAAA()
        << ", historial=";
    for (const auto& queja : quejas) {
        out << queja->toDebug() << ", ";
    }
    string outStr = out.str();
    outStr.pop_back(); outStr.pop_back();
    outStr += ')';
    return outStr;
}

bool MQuejas::saveToFile() const
{
    if (quejas.empty())
    {
        cout << "No hay quejas para guardar.\n";
        return false;
    }

    ofstream outFile("Quejas.txt");
    if (!outFile)
    {
        cerr << "Error al abrir el archivo para guardar las quejas.\n";
        return false;
    }

    SStack<Queja*> tempStack(quejas);
    tempStack.invert();
    for (const auto& queja : tempStack) {
        outFile << queja->toSave() << '\n';
    }

    outFile.close();  // Asegúrate de cerrar el archivo
    return true;      // Retornar true al finalizar exitosamente
}

bool MQuejas::loadFromFile()
{
    ifstream inFile("Quejas.txt");
    if (!inFile)
    {
        return false;
    }

    quejas.clear(); // Limpiar el stack antes de cargar nuevas quejas

    string line;
    while (getline(inFile, line))
    {
        if (line.empty())
        {
            continue;
        }

        Queja* nuevaQueja = new Queja();  // Crear un nuevo puntero para la queja
        nuevaQueja->load(line);  // Método de carga para procesar cada línea
        quejas.push(nuevaQueja);  // Añadir la queja al stack
    }

    return true;
}

void MQuejas::generateRandom()
{
    auto compare = [](Queja* a, Queja* b) {
        return a->getFecha().toStringAAAAMMDD() > b->getFecha().toStringAAAAMMDD();
        };

    AVLTree<Queja*> randomQuejas(compare);

    // Número aleatorio de quejas a generar (por ejemplo entre 1 y 15 quejas)
    size_t numQuejas = 1 + rand() % 15;

    for (size_t i = 0; i < numQuejas; ++i)
    {
        Queja* q = new Queja();
        q->generateRandom();  // Genera una queja aleatoria
        randomQuejas.insert(q);
    }

    // Transferir las quejas ordenadas desde el árbol AVL
    while (!randomQuejas.empty()) {
        quejas.push(randomQuejas.getBack());  // Obtener el último elemento (más antiguo)
        randomQuejas.popBack();                  // Eliminar el último elemento del árbol
    }
}

void MQuejas::interact()
{
    if (tipo == TipoUsuario::Cliente)
    {
        _interactQuejarse();  // El cliente podrá presentar una queja
    }
    else
    {
        _interactResolver();  // El administrador podrá gestionar/resolver las quejas
    }
}
