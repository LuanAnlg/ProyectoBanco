#pragma once

#include <string>

using namespace std;

namespace Format {
    // Códigos de reset
    const string RESET = "\033[0m";

    // Colores regulares
    const string BLACK = "\033[0;30m";
    const string RED = "\033[0;31m";
    const string GREEN = "\033[0;32m";
    const string YELLOW = "\033[0;33m";
    const string BLUE = "\033[0;34m";
    const string MAGENTA = "\033[0;35m";
    const string CYAN = "\033[0;36m";
    const string WHITE = "\033[0;37m";

    // Colores brillantes
    const string BRIGHT_BLACK = "\033[1;30m";
    const string BRIGHT_RED = "\033[1;31m";
    const string BRIGHT_GREEN = "\033[1;32m";
    const string BRIGHT_YELLOW = "\033[1;33m";
    const string BRIGHT_BLUE = "\033[1;34m";
    const string BRIGHT_MAGENTA = "\033[1;35m";
    const string BRIGHT_CYAN = "\033[1;36m";
    const string BRIGHT_WHITE = "\033[1;37m";

    // Estilos de texto
    const string BOLD = "\033[1m";
    const string DIM = "\033[2m";
    const string ITALIC = "\033[3m";
    const string UNDERLINE = "\033[4m";
    const string BLINK = "\033[5m";
    const string REVERSE = "\033[7m";
    const string HIDDEN = "\033[8m";

    // Colores de fondo
    const string BG_BLACK = "\033[40m";
    const string BG_RED = "\033[41m";
    const string BG_GREEN = "\033[42m";
    const string BG_YELLOW = "\033[43m";
    const string BG_BLUE = "\033[44m";
    const string BG_MAGENTA = "\033[45m";
    const string BG_CYAN = "\033[46m";
    const string BG_WHITE = "\033[47m";
}