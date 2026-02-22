# 🔌 Referencia de la API

**Objetivo**: Proveer una referencia técnica detallada para desarrolladores que deseen extender el sistema, documentando funciones, parámetros y estructuras de datos (structs).

> [!TIP]
> **Nota**: Esta documentación se puede generar automáticamente usando **Doxygen**. Si al intentar ejecutarlo obtienes un error de "término no reconocido", consulta la sección de [Configuración de Doxygen](#configuración-técnica-de-doxygen).


**Generacion y Visualizacion**


Para generar la documentación actualizada, ejecuta el siguiente comando en la raíz del proyecto:

```bash
doxygen Doxyfile
```
Para visualizar el manual en el navegador:

Si estás en WSL, la forma más efectiva de abrirlo es:

- Ejecuta 
```bash
explorer.exe docs/html/index.html 
```

(si falla, usa `explorer.exe` . y navega manualmente).

- Selecciona el archivo index.html para abrirlo en tu navegador (Chrome, Edge o Firefox).

---

## 🧩 Módulos Principales

El sistema se divide en dos componentes fundamentales que permiten su modularidad y escalabilidad:

### 1. Shell Core
Este módulo contiene la lógica central del sistema y el ciclo de vida de la aplicación:
* **Ciclo REPL (Read-Eval-Print Loop)**: La función de bucle que mantiene la shell activa, imprime el prompt `[EAFITos] ➜` y espera la entrada del usuario.
* **Sistema de Parseo**: Funciones encargadas de fragmentar la cadena de texto introducida para identificar el comando base y separar sus argumentos.
* **Gestión de Sesión**: Controla el inicio del sistema, la carga del banner de bienvenida y la finalización segura mediante el comando `salir`.

### 2. Commands
Define la lógica individual de cada herramienta disponible en el sistema:
* **Firmas Estándar**: Cada comando (como `calc`, `listar` o `idioma`) sigue una estructura de función específica que facilita la adición de nuevas herramientas sin modificar el núcleo.
* **Validación de Parámetros**: Funciones que verifican que el usuario haya ingresado los datos correctos (por ejemplo, validar que `calc` reciba `<n1> <op> <n2>`).

### 3. Utils (src/utils)
* **Funciones de apoyo**: Manejo de errores, gestión de memoria y utilidades de texto compartidas por toda la shell.

---

## 🛠️ Configuración Técnica de Doxygen

Para generar la documentación automática y evitar los errores de terminal (CommandNotFoundException), sigue estos pasos:

### 1. Instalación Correcta
* **Nombre del comando**: Asegúrate de escribirlo correctamente con "y": `doxygen`. (Se detectaron intentos fallidos con la escritura "doxigen").
* **PATH de Windows**: El ejecutable debe estar en las Variables de Entorno del sistema. Si el comando falla después de instalarlo, añade la ruta de la carpeta `bin` de Doxygen a tu variable PATH.

### 2. Uso de Comentarios Especiales
Para que Doxygen reconozca tus funciones, utiliza el formato de comentarios de bloque sobre cada función en tus archivos `.c` o `.h`:

```c
/**
 * @brief Realiza un cálculo aritmético simple.
 * @param n1 Primer número (float).
 * @param op Operador (+, -, *, /).
 * @param n2 Segundo número (float).
 */
void cmd_calc(float n1, char op, float n2);
```







