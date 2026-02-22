#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"
#include "utils.h"
#include "shell.h" // <--- 1. IMPORTANTE: Agregar esto para usar leer_linea

/**
 * @brief comando crear <archivo>
 * Crea un archivo vacío con el nombre especificado por el usuario.
 * Si el archivo ya existe, lo sobrescribe (comportamiento similar a 'touch' en Unix).
 * @param args Argumentos del comando, donde args[1] es el nombre del archivo a crear.
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
 * Pide confirmación al usuario antes de eliminar un archivo. Si el usuario confirma, se elimina el archivo especificado.
 * Utiliza leer_linea() para obtener la respuesta del usuario, lo que permite que la shell siga funcionando correctamente en modo raw.
 * @param args Argumentos del comando, donde args[1] es el nombre del archivo a eliminar.
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
 * Renombra un archivo de 'viejo' a 'nuevo'. Si el proceso de renombrado falla, se muestra un mensaje de error.
 * @param args Argumentos del comando, donde args[1] es el nombre actual del archivo y args[2] es el nuevo nombre que se desea asignar.
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
 * Copia el contenido de un archivo de 'origen' a 'destino'. Si el proceso de copia falla, se muestra un mensaje de error.
 * @param args Argumentos del comando, donde args[1] es el nombre del archivo de origen y args[2] es el nombre del archivo de destino.
 */
void cmd_copiar(char **args) {
    if (args[1] == NULL || args[2] == NULL) { 
        printf("Uso:" GRN  "copiar" RESET  " " YEL "<origen> <destino>" RESET "\n");
        return; 
    }
    FILE *src = fopen(args[1], "rb"), *dst = fopen(args[2], "wb"); // Abrimos el archivo de origen en modo lectura binaria y el de destino en modo escritura binaria
    if (!src || !dst) { // Si alguno de los archivos no se pudo abrir, mostramos un mensaje de error y cerramos el que sí se abrió (si es el caso)
        char msg[100];
        snprintf(msg, sizeof(msg), "No se pudo abrir uno de los archivos: '%s' o '%s'.", args[1], args[2]);
        error_eafitos(msg); 
        if(src) fclose(src);
        return;
    } 
    char buffer[1024]; // Buffer para copiar el contenido en bloques de 1KB
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) // fread devuelve el número de bytes leídos, que puede ser menor que sizeof(buffer) en la última lectura
        fwrite(buffer, 1, bytes, dst);
    
    printf("Copia finalizada.\n");
    fclose(src); 
    fclose(dst);
}   