#pragma once

// Caracteres de serializaci�n para el guardado de datos
namespace Serialization
{
    // Delimitadores para la serializaci�n de datos

    // Delimitador de primer nivel: se utiliza para separar bloques principales de datos
    constexpr char DELIMITER_MAIN = '|'; // Primer nivel: separa bloques principales
    // Delimitador de segundo nivel: se utiliza para separar secciones dentro de un bloque
    constexpr char DELIMITER_SECTION = ';'; // Segundo nivel: separa secciones dentro de un bloque
    // Delimitador de tercer nivel: se utiliza para separar campos dentro de una secci�n
    constexpr char DELIMITER_FIELD = ':'; // Tercer nivel: separa campos dentro de una secci�n
    // Delimitador de cuarto nivel: se utiliza para separar detalles m�s finos dentro de un campo
    constexpr char DELIMITER_DETAIL = '_'; // Cuarto nivel: separa detalles finos dentro de un campo
    // Delimitador de fechas: se utiliza espec�ficamente para fechas
    constexpr char DELIMITER_DATE = '/'; // Delimitador espec�fico para fechas
}