/**
 * @file utils.h

 * @brief Utilidades generales para la shell EAFITos. 
 * Contiene funciones de manejo de errores, limpieza de pantalla y presentación.
 * Estas funciones son auxiliares para mejorar la experiencia del usuario y la interfaz de la shell.
 * Incluye definiciones de colores ANSI para mejorar la estética de los mensajes.
 */



#ifndef UTILS_H 
#define UTILS_H



/**
 * --- Colores ANSI (Para Interfaz Mejorada) ---
 * Estos códigos de escape permiten cambiar el color del texto en la terminal.
 * Ejemplo de uso: printf(RED "Este texto es rojo" RESET); 
 * Nota: No todos los terminales soportan colores ANSI, pero la mayoría de los modernos sí. 
 */


#define RED   "\x1B[31m" // Rojo
#define GRN   "\x1B[32m" // Verde
#define YEL   "\x1B[33m" // Amarillo
#define BLU   "\x1B[34m" // Azul
#define CYN   "\x1B[36m" // Cian
#define RESET "\x1B[0m"  // Resetear color



/**
 * @brief Imprime un mensaje de error formateado en rojo.
 * 
 * @param mensaje El mensaje de error a mostrar.
 * Ejemplo de uso: error_eafitos("Archivo no encontrado");
 * El mensaje se imprimirá en rojo para destacar que es un error, seguido del texto normal.
 * Nota: Esta función dirige el mensaje al flujo de error estándar (stderr) para que pueda ser separado de la salida normal si es necesario.
 */
void error_eafitos(const char *mensaje);

/**
 * @brief Limpia la pantalla de la terminal. 
 * Utiliza códigos de escape ANSI para limpiar la pantalla y posicionar el cursor en la esquina superior izquierda (0,0).
 */
void limpiar_pantalla();

/**
 * @brief Muestra un banner de bienvenida con colores.
 *  Esta función imprime un mensaje de bienvenida estilizado utilizando colores ANSI para mejorar la experiencia del usuario al iniciar la shell.

 */
void mostrar_bienvenida();

#endif