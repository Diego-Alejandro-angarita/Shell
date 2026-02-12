/**
 * @file commands.h
 * @brief Interfaz para los comandos del sistema.
 * 
 * Define las funciones que implementan la lógica de cada comando disponible
 * en la shell. Todas siguen la firma `void cmd_nombre(char **args)`.
 */

#ifndef COMMANDS_H
#define COMMANDS_H

// --- Prototipos de Comandos ---

/**
 * @brief Lista los archivos del directorio actual.
 */
void cmd_listar(char **args);

/**
 * @brief Lee y muestra el contenido de un archivo.
 */
void cmd_leer(char **args);

/**
 * @brief Muestra la hora del sistema.
 */
void cmd_tiempo(char **args);

/**
 * @brief Realiza operaciones matemáticas simples.
 */
void cmd_calc(char **args);

/**
 * @brief Muestra la lista de ayuda.
 */
void cmd_ayuda(char **args);

/**
 * @brief Termina la ejecución de la shell.
 */
void cmd_salir(char **args);

// --- Utilidades del Registro de Comandos ---

/**
 * @brief Retorna el número total de comandos registrados.
 * @return int Cantidad de comandos.
 */
int num_comandos();



// --- Comandos Avanzados ---

/**
 * @brief Crea un nuevo archivo con el nombre especificado.
 * @param args Argumentos del comando, donde args[1] es el nombre del archivo a crear. 
 * Ejemplo de uso: `crear nuevo_archivo.txt`
 * Nota: Si el archivo ya existe, se mostrará un mensaje de error.
 */
void cmd_crear(char **args);


/**
 * @brief Elimina un archivo especificado por el usuario.
 * @param args Argumentos del comando, donde args[1] es el nombre del archivo a eliminar. 
 * Ejemplo de uso: `eliminar archivo_a_borrar.txt`
 * Nota: Si el archivo no existe o no se puede eliminar, se mostrará un mensaje de error.
 */
void cmd_eliminar(char **args);

/**
 * @brief Renombra un archivo existente a un nuevo nombre.
 * @param args Argumentos del comando, donde args[1] es el nombre actual del archivo y args[2] es el nuevo nombre. 
 * Ejemplo de uso: `renombrar archivo_viejo.txt archivo_nuevo.txt`
 * Nota: Si el archivo original no existe o el nuevo nombre ya está en uso, se mostrará un mensaje de error.
 */
void cmd_renombrar(char **args);

/**
 * @brief Copia un archivo de origen a un destino especificado por el usuario.
 * @param args Argumentos del comando, donde args[1] es el nombre del archivo de origen y args[2] es el nombre del archivo de destino. 
 * Ejemplo de uso: `copiar archivo_origen.txt archivo_destino.txt`
 * Nota: Si el archivo de origen no existe o no se puede copiar, se mostrará un mensaje de error.
 */
void cmd_copiar(char **args);

#endif
