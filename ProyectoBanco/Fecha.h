#pragma once

#include "ISavable.h"
#include "IDebugable.h"
#include "IRandomizable.h"
#include <functional>

// Componente Fecha
class Fecha : public ISavable, IDebugable, IRandomizable {
private:
    int dia; // Día del mes
    int mes; // Mes del año
    int anio; // Año

    bool esBisiesto(const int& anio) const;
    int diasDelMes(const int& mes, const int& anio) const;

    // Formatea un número a dos dígitos
    function<string(int)> formatearDosDigitos = [](int numero) -> string {
        return (numero < 10 ? "0" : "") + to_string(numero);
        };

public:
    Fecha(const int& dia, const int& mes, const int& anio);
    Fecha(const string& datos);
    Fecha();

    ~Fecha() = default;

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    bool setDia(const int& dia);
    bool setMes(const int& mes);
    bool setAnio(const int& anio);

    string toStringDDMM() const;
    string toStringMMAA() const;
    string toStringDDMMAAAA() const;
    string toStringAAAAMMDD() const;

    bool sumarDias(const int& dias);
    bool sumarMeses(const int& meses);
    bool sumarAnios(const int& anios);

    string toDebug() const override;
    string toSave() const override;
    void load(const string& data) override;
    void generateRandom() override;
};

// Constructor que establece la fecha con día, mes y año
Fecha::Fecha(const int& dia, const int& mes, const int& anio) {
    if (!setAnio(anio) || !setMes(mes) || !setDia(dia)) {
        throw runtime_error("Error: Fecha inválida.");
    }
}

// Constructor que inicializa la fecha desde una cadena
Fecha::Fecha(const string& datos) {
    load(datos);
}

// Constructor por defecto, establece la fecha a 01/01/2024
Fecha::Fecha() : dia(1), mes(1), anio(2024) {}

int Fecha::getDia() const {
    return dia;
}

int Fecha::getMes() const {
    return mes;
}

int Fecha::getAnio() const {
    return anio;
}

bool Fecha::esBisiesto(const int& anio) const {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int Fecha::diasDelMes(const int& mes, const int& anio) const {
    switch (mes) {
    case 2:
        return esBisiesto(anio) ? 29 : 28;
    case 4: case 6: case 9: case 11:
        return 30;
    default:
        return 31;
    }
}

bool Fecha::setDia(const int& dia) {
    if (dia < 1 || dia > diasDelMes(mes, anio)) {
        return false;
    }
    this->dia = dia;
    return true;
}

bool Fecha::setMes(const int& mes) {
    if (mes < 1 || mes > 12) {
        return false;
    }
    this->mes = mes;
    if (dia > diasDelMes(mes, anio)) {
        dia = diasDelMes(mes, anio);
    }
    return true;
}

bool Fecha::setAnio(const int& anio) {
    if (anio < 0) {
        return false;
    }
    this->anio = anio;
    if (dia > diasDelMes(mes, anio)) {
        dia = diasDelMes(mes, anio);
    }
    return true;
}

string Fecha::toStringDDMM() const {
    ostringstream out;
    out << formatearDosDigitos(dia) << "/" << formatearDosDigitos(mes);
    return out.str();
}

string Fecha::toStringMMAA() const {
    ostringstream out;
    out << formatearDosDigitos(mes) << "/" << (anio % 100);
    return out.str();
}

string Fecha::toStringDDMMAAAA() const {
    ostringstream out;
    out << formatearDosDigitos(dia) << "/" << formatearDosDigitos(mes) << "/" << anio;
    return out.str();
}

string Fecha::toStringAAAAMMDD() const {
    ostringstream out;
    out << anio << formatearDosDigitos(mes) << formatearDosDigitos(dia);
    return out.str();
}

bool Fecha::sumarDias(const int& dias) {
    if (dias < 0) return false;
    int diasRestantes = dias;

    while (diasRestantes > 0) {
        int diasEnMes = diasDelMes(mes, anio) - dia + 1;
        if (diasRestantes < diasEnMes) {
            dia += diasRestantes;
            break;
        }
        diasRestantes -= diasEnMes;
        dia = 1;
        sumarMeses(1);
    }

    return true;
}

bool Fecha::sumarMeses(const int& meses) {
    if (meses < 0) return false;
    int totalMeses = mes + meses - 1;
    anio += totalMeses / 12;
    mes = (totalMeses % 12) + 1;

    if (dia > diasDelMes(mes, anio)) {
        dia = diasDelMes(mes, anio);
    }

    return true;
}

bool Fecha::sumarAnios(const int& anios) {
    if (anios < 0) return false;
    anio += anios;
    if (dia > diasDelMes(mes, anio)) {
        dia = diasDelMes(mes, anio);
    }
    return true;
}

string Fecha::toDebug() const {
    ostringstream debug;
    debug << "Fecha(dia='" << dia << "', mes='" << mes << "', anio='" << anio << "')";
    return debug.str();
}

string Fecha::toSave() const {
    return toStringDDMMAAAA();
}

void Fecha::load(const string& data) {
    istringstream in(data);
    string diaStr, mesStr, anioStr;

    getline(in, diaStr, '/');
    getline(in, mesStr, '/');
    getline(in, anioStr);

    int diaTemp = stoi(diaStr);
    int mesTemp = stoi(mesStr);
    int anioTemp = stoi(anioStr);

    if (!setAnio(anioTemp) || !setMes(mesTemp) || !setDia(diaTemp)) {
        throw runtime_error("Fecha inválida");
    }
}

void Fecha::generateRandom() {
    anio = 2024;
    mes = 1 + (rand() % 12);
    dia = 1 + (rand() % diasDelMes(mes, anio));
}