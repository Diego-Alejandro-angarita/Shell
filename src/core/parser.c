/**
 * @file parser.c
 * @brief Módulo encargado de interpretar la entrada del usuario con soporte para historial.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // read, write
#include <termios.h>    // Configuración de terminal (modo raw)
#include <ctype.h>      // iscntrl

#include "shell.h"
#include "utils.h"

// --- Configuración del Historial ---
#define HISTORY_MAX 50      // Guardamos los últimos 50 comandos
#define CMD_MAX_LEN 1024    // Longitud máxima de comando

static struct termios orig_termios;
static char historial[HISTORY_MAX][CMD_MAX_LEN];
static int historial_count = 0;

/**
 * @brief Restaura la configuración original de la terminal.
 */
void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

/**
 * @brief Activa el modo Raw para leer tecla a tecla.
 * Desactiva ECHO (nosotros imprimimos los caracteres manualmente)
 * y ICANON (para no esperar al Enter).
 */
void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode); // Asegurar que se restaure al salir
    
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON); // Desactivar eco y modo canónico
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/**
 * @brief Guarda un comando en el array de historial interno.
 */
void agregar_al_historial(const char *cmd) {
    // No guardar líneas vacías o duplicados consecutivos
    if (cmd == NULL || strlen(cmd) == 0) return;
    if (historial_count > 0 && strcmp(historial[historial_count - 1], cmd) == 0) return;

    if (historial_count < HISTORY_MAX) {
        strncpy(historial[historial_count], cmd, CMD_MAX_LEN);
        historial_count++;
    } else {
        // Si está lleno, desplazamos todo a la izquierda (FIFO)
        for (int i = 0; i < HISTORY_MAX - 1; i++) {
            strcpy(historial[i], historial[i+1]);
        }
        strncpy(historial[HISTORY_MAX - 1], cmd, CMD_MAX_LEN);
    }
}

/**
 * @brief Lee la línea del usuario gestionando flechas y backspace.
 * Reemplaza al 'getline' estándar.
 */
char *leer_linea(void) {
    enable_raw_mode(); // 1. Entrar en modo Raw

    char *buffer = malloc(CMD_MAX_LEN);
    memset(buffer, 0, CMD_MAX_LEN);
    
    int pos = 0; // Posición del cursor en el buffer
    int history_index = historial_count; // Índice actual del historial (comienza al final)
    char c;

    while (1) {
        // Leer un solo byte
        if (read(STDIN_FILENO, &c, 1) == -1) break;

        if (c == '\n') { // 2. Usuario presionó ENTER
            buffer[pos] = '\0';
            printf("\n"); // Salto de línea visual
            break;

        } else if (c == 127) { // 3. Usuario presionó BACKSPACE (ASCII 127)
            if (pos > 0) {
                pos--;
                buffer[pos] = '\0';
                // Borrado visual: retroceder, espacio, retroceder
                printf("\b \b"); 
            }

        } else if (c == '\x1b') { // 4. Secuencia de Escape (Flechas)
            char seq[3];
            // Leemos los siguientes 2 bytes para ver qué flecha es ([A o [B)
            if (read(STDIN_FILENO, &seq[0], 1) == -1) break;
            if (read(STDIN_FILENO, &seq[1], 1) == -1) break;

            if (seq[0] == '[') {
                if (seq[1] == 'A') { // --- FLECHA ARRIBA ---
                    if (history_index > 0) {
                        history_index--;
                        // Borrar visualmente la línea actual
                        while (pos > 0) {
                            printf("\b \b");
                            pos--;
                        }
                        // Copiar del historial al buffer
                        strcpy(buffer, historial[history_index]);
                        pos = strlen(buffer);
                        printf("%s", buffer); // Mostrar nuevo comando
                    }
                } else if (seq[1] == 'B') { // --- FLECHA ABAJO ---
                    if (history_index < historial_count) {
                        history_index++;
                        // Borrar visualmente
                        while (pos > 0) {
                            printf("\b \b");
                            pos--;
                        }
                        
                        if (history_index < historial_count) {
                            // Mostrar comando más reciente
                            strcpy(buffer, historial[history_index]);
                        } else {
                            // Estamos al final, línea vacía
                            buffer[0] = '\0';
                        }
                        pos = strlen(buffer);
                        printf("%s", buffer);
                    }
                }
            }
        } else if (!iscntrl(c)) { // 5. Caracter normal (letras, números)
            if (pos < CMD_MAX_LEN - 1) {
                buffer[pos++] = c;
                printf("%c", c); // Hacemos 'echo' manual del caracter
            }
        }
    }

    disable_raw_mode(); // 6. Restaurar terminal normal
    
    // Guardar lo que se acaba de escribir en el historial
    if (pos > 0) {
        agregar_al_historial(buffer);
    }
    
    return buffer;
}

// ... (Mantén aquí la función parsear_linea original sin cambios) ...
char **parsear_linea(char *linea) {
    int bufsize = 64;
    int posicion = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        error_eafitos("Fallo crítico: No se pudo asignar memoria para tokens.");
        exit(EXIT_FAILURE);
    }

    token = strtok(linea, DELIM);
    while (token != NULL) {
        tokens[posicion] = token;
        posicion++;

        if (posicion >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Error de reasignación de memoria\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, DELIM);
    }
    tokens[posicion] = NULL;
    return tokens;
}