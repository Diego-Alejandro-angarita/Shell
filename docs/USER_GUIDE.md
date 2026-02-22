# Guía de Usuario - EAFITos Shell

**Objetivo**: Esta guía explica cómo instalar, configurar y utilizar. **EAFITos** desde la perspectiva de un usuario final, proporcionando las instrucciones necesarias para operar la shell sin necesidad de conocimientos técnicos profundos de programación.

##  1. Instalación y Compilación

Para utilizar **EAFITos**, es necesario preparar el entorno y compilar el código fuente utilizando la herramienta `make`. Siga estos pasos detallados:

### Requisitos previos
* Un sistema basado en Unix (optimizado para **macOS** y Linux).
* Tener instalado el compilador `gcc`.
* Tener instalada la utilidad `make`.

### Instrucciones de Compilación (Uso de `make`)
La compilación se gestiona a través del archivo `Makefile`, que automatiza la creación del programa. Siga este flujo en su terminal:

1. **Limpieza de archivos previos**: Antes de compilar por primera vez o tras realizar cambios significativos, es recomendable ejecutar:

```bash
   make clean

```

*Esto eliminará la carpeta `build/` y cualquier archivo binario residual.*

2. **Compilación del sistema**: Para generar el ejecutable, simplemente escriba:

```bash
make

```


*El sistema compilará cada módulo (`core`, `commands`, `utils`) y creará el archivo ejecutable `sistema_os` dentro de la carpeta `build/`.*

##  2. Configuración y Primeros Pasos

### Ejecución Básica

Una vez compilado, tiene dos formas de iniciar la shell:

* **Manual**: `./build/sistema_os`
* **Acceso rápido**: `make run` (Este comando compila y ejecuta automáticamente).

### Configuración Inicial

Al entrar por primera vez, el sistema estará en **Español** por defecto. Lo primero que se recomienda es verificar los comandos disponibles escribiendo `ayuda`.

### Funciones Especiales del Teclado (Modo Raw)

Para una experiencia más fluida, la shell permite:

* **Historial (↑ / ↓)**: Use las flechas arriba y abajo para recuperar los últimos 50 comandos ejecutados.
* **Borrado Real**: Use **Backspace** para corregir texto mientras escribe.
* **Salida Elegante**: Use `Ctrl+D` para cerrar la sesión inmediatamente.

## 3. Manual Detallado de Comandos

A continuación se presenta la explicación de cada comando con sus respectivos ejemplos de uso.

### Internacionalización

#### `idioma <1/2>`

Cambia el lenguaje de la interfaz y los nombres de los comandos aceptados.

* **Uso**: `idioma 1` para Español, `idioma 2` para Inglés.
* **Ejemplo**:

```bash
[EAFITos] ➜ idioma 2
# El sistema confirmará: "Language set to: English" y mostrará la ayuda en inglés.

```

### Gestión de Archivos

#### `listar`

Muestra una lista de todos los archivos y carpetas en el directorio actual (excluyendo archivos ocultos).

* **Ejemplo**:
```bash
[EAFITos] ➜ listar

```


#### `leer <archivo>`

Muestra el contenido íntegro de un archivo de texto en la terminal.

* **Ejemplo**:
```bash
[EAFITos] ➜ leer notas.txt

```



#### `crear <nombre>`

Genera un archivo nuevo y vacío con el nombre especificado.

* **Ejemplo**:
```bash
[EAFITos] ➜ crear nuevo_documento.txt

```



#### `eliminar <nombre>`

Borra un archivo del disco. Por seguridad, el sistema siempre pedirá una confirmación manual.

* **Ejemplo**:
```bash
[EAFITos] ➜ eliminar viejo.log
¿Eliminar viejo.log? (s/n): s

```



#### `copiar <origen> <destino>`

Crea una copia exacta del archivo de origen con el nombre del destino.

* **Ejemplo**:
```bash
[EAFITos] ➜ copiar datos.csv respaldo_datos.csv

```



#### `renombrar <viejo> <nuevo>`

Cambia el nombre de un archivo existente.

* **Ejemplo**:
```bash
[EAFITos] ➜ renombrar borrador.txt final.txt

```



---

### Utilidades y Sistema

#### `calc <n1> <op> <n2>`

Realiza operaciones matemáticas simples de punto flotante. Soporta `+`, `-`, `*` (o `x`) y `/`.

* **Ejemplo**:
```bash
[EAFITos] ➜ calc 15.5 * 2
➜ Resultado: 31.00

```



#### `tiempo`

Muestra la fecha y hora actual del sistema con formato localizado.

* **Ejemplo**:
```bash
[EAFITos] ➜ tiempo
Fecha y Hora: 22-02-2026 14:35:10

```



#### `limpiar`

Limpia todo el texto de la pantalla y vuelve a mostrar el banner de bienvenida de EAFITos.

* **Ejemplo**:
```bash
[EAFITos] ➜ limpiar

```



#### `ayuda`

Muestra el panel de asistencia con la lista de comandos traducida al idioma actual.

* **Ejemplo**:
```bash
[EAFITos] ➜ ayuda

```



#### `salir`

Termina la ejecución de la shell y regresa al sistema operativo padre.

* **Ejemplo**:
```bash
[EAFITos] ➜ salir
