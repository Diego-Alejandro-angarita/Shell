# 🧩 Diseño del Sistema

**Objetivo**: Documentar las decisiones arquitectónicas, diagramas de flujo y estructuras de datos clave utilizadas en el desarrollo del kernel y la shell.

## 1. Ciclo de Vida de la Shell (REPL)
La shell opera mediante un ciclo continuo de Lectura-Evaluación-Impresión (REPL, por sus siglas en inglés), el cual es gestionado por la función `loop_shell()`. Este bucle no se detiene hasta que el usuario invoca el comando explícito de `salir`. El flujo se divide en tres etapas principales:

![Diagrama del bucle principal REPL](../images/Diagrama__REPL.png)

1. **Lectura (`leer_linea`)**: Se captura una línea de texto desde la entrada estándar del usuario. 
2. **Análisis Léxico (`parsear_linea`)**: La cadena cruda ingresada se divide en un arreglo de "tokens" o argumentos. Para hacer esta separación, el sistema utiliza un conjunto de delimitadores definidos en la constante `DELIM`, los cuales incluyen espacios, tabulaciones y saltos de línea (`" \t\r\n\a"`). El primer token (`args[0]`) corresponde al comando y los subsiguientes a sus parámetros.
3. **Ejecución (`ejecutar`)**: Se orquesta la ejecución del comando correspondiente pasándole la lista de argumentos generada en el paso anterior.

## 2. Gestión de Memoria
El manejo eficiente de los recursos es fundamental en C, por lo que el sistema delega responsabilidades claras para la asignación y liberación de memoria:

* **Buffer de Entrada**: Se define un tamaño máximo de buffer inicial a través de `MAX_CMD_INPUT` (1024 bytes). Sin embargo, funciones dinámicas se encargan de manejar la memoria de la entrada.
* **Liberación de Punteros**: El puntero a la cadena retornada por `leer_linea()` se asigna dinámicamente y es responsabilidad del ciclo principal liberar esa memoria utilizando `free` para evitar fugas de memoria.
* **Arreglo de Argumentos**: La función de parseo devuelve un arreglo de cadenas de texto terminado en `NULL`, lo que requiere una correcta gestión de las referencias generadas durante la tokenización.

## 3. Modularidad: `core` vs `commands`
Para mantener un código limpio y escalable, el proyecto divide sus responsabilidades en dos grandes módulos:

* **El Núcleo (`core`)**: Reside en el directorio `/src` (como se evidencia con `main.c`) y es responsable de la operación interna de la shell. Incluye la lógica principal del bucle, la captura de la entrada del usuario, el motor de parseo de las cadenas y el estado general del sistema, como la gestión del `idioma_actual` de la interfaz.
* **Los Comandos (`commands`)**: Este módulo aísla la lógica de negocio de cada utilidad individual de la shell. Aquí se implementan las operaciones específicas como la gestión del sistema de archivos (`listar`, `crear`, `eliminar`, `renombrar`, `copiar`), la manipulación de información (`leer`, `tiempo`, `calc`) y el control del entorno (`limpiar`, `ayuda`, `idioma`, `salir`).

## 4. Sistema de Despacho de Comandos (Registro Dinámico)
Una de las decisiones arquitectónicas más importantes del núcleo es evitar el uso de cadenas interminables de declaraciones `if-else` para buscar qué comando ejecutar. En su lugar, el sistema de despacho en `ejecutar()` utiliza dos arreglos paralelos:

* `nombres_comandos[]`: Un arreglo de cadenas de texto (strings) con los nombres de los comandos reconocidos por la shell (ej. `"listar"`, `"crear"`, `"salir"`).
* `func_comandos[]`: Una tabla de punteros a función asociados a cada comando. Todas las funciones de los comandos respetan una firma estándar: `void cmd_nombre(char **args)`.

**Flujo de ejecución:** Al recibir los argumentos parseados, el sistema itera sobre la cantidad total de comandos llamando a `strcmp`. Si encuentra una coincidencia exacta entre el texto introducido y un índice en `nombres_comandos`, invoca inmediatamente la función correspondiente en ese mismo índice dentro de `func_comandos`. Esto hace que la shell sea altamente extensible: para agregar un nuevo comando, un desarrollador solo necesita agregar la firma en el archivo de cabecera y actualizar estas dos listas.

## 5. Procesamiento de Entrada y Modo Raw (Historial de Comandos)
La captura de la entrada del usuario va más allá del uso de funciones estándar como `getline` o `scanf`. Para permitir una interacción dinámica (como navegar por el historial o borrar caracteres), el archivo encargado del parseo implementa una lectura byte a byte manipulando la configuración de la terminal mediante la librería `<termios.h>`.

* **Modo Raw:** Al llamar a `leer_linea()`, el sistema desactiva temporalmente las banderas `ECHO` (para que la terminal no imprima automáticamente lo que se teclea) y `ICANON` (para no tener que esperar a que el usuario presione la tecla *Enter* para procesar los datos). Al terminar la lectura, se restaura el estado original.
* **Manejo de caracteres especiales:** Al capturar la entrada manualmente, el sistema puede reaccionar a la tecla retroceso (Backspace, ASCII 127) borrando visualmente los caracteres de la pantalla (`"\b \b"`).
* **Historial de Comandos:** Se interceptan las secuencias de escape ANSI (`\x1b`) seguidas de `[A` o `[B` para detectar cuándo el usuario presiona las flechas direccionales hacia arriba o abajo. El sistema mantiene un arreglo bidimensional estático (`historial`) con capacidad para los últimos 50 comandos ejecutados de hasta 1024 caracteres de longitud. Cuando este límite se alcanza, los comandos antiguos se desplazan mediante un enfoque de lista FIFO (First-In, First-Out) para hacer espacio al más reciente.

## 6. Interfaz, Utilidades y Manejo de Errores
La presentación de la información está centralizada en un módulo de utilidades diseñado para enriquecer la experiencia visual del sistema operativo.

* **Códigos de Escape ANSI:** Se utilizan macros predefinidas (como `RED`, `GRN`, `CYN`) que inyectan códigos de escape directamente en los mensajes de salida (e.g. `\x1b[31m`). Esto se utiliza tanto en el prompt iterativo (`EAFITos>`), como en la función de bienvenida inicial (`mostrar_bienvenida()`) invocada desde el punto de entrada.
* **Gestión Centralizada de Errores:** En lugar de hacer impresiones manuales por todo el código, el sistema utiliza la función `error_eafitos()`. Esta función no solo formatea el mensaje en texto rojo para resaltarlo, sino que conceptualmente sirve como punto de apoyo en caso de que en un futuro se requiera enviar los errores al flujo estándar de errores (`stderr`) en lugar de a la salida normal.