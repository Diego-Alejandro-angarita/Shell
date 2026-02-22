/**
 * @file file_commands.c
 * @brief Comandos para manipulación y visualización de archivos.
 *
 * @details
 * Implementa funcionalidades similares a los comandos
 * Unix 'ls' y 'cat', utilizando la API POSIX
 * para interacción con el sistema de archivos.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // Librería POSIX para manejo de directorios
#include "commands.h"
#include "utils.h" // Para funciones auxiliares como trim_whitespace

/**
 * @brief Comando LISTAR (ls)
 * 
 * Abre el directorio actual (".") e itera sobre sus entradas para mostrar los nombres.
 * 
 * @param args Argumentos del comando (ignorados en esta versión simple).
 */
void cmd_listar(char **args) {
    DIR *d;               // Puntero al flujo del directorio
    struct dirent *dir;   // Estructura que representa una entrada (archivo/carpeta)

    // opendir(): Abre un flujo de directorio correspondiente al directorio dado.
    d = opendir(".");
    
    if (d) {
        // printf(): Imprime un encabezado para la lista de archivos, usando colores para mejorar la legibilidad.
        printf(CYN "\n--- Archivos en el directorio actual ---\n" RESET);
        // readdir(): Lee la siguiente entrada del directorio. Retorna NULL al final.
        while ((dir = readdir(d)) != NULL) {
            // Filtramos las entradas especiales "." (actual) y ".." (padre) para limpiar la salida
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                printf("  %s\n", dir->d_name);
            }
        }
        // closedir(): Cierra el flujo y libera recursos asociados.
        closedir(d);
    } else {
        // perror(): Imprime un mensaje de error descriptivo basado en el valor global 'errno'
        error_eafitos("No se pudo acceder al directorio actual.");
        perror("Detalle");
    }
    (void)args;
}

/**
 * @brief Comando LEER (cat)
 * 
 * Abre un archivo en modo lectura, lee su contenido caracter por caracter
 * y lo imprime en la terminal.
 * 
 * @param args args[1] debe contener la ruta o nombre del archivo a leer.
 */
void cmd_leer(char **args) {
    // Validación básica: ¿El usuario pasó el nombre del archivo?
    if (args[1] == NULL) {
        error_eafitos("Falta el nombre del archivo.");
        printf("  Uso: " YEL "leer <nombre_archivo>" RESET "\n");
        return;
    }

    // fopen(): Abre el archivo especificado en modo lectura ("r").
    // Retorna un puntero a FILE o NULL si falla (ej. archivo no existe).
    FILE *fp = fopen(args[1], "r");
    if (fp == NULL) {
        // Construimos un mensaje de error específico para el archivo que no se pudo abrir.
        char msg[128];
        snprintf(msg, sizeof(msg), "No se pudo abrir el archivo '%s'.", args[1]);
        error_eafitos(msg);
        
        return;
    }

    // Título estético antes de mostrar contenido
    printf(YEL "[ Contenido de: %s ]\n" RESET, args[1]);
    printf("------------------------------------------\n");

    char ch;
    // fgetc(): Lee el siguiente caracter del flujo.
    // El bucle continúa hasta encontrar EOF (End Of File).
    while ((ch = fgetc(fp)) != EOF) {
        // putchar(): Escribe un caracter en la salida estándar (consola).
        putchar(ch);
    }
    printf("\n------------------------------------------\n\n"); // Salto de línea estético al final

    // fclose(): Es crítico cerrar los archivos para evitar fugas de recursos.
    fclose(fp);
}
