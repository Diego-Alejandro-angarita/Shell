/**
 * @file error_handler.c
 * @brief Manejo de errores en la shell y utilidades visuales.
 *
  * @details
 * Este archivo centraliza el manejo de errores y funciones
 * visuales de la shell EAFITos.
 *
 * Proporciona:
 * - Impresión de errores en stderr con formato ANSI.
 * - Limpieza de pantalla.
 * - Banner de bienvenida estilizado.
 */


/* 
 * --- Librerías Estándar ---
 * <stdio.h>: Standard Input/Output. 
 * Provee funcionalidades para operaciones de entrada y salida..
 * En este caso, se usa para la función printf() que imprime texto en la terminal.
 */
#include <stdio.h>

/* 
 * <stdlib.h>: Standard Library. 
 * Provee funciones para manejo de memoria, procesos, conversiones, etc.
 * En este caso, se incluye para futuras funciones relacionadas con manejo de errores que puedan necesitar exit() o malloc().
 */
#include <stdlib.h>

/* 
 * --- Cabeceras Propias ---
 * "utils.h": Incluye los prototipos de las funciones de utilidad, como error_eafitos(), limpiar_pantalla() y mostrar_bienvenida().
 * Esto permite que este archivo conozca la existencia de estas funciones y pueda usarlas o implementarlas.
 */
#include "../../include/utils.h"


/**
 * @brief Imprime un mensaje de error formateado en rojo.
 * 
 * @param mensaje El mensaje de error a imprimir.
 */
void error_eafitos(const char *mensaje) {
    // Usamos fprintf para dirigir el error al flujo de error estándar (stderr)
    fprintf(stderr, RED " [Error]: " RESET "%s\n", mensaje);
}

/**
 * @brief Limpia la pantalla de la terminal.
 * Utiliza códigos de escape ANSI para limpiar la pantalla y posicionar el cursor en la esquina superior izquierda (0,0).
 * Esto mejora la experiencia del usuario al proporcionar un entorno despejado.
 *  
 */
void limpiar_pantalla() {
    // \033[H  -> Mueve el cursor al inicio (Home)
    // \033[2J -> Limpia la pantalla visible
    // \033[3J -> Borra el historial de scroll (scrollback buffer)
    printf("\033[H\033[2J\033[3J");
}




/**
 * @brief Muestra un banner de bienvenida con colores.
 *  Esta función imprime un mensaje de bienvenida estilizado utilizando colores ANSI para mejorar la experiencia del usuario al iniciar la shell.
 */
void mostrar_bienvenida() {


    // Limpia la pantalla y coloca el cursor arriba
limpiar_pantalla();

    // Banner en ASCII Art centrado
    printf(CYN "  ____________________________________________________________\n");
    printf("  ||                                                        ||\n");
    // Fíjate cómo insertamos YEL antes de la parte final de cada línea
    printf("  ||  " GRN "  ______          ______ _____ _______ " YEL "            " CYN "   ||\n");
    printf("  ||  " GRN " |  ____|   /\\   |  ____|_   _|__   __|" YEL "            " CYN "   ||\n");
    printf("  ||  " GRN " | |__     /  \\  | |__    | |    | |  " YEL "___  ___    " CYN "    ||\n");
    printf("  ||  " GRN " |  __|   / /\\ \\ |  __|   | |    | | " YEL "/ _ \\/ __|   " CYN "    ||\n");
    printf("  ||  " GRN " | |____ / ____ \\| |     _| |_   | |" YEL "| (_) \\__ \\   " CYN "    ||\n");
    printf("  ||  " GRN " |______/_/    \\_\\_|    |_____|  |_|" YEL " \\___/|___/   " CYN "    ||\n");
    printf("  ||                                                        ||\n");
    printf("  ____________________________________________________________\n" RESET);
}

