#pragma once

// Caracteres de serialización para el guardado de datos
namespace Serialization
{
    // Delimitadores para la serialización de datos

    // Delimitador de primer nivel: se utiliza para separar bloques principales de datos
    constexpr char DELIMITER_MAIN = '|'; // Primer nivel: separa bloques principales
    // Delimitador de segundo nivel: se utiliza para separar secciones dentro de un bloque
    constexpr char DELIMITER_SECTION = ';'; // Segundo nivel: separa secciones dentro de un bloque
    // Delimitador de tercer nivel: se utiliza para separar campos dentro de una sección
    constexpr char DELIMITER_FIELD = ':'; // Tercer nivel: separa campos dentro de una sección
    // Delimitador de cuarto nivel: se utiliza para separar detalles más finos dentro de un campo
    constexpr char DELIMITER_DETAIL = '_'; // Cuarto nivel: separa detalles finos dentro de un campo
    // Delimitador de fechas: se utiliza específicamente para fechas
    constexpr char DELIMITER_DATE = '/'; // Delimitador específico para fechas
}