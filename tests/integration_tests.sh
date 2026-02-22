#!/bin/bash

# Definir colores para salida visual
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Configuración de archivos
EJECUTABLE="./build/sistema_os"
INPUT_FILE="tests/input_temp.txt"
OUTPUT_FILE="tests/output_temp.txt"

echo -e "\nIniciando Pruebas de Integración (Modo Bilingüe ES/EN)..."

# 1. Asegurar que el proyecto esté compilado
if [ ! -f "$EJECUTABLE" ]; then
    echo "Compilando proyecto..."
    make > /dev/null
    if [ $? -ne 0 ]; then
        echo -e "${RED}[ERROR]${NC} La compilación falló."
        exit 1
    fi
fi

# --- FUNCIÓN DE PRUEBA FLEXIBLE ---

run_test() {
    local test_name="$1"
    local commands="$2"
    local pattern="$3"

    # Crear archivo de entrada
    echo -e "$commands\nsalir" > "$INPUT_FILE"

    # Ejecutar y capturar salida
    $EJECUTABLE < "$INPUT_FILE" > "$OUTPUT_FILE" 2>&1

    # --- NUEVO: Limpiar códigos de color ANSI ---
    # Esto elimina secuencias como \x1B[32m para dejar solo texto plano
    sed -i 's/\x1b\[[0-9;]*m//g' "$OUTPUT_FILE"

    # Buscar el patrón en el archivo limpio
    if grep -Eiq "$pattern" "$OUTPUT_FILE"; then
        echo -e "${GREEN}[PASS]${NC} $test_name"
    else
        echo -e "${RED}[FAIL]${NC} $test_name"
        echo "   Buscaba patrón: '$pattern'"
        echo "   Salida obtenida (limpia):"
        echo "   --------------------------------"
        tail -n 5 "$OUTPUT_FILE"
        echo "   --------------------------------"
        GLOBAL_STATUS=1
    fi
}

GLOBAL_STATUS=0

# --- EJECUCIÓN DE CASOS (Patrones Bilingües) ---

# Prueba 1: Calculadora Suma
# Busca "Resultado" O "Result" seguido de "10.00"
# La barra vertical | significa "O". \. escapa el punto literal.
run_test "Calculadora (5 + 5)" \
         "calc 5 + 5" \
         "(Resultado|Result): 10\.00"

# Prueba 2: Calculadora División
run_test "Calculadora División (10 / 2)" \
         "calc 10 / 2" \
         "(Resultado|Result): 5\.00"

# Prueba 3: Crear Archivo
# Como 'crear' en advanced_commands.c solo tiene mensaje en español por ahora,
# dejamos el patrón en español, pero preparado para el futuro:
run_test "Crear Archivo" \
         "crear test_file.txt" \
         "(Archivo|File) 'test_file.txt' (creado|created)"

# Prueba 4: Listar Archivo Creado
# Simplemente buscamos que el nombre del archivo aparezca en la lista
run_test "Listar Archivo" \
         "listar" \
         "test_file.txt"

# Prueba 5: Eliminar Archivo
# Nota: Enviamos "eliminar ... \n s \n" explícitamente.
run_test "Eliminar Archivo" \
         "eliminar test_file.txt\ns" \
         "(Eliminado|Deleted)"

# Prueba 6: Manejo de error comando desconocido
run_test "Comando Inválido" \
         "saltar_cuerda" \
         "(no reconocido|not recognized)"

# --- LIMPIEZA Y RESULTADO FINAL ---

rm -f "$INPUT_FILE" "$OUTPUT_FILE"

echo ""
if [ $GLOBAL_STATUS -eq 0 ]; then
    echo -e "\033[1;32mTODAS LAS PRUEBAS PASARON EXITOSAMENTE\033[0m"
    exit 0
else
    echo -e "   \033[1;31mALGUNAS PRUEBAS FALLARON\033[0m"
    exit 1
fi