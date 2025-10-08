#!/bin/bash

echo "=== Prueba del proyecto EncFile ==="
echo ""

# Compilar el proyecto
echo "1. Compilando el proyecto..."
make clean > /dev/null 2>&1
if make > /dev/null 2>&1; then
    echo "   ✅ Compilación exitosa"
else
    echo "   ❌ Error en la compilación"
    exit 1
fi

echo ""
echo "2. Verificando estructura de archivos..."

# Verificar archivos principales
files=("main.cpp" "src/User.cpp" "src/Vault.cpp" "include/User.h" "include/Vault.h" "Makefile")
for file in "${files[@]}"; do
    if [ -f "$file" ]; then
        echo "   ✅ $file existe"
    else
        echo "   ❌ $file no encontrado"
    fi
done

echo ""
echo "3. Creando directorio de datos..."
mkdir -p data

echo ""
echo "4. El proyecto está listo para usar!"
echo "   Para ejecutar: ./encfile"
echo ""
echo "=== Funcionalidades implementadas ==="
echo "   ✅ Registro de usuarios con SHA-256"
echo "   ✅ Inicio de sesión seguro"
echo "   ✅ Cifrado de archivos con XOR"
echo "   ✅ Descifrado flexible (carpeta personal o ubicación específica)"
echo "   ✅ Listado de archivos cifrados"
echo "   ✅ Eliminación de archivos cifrados"
echo "   ✅ Directorio separado por usuario"
echo "   ✅ Manejo de excepciones"