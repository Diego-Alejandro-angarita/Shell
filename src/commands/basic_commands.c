/**
 * @file basic_commands.c
 * @brief Implementación de comandos básicos del sistema.
 */

#include <stdio.h>  // printf
#include <stdlib.h> // exit, malloc
#include <time.h>   // time, localtime, strftime
#include "commands.h"
#include "utils.h"  // Para funciones de utilidad como error_eafitos

/* * Referencia externa al idioma global definido en shell_loop.c 
 * 1: Español, 2: Inglés 
 */
extern int idioma_actual;

/**
 * @brief Comando AYUDA
 * * Muestra al usuario la lista de acciones que puede realizar.
 * Se adapta al idioma actual configurado en la shell.
 * * @param args Argumentos del comando (no se usan aquí).
 */
void cmd_ayuda(char **args) {

    if (idioma_actual == 1) {
        // --- VERSIÓN EN ESPAÑOL ---
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
        printf("  - " GRN "idioma" RESET " " YEL "<1/2>" RESET " : Cambia el idioma (1: ES, 2: EN).\n");
        printf("  - " GRN "salir" RESET " : Termina la sesión.\n");
    } 
    else {
        // --- VERSIÓN EN INGLÉS ---
        printf(CYN "\n---  EAFITos Help Panel ---" RESET "\n");
        printf("List of available commands:\n\n");

        printf("  - " GRN "listar" RESET " List files in the current directory.\n");
        printf("  - " GRN "leer" RESET " " YEL "<file>" RESET " : Display the content of a file.\n");
        printf("  - " GRN "tiempo" RESET " : Show the current date and time.\n");
        printf("  - " GRN "calc" RESET "" YEL " <n1> <op> <n2>" RESET " : Perform simple calculations.\n");
        printf("  - " GRN "ayuda" RESET " : Display this help message.\n");
        printf("  - " GRN "crear" RESET " " YEL "<file>" RESET " : Create an empty file.\n");
        printf("  - " GRN "eliminar" RESET " " YEL "<file>" RESET " : Delete a file with confirmation.\n");
        printf("  - " GRN "renombrar" RESET " " YEL "<old> <new>" RESET " : Change a file's name.\n");
        printf("  - " GRN "copiar" RESET " " YEL "<src> <dst>" RESET " : Copy content from one file to another.\n");
        printf("  - " GRN "idioma" RESET " " YEL "<2/2>" RESET " : Change language (1: ES, 2: EN).\n");
        printf("  - " GRN "salir" RESET " : Terminate the session.\n");
    }
    
    (void)args;
}



/**
 * @brief Comando SALIR
 * * Finaliza la ejecución del programa de forma controlada.
 */
void cmd_salir(char **args) {
    if (idioma_actual == 1) {
        printf(YEL "Cerrando sesión en EAFITos... ¡Hasta pronto!\n" RESET);
    } else {
        printf(YEL "Closing EAFITos session... See you soon!\n" RESET);
    }
    exit(0);
    (void)args;
}

/**
 * @brief Comando TIEMPO (date)
 * * Obtiene y formatea la fecha y hora del sistema.
 */
void cmd_tiempo(char **args) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    if (idioma_actual == 1) {
        printf(GRN " Fecha y Hora: " RESET "%02d-%02d-%04d %02d:%02d:%02d\n",
               tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
               tm.tm_hour, tm.tm_min, tm.tm_sec); 
    } else {
        printf(GRN " Date and Time: " RESET "%04d/%02d/%02d %02d:%02d:%02d\n",
               tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
               tm.tm_hour, tm.tm_min, tm.tm_sec); 
    }
           
    (void)args;
}

//Actualizacion repositorio