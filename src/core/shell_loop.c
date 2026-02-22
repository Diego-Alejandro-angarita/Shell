/**
 * @file shell_loop.c
 * @brief Implementación del bucle principal y despacho de comandos.
 *
 * @details
 * Este módulo implementa el REPL (Read-Eval-Print Loop)
 * de la shell EAFITos.
 *
 * Funcionalidades principales:
 * - Registro dinámico de comandos.
 * - Búsqueda mediante tabla de punteros a función.
 * - Ejecución y manejo de errores.
 */

/**
 * --- Librerías Estándar ---
 * <stdio.h>: Standard Input/Output.
 * @brief Utilidades generales para la shell EAFITos. 
 * Contiene funciones de manejo de errores, limpieza de pantalla y presentación.
* Estas funciones son auxiliares para mejorar la experiencia del usuario y la interfaz de la shell.
 */     
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "commands.h"
#include "utils.h"


/**
 * @brief Idioma activo de la shell.
 * @details Se inicializa en ESPANOL por defecto.
 */
Idioma idioma_actual = ESPANOL; // Valor por defecto

/*
 * --- Registro de Comandos ---
 * Para evitar una larga cadena de 'if-else if-else', usamos dos arreglos paralelos:
 * 1. nombres_comandos: Lista de cadenas con los nombres reconocidos.
 * 2. func_comandos: Lista de punteros a funciones correspondientes.
 *
 * Esto facilita la extensibilidad: para añadir un comando, solo se agregan entradas aquí.
 */

/**
 * @brief Lista de nombres de comandos soportados por la shell.
 */
char *nombres_comandos[] = {
    "idioma",
    "listar",
    "leer",
    "limpiar",
    "tiempo",
    "calc",
    "ayuda",
    "crear",
    "eliminar",
    "renombrar",
    "copiar",
    "salir"
};

/*
 * Puntero a función: void (*func)(char **)
 * Significa: "La dirección de una función que no retorna nada (void)
 * y recibe como parámetro un arreglo de cadenas (char **)".
 */

/**
 * @brief Tabla paralela de punteros a funciones asociadas a cada comando.
 *
 * Cada índice corresponde al mismo índice en nombres_comandos[].
 */
void (*func_comandos[]) (char **) = {
    &cmd_idioma,
    &cmd_listar,
    &cmd_leer,
    &cmd_limpiar,
    &cmd_tiempo,
    &cmd_calc,
    &cmd_ayuda,
    &cmd_crear,
    &cmd_eliminar,
    &cmd_renombrar,
    &cmd_copiar,
    &cmd_salir
};

/**
 * @brief Calcula dinámicamente cuántos comandos hay registrados.
 * 
 * @return int El número de comandos (tamaño del array / tamaño de un elemento ptr).
 */
int num_comandos() {
    return sizeof(nombres_comandos) / sizeof(char *);
}

/**
 * @brief Busca y ejecuta el comando solicitado por el usuario.
 * 
 * @param args Lista de argumentos parseados. args[0] es el nombre del comando.
 */
void ejecutar(char **args) {
    if (args[0] == NULL) {
        // El usuario presionó Enter sin escribir nada.
        return; 
    }

    // Recorremos el registro de comandos buscando una coincidencia.
    for (int i = 0; i < num_comandos(); i++) {
        // strcmp: Retorna 0 si dos cadenas son idénticas.
        if (strcmp(args[0], nombres_comandos[i]) == 0) {
            // ¡Coincidencia encontrada! Llamamos a la función a través del puntero.
            (*func_comandos[i])(args);
            return;
        }
    }


    /**
     * @brief  
     *  Usamos snprintf para evitar desbordamientos de buffer, limitando el tamaño del mensaje a 128 caracteres.
     *  Luego, llamamos a error_eafitos() para imprimir el mensaje en rojo
     */
    char msg_error[128]; 
    snprintf(msg_error, sizeof(msg_error), "Comando '%s' no reconocido.", args[0]);
    
    // USAMOS LA FUNCIÓN DE UTILS.H
    error_eafitos(msg_error);  
    printf("Escribe " GRN "'ayuda'" RESET " para ver los comandos disponibles.\n");
}


/**
 * @brief Bucle principal Read-Eval-Print Loop (REPL).
 * 
 * Ciclo de vida:
 * 1. Read: Muestra el prompt "EAFITos>" y lee la entrada.
 * 2. Parse (Eval implícito): Divide la entrada en argumentos.
 * 3. Execute: Busca y corre el comando.
 * 4. Loop: Repite o libera memoria.
 */
void loop_shell() {
    char *linea;   // Almacenará la línea cruda
    char **args;   // Almacenará los tokens
    int status = 1; // Variable de control del bucle

    do {
        // Mostrar el prompt con colores
        printf(CYN "[" GRN "EAFITos" CYN "] " YEL "➜  " RESET);
        
        // 1. Lectura
        linea = leer_linea();
        
        // 2. Parseo
        args = parsear_linea(linea);
        

        ejecutar(args);
        
        // 4. Limpieza de memoria (Gestión manual requerida en C)
        free(linea); // Libera el buffer de getline
        free(args);  // Libera el arreglo de punteros (nota: no los strings individuales si son punteros a 'linea')
        
    } while (status); // Por ahora el loop es infinito hasta que cmd_salir hace exit(0)
}


