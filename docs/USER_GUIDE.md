# 📖 Guía de Usuario - EAFITos Shell

Bienvenido a **EAFITos**, una interfaz de línea de comandos (shell) diseñada para interactuar con el sistema de forma eficiente.  
Esta guía explica cómo instalar, configurar y utilizar la aplicación, así como dominar los comandos disponibles.

---

## 🎯 Objetivo

El propósito de esta guía es explicar cómo instalar, configurar y utilizar **EAFITos**, una shell personalizada orientada a la gestión eficiente de archivos y a la ejecución de operaciones matemáticas desde la terminal.

---

# 📑 Contenido

1. **Instalación y Preparación**
2. **Primeros Pasos**
3. **Manual de Comandos**
4. **Tips y Convenciones Visuales**

---

# 1️⃣ Instalación y Preparación

Para ejecutar **EAFITos**, primero debes compilar el código fuente en tu entorno local.  
Se recomienda utilizar un entorno Linux o WSL en Windows.



## 🔧 Prerrequisitos

Asegúrate de tener instaladas las herramientas básicas de compilación:

- **GCC**: Compilador de C.
- **Make**: Herramienta de automatización de compilación.

En sistemas basados en Ubuntu/Debian puedes instalarlas con:

```bash
sudo apt update
sudo apt install build-essential
```


## 📥 Clonar el Repositorio

Descarga el código fuente en tu máquina local ejecutando:

```bash
git clone https://github.com/Diego-Alejandro-angarita/Shell.git
cd Shell
```

## ⚙️ Compilación y Ejecución

El proyecto incluye un archivo Makefile, lo que permite automatizar el proceso de compilación.
Para compilar y ejecutar la shell automáticamente, utiliza:

```bash
   make run
   # O directamente:
   ./build/sistema_os
   ```

Este comando:

1. **Compila los archivos fuente**
2. **Genera el ejecutable**
3. **Inicia EAFITos Shell**


Si solo deseas compilar sin ejecutar:

```bash
make
```

✅ Verificación

Si la compilación y ejecución fueron exitosas, deberías ver el banner de bienvenida de EAFITos Shell. Esto confirma que el sistema está cargado y listo para operar.

```bash
Iniciando EAFITos v1.0...
Escribe 'ayuda' para comenzar.

[EAFITos] ➜ █
```


---

# 2. ✨ Primeros Pasos

Al iniciar, serás recibido por el banner de bienvenida . El prompt de espera se verá de la siguiente manera:

```bash
Iniciando EAFITos v1.0...
Escribe 'ayuda' para comenzar.

[EAFITos] ➜ █
```
Una vez dentro de EAFITos, puedes interactuar con el sistema mediante comandos de texto.

* **Ayuda rápida**: Escribe `ayuda` para desplegar la lista completa de comandos disponibles y sus descripciones.

Verás comandos para gestionar archivos (listar, leer, crear), realizar cálculos (calc) o incluso cambiar el idioma.

* **Historial de comandos**: Puedes presionar las teclas de flecha arriba (↑) o flecha abajo (↓) para navegar y reutilizar comandos que hayas escrito anteriormente.

* **Limpieza de pantalla**: Si la pantalla se llena de texto, utiliza el comando `limpiar`.

Nota: Este comando vacía el historial visual de la pantalla para darte un espacio de trabajo limpio, pero no borra el historial de las flechas del teclado.


* **Finalizar sesión**: Para cerrar la shell de forma segura, utiliza el comando `salir`.

---


# 3. 🛠️ Manual de Comandos

A continuación, se detallan las herramientas disponibles en **EAFITos** clasificadas por su función:

## 📁 Gestión de Archivos
| Comando | Uso | Descripción |
| :--- | :--- | :--- |
| **`listar`** | `listar` | Muestra todos los archivos y carpetas en el directorio actual. |
| **`crear`** | `crear <nombre>` | Crea un nuevo archivo vacío con el nombre especificado. |
| **`leer`** | `leer <archivo>` | Muestra el contenido de un archivo de texto directamente en la terminal. |
| **`copiar`** | `copiar <origen> <destino>` | Crea una copia exacta del archivo origen en la ruta de destino. |
| **`renombrar`**| `renombrar <viejo> <nuevo>` | Cambia el nombre de un archivo o lo mueve de ubicación. |
| **`eliminar`** | `eliminar <archivo>` | Borra un archivo. **Nota**: Requiere confirmación manual (`s/n`) antes de proceder. |


