/**
 * @file system_commands.c
 * @brief Comandos de utilería del sistema.
 * * Actualmente contiene la calculadora y el sistema de internacionalización (idiomas).
 */

#include <stdio.h>
#include <stdlib.h> // Para atof (ASCII to Float conversion) y atoi
#include "commands.h"
#include "utils.h" 

/* * Referencia externa a la variable global definida en shell_loop.c 
 * Esto permite que este archivo sepa en qué idioma estamos.
 */
extern int idioma_actual; 

/**
 * @brief Comando CALC (Calculadora)
 * * Realiza operaciones aritméticas básicas entre dos números.
 * Sintaxis esperada: calc <num1> <operador> <num2>
 */
void cmd_calc(char **args) {
    // 1. Validación de argumentos. Necesitamos exactamente 3 partes después del comando.
    if (args[1] == NULL || args[2] == NULL || args[3] == NULL) {
       if (idioma_actual == 1) { // Español
           error_eafitos("Faltan parámetros para la operación.");
           printf("  Uso: " YEL "calc <num1> <operador> <num2>" RESET "\n");
           printf("  Ejemplo: calc 5 + 3\n");
       } else { // Inglés
           error_eafitos("Missing parameters for the operation.");
           printf("  Usage: " YEL "calc <num1> <operator> <num2>" RESET "\n");
           printf("  Example: calc 5 + 3\n");
       }
       return;
    }

    // 2. Conversión de tipos (Parsing)
    float n1 = atof(args[1]);
    char op = args[2][0]; 
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
        case 'x': 
            res = n1 * n2; 
            break;
        case '/': 
            if (n2 == 0) {
                if (idioma_actual == 1) error_eafitos("Operación inválida: División por cero.");
                else error_eafitos("Invalid operation: Division by zero.");
                return;
            }
            res = n1 / n2; 
            break;
        default: 
            {
                char msg[50]; 
                if (idioma_actual == 1) sprintf(msg, "Operador '%c' no reconocido.", op);
                else sprintf(msg, "Operator '%c' not recognized.", op);
                error_eafitos(msg);
                return;
            }
    }

    // 4. Salida
    if (idioma_actual == 1) printf(GRN "➜  Resultado: " RESET "%.2f\n", res);
    else printf(GRN "➜  Result: " RESET "%.2f\n", res);
}

/**
 * @brief Comando IDIOMA
 * * Permite al usuario cambiar el idioma global de la shell EAFITos.
 * Opciones: 1 para Español, 2 para Inglés.
 */
void cmd_idioma(char **args) {
    // Si el usuario no pone argumentos (ej: solo escribe 'idioma')
    if (args[1] == NULL) {
        if (idioma_actual == 1) {
            error_eafitos("Debe especificar un idioma.");
            printf("  Uso: " YEL "idioma <1 o 2>" RESET "\n");
            printf("  1: Español | 2: Inglés\n");
        } else {
            error_eafitos("You must specify a language.");
            printf("  Usage: " YEL "idioma <1 or 2>" RESET "\n");
            printf("  1: Spanish | 2: English\n");
        }
        return;
    }

    int seleccion = atoi(args[1]);

    if (seleccion == 1) {
        idioma_actual = 1; // ESPAÑOL
        printf(GRN "➜  Idioma configurado en: " RESET "Español\n");
        cmd_ayuda(args);
    } else if (seleccion == 2) {
        idioma_actual = 2; // INGLES
        printf(GRN "➜  Language set to: " RESET "English\n");
        cmd_ayuda(args);
    } else {
        if (idioma_actual == 1) error_eafitos("Opción no válida. Use 1 o 2.");
        else error_eafitos("Invalid option. Use 1 or 2.");
    }
}