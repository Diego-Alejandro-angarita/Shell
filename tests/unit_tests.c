/**
 * @file unit_test.c
 * @brief Suite de pruebas unitarias para EAFITos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/shell.h"
#include "../include/commands.h"
#include "../include/utils.h"

// --- Macros simples para Testing ---
#define ASSERT_STR_EQ(esperado, actual) \
    do { \
        if (strcmp((esperado), (actual)) != 0) { \
            printf(RED "FALLO" RESET " en %s:%d\n", __FILE__, __LINE__); \
            printf("  Esperado: '%s'\n", (esperado)); \
            printf("  Obtenido: '%s'\n", (actual)); \
            return 0; \
        } \
    } while(0)

#define ASSERT_INT_EQ(esperado, actual) \
    do { \
        if ((esperado) != (actual)) { \
            printf(RED "FALLO" RESET " en %s:%d\n", __FILE__, __LINE__); \
            printf("  Esperado: %d\n", (esperado)); \
            printf("  Obtenido: %d\n", (actual)); \
            return 0; \
        } \
    } while(0)

// --- Pruebas ---

int test_parser_basico() {
    printf("Probando Parser Básico... ");
    char input[] = "calc 5 + 10"; // Usamos array modificable
    char **args = parsear_linea(input);

    ASSERT_STR_EQ("calc", args[0]);
    ASSERT_STR_EQ("5", args[1]);
    ASSERT_STR_EQ("+", args[2]);
    ASSERT_STR_EQ("10", args[3]);
    
    // Verificar que termine en NULL
    if (args[4] != NULL) {
        printf(RED "FALLO" RESET ": La lista de argumentos no termina en NULL.\n");
        return 0;
    }

    free(args);
    printf(GRN "OK" RESET "\n");
    return 1;
}

int test_parser_espacios_multiples() {
    printf("Probando Parser con Espacios Extra... ");
    char input[] = "   crear    archivo.txt   "; 
    char **args = parsear_linea(input);

    ASSERT_STR_EQ("crear", args[0]);
    ASSERT_STR_EQ("archivo.txt", args[1]);
    
    free(args);
    printf(GRN "OK" RESET "\n");
    return 1;
}

int test_cambio_idioma() {
    printf("Probando Cambio de Idioma... ");
    
    // Simular comando "idioma 2"
    char *args_en[] = {"idioma", "2", NULL};
    
    // Redirigir stdout temporalmente para no ensuciar la terminal con mensajes del comando
    freopen("/dev/null", "w", stdout); 
    cmd_idioma(args_en);
    freopen("/dev/tty", "w", stdout); // Restaurar stdout (en Linux/Mac)

    ASSERT_INT_EQ(2, idioma_actual);

    // Regresar a español
    char *args_es[] = {"idioma", "1", NULL};
    freopen("/dev/null", "w", stdout);
    cmd_idioma(args_es);
    freopen("/dev/tty", "w", stdout);

    ASSERT_INT_EQ(1, idioma_actual);

    printf(GRN "OK" RESET "\n");
    return 1;
}

int main() {
    printf(CYN "\n=== Iniciando Suite de Pruebas Unitarias EAFITos ===\n" RESET);
    
    int pasadas = 0;
    int total = 0;

    total++; if (test_parser_basico()) pasadas++;
    total++; if (test_parser_espacios_multiples()) pasadas++;
    total++; if (test_cambio_idioma()) pasadas++;

    printf("\nResumen: " GRN "%d/%d" RESET " pruebas pasaron.\n", pasadas, total);

    return (pasadas == total) ? 0 : 1;
}