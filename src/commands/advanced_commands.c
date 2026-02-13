#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"
#include "utils.h"  // Para funciones de utilidad como error_eafitos


/**
 * @brief comando crear <archivo>
 *  Crea un archivo vacío con el nombre especificado por el usuario.
 *  Si el archivo ya existe, se sobrescribe sin advertencia.
 *  Utiliza fopen() con el modo "w" para crear o truncar el archivo
 * @param args Argumentos del comando (args[1] es el nombre del archivo a crear).
 * 
 */

void cmd_crear(char **args) {
    if (args[1] == NULL) { // Verificar que se proporcionó un nombre de archivo
        printf("Uso:" GRN  "crear" RESET " " YEL "<nombre>" RESET "\n");
        return; 
    }
    FILE *fp = fopen(args[1], "w"); // "w" crea o trunca el archivo, "a" solo crea si no existe
    if (fp) { printf( "Archivo '%s' creado.\n", args[1]);
        fclose(fp); } // Cerrar el archivo después de crearlo
    else {
    char msg[100];
        snprintf(msg, sizeof(msg), "No se pudo crear el archivo '%s'.", args[1]);
        error_eafitos(msg);
    }
}

/**
 * @brief  comando eliminar <archivo>
 *  Elimina un archivo especificado por el usuario después de una confirmación.
 *  Utiliza remove() para eliminar el archivo del sistema de archivos.
 *  Si el usuario confirma, se intenta eliminar el archivo y se muestra un mensaje de éxito o error.
 * @param args Argumentos del comando (args[1] es el nombre del archivo a eliminar).
 */

void cmd_eliminar(char **args) {
    if (args[1] == NULL) { printf( "Uso:" GRN  "eliminar" RESET  " " YEL "<nombre>" RESET "\n");
        return; 
    }
    char conf[10];
    printf("¿Eliminar %s? (s/n): ", args[1]);
    scanf("%s", conf); getchar(); // Limpiar el buffer de entrada
    if (strcmp(conf, "s") == 0 || strcmp(conf, "S") == 0) { // Confirmación positiva
        if (remove(args[1]) == 0) 
        printf(  "Eliminado.\n"  );
        else {
        char msg[100];
        snprintf(msg, sizeof(msg), "No se pudo eliminar el archivo '%s'.", args[1]);
        error_eafitos(msg);
        }
    }
}

/**
 * @brief comando renombrar <viejo> <nuevo>
 *  Cambia el nombre de un archivo existente a uno nuevo especificado por el usuario.
 *  Utiliza rename() para realizar la operación de renombrado en el sistema de archivos.
 * @param args Argumentos del comando (args[1] es el nombre actual del archivo, args[2] es el nuevo nombre).
 *  Si el comando no se usa correctamente (falta alguno de los nombres), se muestra un mensaje de uso.
 *  Si el renombrado es exitoso, se muestra un mensaje de éxito; de lo contrario, se muestra un mensaje de error detallado
 */

void cmd_renombrar(char **args) {
    if (args[1] == NULL || args[2] == NULL) { // Verificar que se proporcionaron ambos nombres de archivo
    printf("Uso:" GRN  "renombrar" RESET  " " YEL "<viejo> <nuevo>" RESET "\n"); 
    return;
    } 
    if (rename(args[1], args[2]) == 0) printf("Renombrado con éxito.\n"); // rename() devuelve 0 si tuvo éxito
    else {
        char msg[100];
        snprintf(msg, sizeof(msg), "No se pudo renombrar '%s' a '%s'.", args[1], args[2]);
        error_eafitos(msg);
    }
}

/**
 * @brief comando copiar <origen> <destino>
 *  Copia un archivo de origen a destino.
 * Utiliza fopen() para abrir ambos archivos (origen en modo lectura "rb" y destino en modo escritura "wb").
 * @param args  Argumentos del comando (args[1] es el archivo de origen, args[2] es el archivo de destino).
 * Si no se proporcionan ambos nombres de archivo, se muestra un mensaje de uso.
 */
void cmd_copiar(char **args) {
    if (args[1] == NULL || args[2] == NULL) { 
        printf("Uso:" GRN  "copiar" RESET  " " YEL "<origen> <destino>" RESET "\n");
        return; 
    }
    FILE *src = fopen(args[1], "rb"), *dst = fopen(args[2], "wb"); // "rb" para leer en modo binario, "wb" para escribir en modo binario
    if (!src || !dst) { // Verificar que ambos archivos se abrieron correctamente
        char msg[100];
        snprintf(msg, sizeof(msg), "No se pudo abrir uno de los archivos: '%s' o '%s'.", args[1], args[2]);
        error_eafitos(msg); 
        if(src) fclose(src);
        return; // Si el archivo de destino no se pudo abrir, cerramos el archivo de origen si se abrió correctamente 
    } 
    char buffer[1024]; size_t bytes; // Buffer para copiar datos en bloques de 1KB
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) fwrite(buffer, 1, bytes, dst);
    printf("Copia finalizada.\n"); // Informar al usuario que la copia se ha completado
    fclose(src); fclose(dst); // Cerrar ambos archivos después de la operación

}