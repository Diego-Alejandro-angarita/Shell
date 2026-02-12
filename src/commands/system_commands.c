/**
 * @file system_commands.c
 * @brief Comandos de utilería del sistema.
 * 
 * Actualmente contiene la calculadora, pero podría expandirse para incluir
 * gestión de procesos o informes de memoria.
 */


#include <stdio.h>
#include <stdlib.h> // Para atof (ASCII to Float conversion)
#include "commands.h"
#include "utils.h" 


/**
 * @brief  Comando LIMPIAR
 * 
 * Limpia la pantalla de la terminal y muestra el banner de bienvenida.
 * Esto mejora la experiencia del usuario al proporcionar un entorno despejado.
 * @param args Argumentos del comando (no se usan aquí, por eso (void)args).
 */
void cmd_limpiar(char **args) {
    limpiar_pantalla();    // Ahora con \033[3J para borrar el scroll
      // Reaparece tu logo centrado
    cmd_ayuda(args);       // Muestra el menú de comandos
    
}




/**
 * @brief Comando CALC (Calculadora)
 * 
 * Realiza operaciones aritméticas básicas entre dos números.
 * Sintaxis esperada: calc <num1> <operador> <num2>
 * 
 * @param args Lista de argumentos donde:
 *             args[1]: Primer operando (cadena)
 *             args[2]: Operador (+, -, *, /)
 *             args[3]: Segundo operando (cadena)
 */

void cmd_calc(char **args) {
    // 1. Validación de argumentos. Necesitamos exáctamente 3 partes después del comando.
    if (args[1] == NULL || args[2] == NULL || args[3] == NULL) {
       error_eafitos("Faltan parámetros para la operación.");  // Llamada a función de error personalizada
        printf("  Uso: " YEL "calc <num1> <operador> <num2>" RESET "\n"); // Mensaje de ayuda específico para este comando
        printf("  Ejemplo: calc 5 + 3\n");
        return;
    }

    // 2. Conversión de tipos (Parsing)
    // atof(): Convierte una cadena numérica a un float (double precision).
    float n1 = atof(args[1]);
    char op = args[2][0]; // Tomamos el primer caracter del argumento operador
    float n2 = atof(args[3]);
    float res = 0;

    // 3. Lógica de selección (Switch)
    switch(op) {
        case '+': 
            res = n1 + n2; 
            break;
        case '-': 
            res = n1 - n2; 
            break;
        case '*': 
        case 'x': // Permitimos 'x' como alias de multiplicación
            res = n1 * n2; 
            break;
        case '/': 
            // Manejo de caso borde: División por cero
            if (n2 == 0) {
                error_eafitos("Operación inválida: División por cero.");
                return;
            }
            res = n1 / n2; 
            break;
        default: 

        /**
         * @brief  Manejo de operador desconocido
         *  Si el usuario ingresa un operador que no reconocemos, mostramos un error específico.
         *   sprintf() se utiliza para construir un mensaje de error dinámico que incluye el operador no reconocido.
         *   Esto mejora la experiencia del usuario al proporcionar información clara sobre lo que salió mal.
         *  msg es un buffer de 50 caracteres, lo suficientemente grande para contener el mensaje de error.
         */
            char msg[50]; 
            sprintf(msg, "Operador '%c' no reconocido.", op); 
            error_eafitos(msg);
            return;
    }

    // 4. Salida
    // %.2f formatea el float para mostrar solo 2 decimales.
    printf(GRN "➜  Resultado: " RESET "%.2f\n", res);
}
