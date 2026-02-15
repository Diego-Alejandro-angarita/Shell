#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"
#include "utils.h"
#include "shell.h" // <--- 1. IMPORTANTE: Agregar esto para usar leer_linea

/**
 * @brief comando crear <archivo>
 */
void cmd_crear(char **args) {
    if (args[1] == NULL) {
        printf("Uso:" GRN  "crear" RESET " " YEL "<nombre>" RESET "\n");
        return; 
    }
    FILE *fp = fopen(args[1], "w");
    if (fp) { 
        printf("Archivo '%s' creado.\n", args[1]);
        fclose(fp); 
    } else {
        char msg[100];
        snprintf(msg, sizeof(msg), "No se pudo crear el archivo '%s'.", args[1]);
        error_eafitos(msg);
    }
}

/**
 * @brief comando eliminar <archivo>
 */
void cmd_eliminar(char **args) {
    if (args[1] == NULL) { 
        printf("Uso:" GRN  "eliminar" RESET  " " YEL "<nombre>" RESET "\n");
        return; 
    }

    // --- 2. CAMBIO DE LÓGICA DE LECTURA ---
    printf("¿Eliminar %s? (s/n): ", args[1]);
    fflush(stdout); // Asegurar que el mensaje salga antes de pedir entrada

    // Usamos leer_linea() para ser consistentes con el modo raw de la shell
    char *respuesta = leer_linea();

    if (strcmp(respuesta, "s") == 0 || strcmp(respuesta, "S") == 0) { 
        if (remove(args[1]) == 0) 
            printf("Eliminado.\n");
        else {
            char msg[100];
            snprintf(msg, sizeof(msg), "No se pudo eliminar el archivo '%s'.", args[1]);
            error_eafitos(msg);
        }
    } else {
        printf("Operación cancelada.\n");
    }

    free(respuesta); // Importante: liberar la memoria de leer_linea
}

/**
 * @brief comando renombrar <viejo> <nuevo>
 */
void cmd_renombrar(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        printf("Uso:" GRN  "renombrar" RESET  " " YEL "<viejo> <nuevo>" RESET "\n"); 
        return;
    } 
    if (rename(args[1], args[2]) == 0) 
        printf("Renombrado con éxito.\n");
    else {
        char msg[100];
        snprintf(msg, sizeof(msg), "No se pudo renombrar '%s' a '%s'.", args[1], args[2]);
        error_eafitos(msg);
    }
}

/**
 * @brief comando copiar <origen> <destino>
 */
void cmd_copiar(char **args) {
    if (args[1] == NULL || args[2] == NULL) { 
        printf("Uso:" GRN  "copiar" RESET  " " YEL "<origen> <destino>" RESET "\n");
        return; 
    }
    FILE *src = fopen(args[1], "rb"), *dst = fopen(args[2], "wb");
    if (!src || !dst) {
        char msg[100];
        snprintf(msg, sizeof(msg), "No se pudo abrir uno de los archivos: '%s' o '%s'.", args[1], args[2]);
        error_eafitos(msg); 
        if(src) fclose(src);
        return;
    } 
    char buffer[1024]; 
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) 
        fwrite(buffer, 1, bytes, dst);
    
    printf("Copia finalizada.\n");
    fclose(src); 
    fclose(dst);
}   