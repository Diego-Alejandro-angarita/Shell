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
 * @brief Función principal del programa.
 * 
 * En C, la ejecución siempre comienza en la función main.
 * 
 * @return int Retorna 0 al sistema operativo para indicar que el programa
 *         terminó correctamente (EXIT_SUCCESS).
 */
int main() {

    // Desactiva el buffering de stdout para todo el programa
    setbuf(stdout, NULL); 

/**
 * @brief Construct a new mostrar bienvenida object
 * Esta sección se encarga de mostrar un mensaje de bienvenida al usuario al iniciar la shell.
 * Se implementan las siguientes mejoras para una experiencia de usuario más atractiva:
 * 1. Limpieza de Pantalla: Antes de mostrar cualquier mensaje, se limpia la pantalla para ofrecer una interfaz limpia y profesional.
 * 2. Mensaje de Bienvenida: Se muestra un banner de bienvenida estilizado utilizando colores ANSI para mejorar la experiencia del usuario.
 * 3. Información Adicional: Se imprime un mensaje adicional indicando la versión de EAFITos y una sugerencia para comenzar a usar la shell.
 */
    mostrar_bienvenida(); // Definida en utils.h

    printf(YEL "Iniciando EAFITos v1.0...\n" RESET);
    printf("Escribe " GRN "'ayuda'" RESET " para comenzar.\n\n");


/**
 * @brief Construct a new loop shell object
 * Después de mostrar la bienvenida, se llama a loop_shell(), que es el bucle principal de la shell.
 * Este bucle se encarga de:
 * 1. Mostrar el prompt "EAFITos>".
 * 2. Leer la entrada del usuario.
 * 3. Parsear la entrada en comandos y argumentos.
 * 4. Ejecutar el comando correspondiente.
 * 5. Repetir el proceso hasta que el usuario decida salir.
 */
    loop_shell();

    // Retornamos 0 para indicar una finalización exitosa.
    return 0;
}

