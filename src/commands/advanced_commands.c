#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"
#include "utils.h"  // Para funciones de utilidad como error_eafitos

// crear <archivo>
void cmd_crear(char **args) {
    if (args[1] == NULL) { printf("Uso: crear <nombre>\n"); return; }
    FILE *fp = fopen(args[1], "w");
    if (fp) { printf("Archivo '%s' creado.\n", args[1]); fclose(fp); }
    else perror("Error al crear");
}

// eliminar <archivo> (con confirmación)
void cmd_eliminar(char **args) {
    if (args[1] == NULL) { printf("Uso: eliminar <nombre>\n"); return; }
    char conf[10];
    printf("¿Eliminar %s? (s/n): ", args[1]);
    scanf("%s", conf); getchar();
    if (strcmp(conf, "s") == 0 || strcmp(conf, "S") == 0) {
        if (remove(args[1]) == 0) printf("Eliminado.\n");
        else perror("Error");
    }
}

// renombrar <viejo> <nuevo>
void cmd_renombrar(char **args) {
    if (args[1] == NULL || args[2] == NULL) { printf("Uso: renombrar <viejo> <nuevo>\n"); return; }
    if (rename(args[1], args[2]) == 0) printf("Renombrado con éxito.\n");
    else perror("Error");
}

// copiar <origen> <destino>
void cmd_copiar(char **args) {
    if (args[1] == NULL || args[2] == NULL) { printf("Uso: copiar <origen> <destino>\n"); return; }
    FILE *src = fopen(args[1], "rb"), *dst = fopen(args[2], "wb");
    if (!src || !dst) { perror("Error en archivos"); if(src) fclose(src); return; }
    char buffer[1024]; size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) fwrite(buffer, 1, bytes, dst);
    printf("Copia finalizada.\n");
    fclose(src); fclose(dst);
}