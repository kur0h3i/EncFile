# EncFile

Sistema de archivos cifrados en C++ con autenticación de usuarios.

## � Inicio Rápido

```bash
# Instalar dependencias
sudo apt install build-essential libssl-dev

# Compilar y ejecutar
make
make run
```

## ✨ Funcionalidades

- 🔐 Registro y login con SHA-256
- 🗂️ Cifrado/descifrado de archivos (XOR)
- 📁 Bóveda personal por usuario
- 🗃️ Gestión de archivos cifrados

## 📁 Estructura

```
EncFile/
├── main.cpp          # Punto de entrada
├── bin/encfile       # Ejecutable
├── src/              # Código fuente
├── include/          # Headers
└── data/             # Archivos de usuario
```

## 🎯 Uso

1. **Registrarse**: Crear cuenta nueva
2. **Login**: Iniciar sesión
3. **Cifrar**: Proteger archivos con clave
4. **Descifrar**: Recuperar archivos originales
5. **Gestionar**: Listar y eliminar archivos

---
**Autor**: Pedro Pérez Montero