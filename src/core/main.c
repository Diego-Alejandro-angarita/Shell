/**
 * @file main.c
 * @brief Punto de entrada principal del sistema operativo educativo EAFITos.
 *
 * Este archivo contiene la función main(), que es el lugar donde comienza
 * la ejecución del programa. Su única responsabilidad es inicializar el mensaje
 * de bienvenida y ceder el control al bucle principal de la shell.
 */

/* 
 * --- Librerías Estándar ---
 * <stdio.h>: Standard Input/Output. 
 * Provee funcionalidades para operaciones de entrada y salida..
 * En este caso, se usa para la función printf() que imprime texto en la terminal.
 */
#include <stdio.h>

/*
 * --- Cabeceras Propias ---
 * "shell.h": Incluye los prototipos de las funciones principales del núcleo,
 * como loop_shell(), permitiendo que main() conozca su existencia.
 */
#include "shell.h"

//mejora previa a main.c para incluir utils.h y usar funciones de bienvenida y limpieza de pantalla
#include "utils.h"   // Para mostrar_bienvenida() y colores

/**
 * @brief Punto de inicio del sistema EAFITos.
 *
 * @details
 * Inicializa el entorno de ejecución,
 * muestra el banner de bienvenida y
 * transfiere el control al bucle principal (REPL).
 *
 * @return int EXIT_SUCCESS si finaliza correctamente.
 */
int main(void) {

    // Desactiva el buffering de stdout para todo el programa
    setbuf(stdout, NULL); 

// Mostrar banner de bienvenida y mensaje inicial
mostrar_bienvenida();

printf(YEL "Iniciando EAFITos v1.0...\n" RESET);
printf("Escribe " GRN "'ayuda'" RESET " para comenzar.\n\n");

// Transferir control al bucle principal REPL
    loop_shell();

    // Retornamos 0 para indicar una finalización exitosa.
    return 0;
}

