# 📅 Historial de Cambios (Changelog)

El objetivo de este archivo es llevar un registro cronológico de las versiones, nuevas funcionalidades y correcciones de errores del sistema operativo **EAFITos**.

---

## [v1.1.0] - 2026-02-22
### Añadido
- **Historial y Modo Raw**: Implementación de navegación mediante flechas del teclado y manejo de terminal con `termios.h`.
- **Internacionalización**: Sistema bilingüe dinámico (Español/Inglés) con actualización automática de comandos.
- **Referencia de la API**: Finalización de la documentación técnica de las interfaces del sistema (vía Esteban).
- **Suite de Pruebas**: Desarrollo e implementación exitosa de tests para verificar la estabilidad de los comandos (vía Diego).
- **Comandos de Archivos**: Incorporación de funciones para `crear`, `eliminar`, `copiar` y `renombrar`.

### Cambios
- **Documentación de Usuario**: Finalización de la guía detallada con ejemplos de uso prácticos para el usuario final.
- **Interfaz (UX)**: Aplicación de colores ANSI para mejorar la legibilidad de errores y prompts.
- **Estructura de Git**: Consolidación de ramas `Esteban` y `Diego` hacia la rama principal y rama `Frank`.

### Corregido
- **Gestión de Memoria**: Eliminación de fugas (memory leaks) en el parser y el loop principal.
- **Sincronización**: Corrección de conflictos de enlazado y visualización de salida en terminales macOS.

---

## [v1.0.0] - 2026-02-04
### Añadido
- **Shell Interactiva**: Bucle REPL funcional.
- **Comandos Básicos**: `listar`, `leer`, `tiempo`, `calc`, `ayuda`, `salir`.
- **Arquitectura Modular**: Separación en `core`, `commands`, `utils`.
- **Sistema de Documentación**: Soporte para Doxygen.

### Cambios
- Migración de `main.c` monolítico a estructura modular.