---

## 🔢 Utilidades del Sistema

| Comando | Uso | Descripción |
| :--- | :--- | :--- |
| **`calc`** | `calc <n1> <op> <n2>` | Realiza cálculos matemáticos básicos. Operadores: `+`, `-`, `*`, `/`. |
| **`tiempo`** | `tiempo` | Muestra la fecha y hora actual del sistema. |
| **`limpiar`** | `limpiar` | Limpia la pantalla de la terminal. |
| **`idioma`** | `idioma <1/2>` | Cambia el idioma del sistema (1: Español, 2: Inglés). |
| **`ayuda`** | `ayuda` | Muestra el menú completo de comandos disponibles. |
| **`salir`** | `salir` | Finaliza la ejecución de la shell. |

---

## 💡 Convenciones

- Los parámetros entre `< >` son obligatorios.
- Ejemplo correcto:
```bash
  leer notas.txt
  calc 10 * 5
```


### 🔢 Utilidades del Sistema
* **`calc <n1> <op> <n2>`**: Realiza cálculos matemáticos básicos.
    * **Operadores soportados**: `+`, `-`, `*`, `/`.
```bash
[EAFITos] ➜  calc 10 * 5
➜  Resultado: 50.00
[EAFITos] ➜
```

* **`tiempo`**: Muestra la fecha y hora exacta del sistema.
```bash
[EAFITos] ➜  tiempo
 Fecha y Hora: 21-02-2026 22:51:36
[EAFITos] ➜
```

* **`limpiar`**: Ejecuta una limpieza profunda de la terminal y muestra nuevamente la interfaz de bienvenida.
```bash
[EAFITos] ➜  limpiar



---  Panel de Ayuda EAFITos ---
Lista de comandos disponibles:

  - listar Muestra archivos del directorio.
  - leer <archivo> : Muestra el contenido de un archivo.
  - tiempo : Muestra la fecha y hora actual.
  - limpiar : Limpia la pantalla de la terminal.
  - calc <n1> <op> <n2> : Realiza cálculos simples.
  - ayuda : Muestra este mensaje.
  - crear <archivo> : Crea un archivo vacío.
  - eliminar <archivo> : Borra un archivo con confirmación.
  - renombrar <viejo> <nuevo> : Cambia el nombre de un archivo.
  - copiar <origen> <destino> : Copia el contenido de un archivo.
  - idioma <1/2> : Cambia el idioma (1: ES, 2: EN).
  - salir : Termina la sesión.
[EAFITos] ➜
```

* **`salir`**: Finaliza la ejecución de la shell y regresa a la terminal del sistema operativo.
```bash
[EAFITos] ➜  salir
Cerrando sesión en EAFITos... ¡Hasta pronto!
esteban@DESKTOP-A76EOMO:/mnt/c/Users/USUARIO/Esteban/Shell$
```
* **`ayuda`**: Muestra el panel completo de comandos disponibles.
```bash
[EAFITos] ➜  ayuda

---  Panel de Ayuda EAFITos ---
Lista de comandos disponibles:

  - listar Muestra archivos del directorio.
  - leer <archivo> : Muestra el contenido de un archivo.
  - tiempo : Muestra la fecha y hora actual.
  - limpiar : Limpia la pantalla de la terminal.
  - calc <n1> <op> <n2> : Realiza cálculos simples.
  - ayuda : Muestra este mensaje.
  - crear <archivo> : Crea un archivo vacío.
  - eliminar <archivo> : Borra un archivo con confirmación.
  - renombrar <viejo> <nuevo> : Cambia el nombre de un archivo.
  - copiar <origen> <destino> : Copia el contenido de un archivo.
  - idioma <1/2> : Cambia el idioma (1: ES, 2: EN).
  - salir : Termina la sesión.
[EAFITos] ➜
```
* **`idioma <1/2>`**: Cambia el idioma del sistema.

1 → Español

