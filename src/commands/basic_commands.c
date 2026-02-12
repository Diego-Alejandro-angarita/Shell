/**
 * @file basic_commands.c
 * @brief Implementación de comandos básicos del sistema.
 */

#include <stdio.h>  // printf
#include <stdlib.h> // exit, malloc
#include <time.h>   // time, localtime, strftime
#include "commands.h"
#include "utils.h"  // Para funciones de utilidad como error_eafitos

/**
 * @brief Comando AYUDA
 * 
 * Muestra al usuario la lista de acciones que puede realizar.
 * Es fundamental para la usabilidad de la shell.
 * 
 * @param args Argumentos del comando (no se usan aquí, por eso (void)args).
 */
void cmd_ayuda(char **args) {

    printf(CYN "\n---  Panel de Ayuda EAFITos ---" RESET "\n");
    printf("Lista de comandos disponibles:\n\n");

    printf("  - " GRN "listar" RESET " Muestra archivos del directorio.\n");
    printf("  - " GRN "leer" RESET " " YEL "<archivo>" RESET " : Muestra el contenido de un archivo.\n");
    printf("  - " GRN "tiempo" RESET " : Muestra la fecha y hora actual.\n");
    printf("  - " GRN "calc" RESET "" YEL " <n1> <op> <n2>" RESET " : Realiza cálculos simples.\n");
    printf("  - " GRN "ayuda" RESET " : Muestra este mensaje.\n");
    printf("  - " GRN "crear" RESET " " YEL "<archivo>" RESET " : Crea un archivo vacío.\n");
    printf("  - " GRN "eliminar" RESET " " YEL "<archivo>" RESET " : Borra un archivo con confirmación.\n");
    printf("  - " GRN "renombrar" RESET " " YEL "<viejo> <nuevo>" RESET " : Cambia el nombre de un archivo.\n");
    printf("  - " GRN "copiar" RESET " " YEL "<origen> <destino>" RESET " : Copia el contenido de un archivo.\n");
    printf("  - " GRN "salir" RESET " : Termina la sesión.\n");
    
    // Silenciar advertencia de compilador sobre variable no usada
    (void)args;
}

/**
 * @brief Comando SALIR
 * 
 * Finaliza la ejecución del programa de forma controlada.
 * Utiliza la llamada al sistema exit().
 * 
 * @param args Argumentos del comando (ignorados).
 */
void cmd_salir(char **args) {
    printf(YEL "Cerrando sesión en EAFITos... ¡Hasta pronto!\n" RESET);
    // exit(0) devuelve el código 0 al sistema operativo padre,
    // indicando que el proceso terminó sin errores.
    exit(0);
    (void)args;
}

/**
 * @brief Comando TIEMPO (date)
 * 
 * Obtiene y formatea la fecha y hora del sistema.
 * Demuestra el uso de la librería estándar <time.h>.
 * 
 * @param args Argumentos del comando (ignorados).
 */
void cmd_tiempo(char **args) {
    // 1. Obtener tiempo "crudo" (segundos desde 1970 - Epoch Unix)
    time_t t = time(NULL);
    
    // 2. Convertir a una estructura estructurada local (struct tm)
    // localtime devuelve un puntero, así que desreferenciamos con *
    struct tm tm = *localtime(&t);
    
    // 3. Imprimir con formato
    // tm_year cuenta desde 1900, por eso sumamos 1900.
    // tm_mon es 0-11, por eso sumamos 1.

    printf(GRN " Fecha y Hora: " RESET "%02d-%02d-%04d %02d:%02d:%02d\n",
           tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
           tm.tm_hour, tm.tm_min, tm.tm_sec); 
           
    (void)args;
}

//Actualizacion repositorio