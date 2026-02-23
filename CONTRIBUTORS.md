# 👥 Colaboradores del Proyecto

Este archivo tiene como objetivo reconocer a todas las personas que han contribuido al desarrollo de **EAFITos**.

---

## Mantenedores Principales

* **Esteban Alvarez Garcia**
- Diseño de la interfaz en terminal. 
- Documentación técnica con Doxygen.

* **Diego Angarita Arboleda** 
- Validación y manejo de errores.
- Pruebas y control de calidad.

* **Yan Frank Rios Lopez**

* **Motor del Núcleo (Core Engine):**
* Optimización del bucle **principal REPL** (Read-Eval-Print Loop) para una ejecución sin latencia.
* Desarrollo del **Parser de Comandos** con gestión dinámica de memoria para la tokenización de argumentos.
* Implementación de señales de salida controlada (`Ctrl+D`) y limpieza de buffers de entrada.


* **Sistema de Comandos Avanzados (POSIX):**
* Implementación de lógica para manipulación de archivos: `crear`, `eliminar` (con flujo de confirmación manual), `copiar` y `renombrar`.
* Desarrollo de la utilidad **Calculadora Aritmética** con soporte para operaciones de punto flotante.
* Comando de gestión de tiempo y estados del sistema.


* **Internacionalización y Localización (i18n):**
* Diseño del motor de **Traducción Dinámica** (Español/Inglés) que permite el cambio de nombres de comandos en tiempo de ejecución.
* Sincronización del panel de ayuda (`ayuda`/`help`) según el contexto regional seleccionado.


* **Gestión de Entregables y DevOps:**
* **Edición y post-producción del video** demostrativo para la sustentación final del proyecto.
* Auditoría de **Fugas de Memoria** y optimización del uso de punteros para estabilidad del sistema.
* Redacción y estructuración de la **Guía de Usuario** y el **Changelog** oficial del proyecto.


---

## Colaboradores

* **Edison Valencia Diaz**  
- Arquitectura del núcleo y shell básica.
- Implementación del módulo de gestión de archivos.

---

## Cómo contribuir
Si deseas aparecer en esta lista:
1. Haz un fork del repositorio.
2. Implementa una nueva funcionalidad (ej. gestión de procesos).
3. Envía un Pull Request.


---