2 → Inglés
```bash
[EAFITos] ➜  idioma 2
➜  Language set to: English

---  EAFITos Help Panel ---
List of available commands:

  - listar List files in the current directory.
  - leer <file> : Display the content of a file.
  - tiempo : Show the current date and time.
  - limpiar : Clear the terminal screen.
  - calc <n1> <op> <n2> : Perform simple calculations.
  - ayuda : Display this help message.
  - crear <file> : Create an empty file.
  - eliminar <file> : Delete a file with confirmation.
  - renombrar <old> <new> : Change a file's name.
  - copiar <src> <dst> : Copy content from one file to another.
  - idioma <2/2> : Change language (1: ES, 2: EN).
  - salir : Terminate the session.
[EAFITos] ➜
```


### 📁 Gestión de Archivos

* **`listar`**: Muestra todos los archivos del directorio actual.
```bash
[EAFITos] ➜  listar

--- Archivos en el directorio actual ---
  .git
  build
  CHANGELOG.md
  CONTRIBUTORS.md
  docs
  Doxyfile
  include
  LICENSE
  Makefile
  README.md
  scripts
  src
  tests
[EAFITos] ➜
```

* **`crear <archivo>`**: Crea un archivo vacío con el nombre especificado.
```bash
[EAFITos] ➜  crear ejemplo.txt
Archivo 'ejemplo.txt' creado.

--- Archivos en el directorio actual ---
  .git
  build
  CHANGELOG.md
  CONTRIBUTORS.md
  docs
  Doxyfile
  ejemplo.txt
  include
  LICENSE
  Makefile
  README.md
  scripts
  src
  tests
[EAFITos] ➜
```

* **`leer <archivo>`**: Muestra el contenido de un archivo en la terminal.
```bash
[EAFITos] ➜  leer ejemplo.txt
[ Contenido de: ejemplo.txt ]
------------------------------------------
rwerrr
------------------------------------------

[EAFITos] ➜
```

Si el archivo no existe:
```bash
[EAFITos] ➜  leer w
 [Error]: No se pudo abrir el archivo 'w'.
[EAFITos] ➜
```


* **`copiar <origen> <destino>`**: Copia el contenido de un archivo en otro.
```bash
[EAFITos] ➜  copiar ejemplo.txt ej.txt
Copia finalizada.
[EAFITos] ➜
```

* **`renombrar <viejo> <nuevo>`**: Cambia el nombre de un archivo.
```bash
[EAFITos] ➜  renombrar ej.txt ej1.txt
Renombrado con éxito.

--- Archivos en el directorio actual ---
  .git
  build
  CHANGELOG.md
  CONTRIBUTORS.md
  docs
  Doxyfile
  ej1.txt
  ejemplo.txt
  include
  LICENSE
  Makefile
  README.md
  scripts
  src
  tests

[EAFITos] ➜
```

* **`eliminar <archivo>`**: Borra un archivo solicitando confirmación previa.
```bash
[EAFITos] ➜  eliminar ejemplo.txt
¿Eliminar ejemplo.txt? (s/n): s
Eliminado.
[EAFITos] ➜  listar

--- Archivos en el directorio actual ---
  .git
  build
  CHANGELOG.md
  CONTRIBUTORS.md
  docs
  Doxyfile
  ej1.txt
  include
  LICENSE
  Makefile
  README.md
  scripts
  src
  tests
[EAFITos] ➜
```
Si el usuario cancela:
```bash
[EAFITos] ➜  eliminar ej1.txt
¿Eliminar ej1.txt? (s/n): n
Operación cancelada.
[EAFITos] ➜
```

---

# 4. 💡 Tips y Convenciones Visuales

Para mejorar tu experiencia, **EAFITos** utiliza un sistema de códigos visuales:

* **Símbolos de Estado**:
    * **`[✔]` (Verde)**: Indica que la operación se completó exitosamente.
    * **`[✘]` (Rojo)**: Indica que ocurrió un error (ej. comando no reconocido o archivo inexistente).
* **Uso de Parámetros**:
    * Los textos encerrados en `< >` son obligatorios.
    * *Ejemplo*: En `leer <archivo>`, debes escribir algo como `leer notas.txt`.

---
