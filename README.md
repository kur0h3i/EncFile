# EncFile - Sistema de Archivos Cifrados

## 📁 Descripción
EncFile es un sistema de gestión de archivos cifrados desarrollado en C++ que permite a los usuarios registrarse, autenticarse y gestionar archivos cifrados en una "bóveda" personal.

## ✨ Características
- ✅ **Registro seguro de usuarios** con hashing SHA-256
- ✅ **Autenticación robusta** con validación estricta
- ✅ **Cifrado de archivos** usando algoritmo XOR
- ✅ **Descifrado flexible** - en carpeta personal o ubicación específica
- ✅ **Listado de archivos cifrados** por usuario
- ✅ **Eliminación segura** de archivos cifrados
- ✅ **Directorios separados** por usuario
- ✅ **Manejo completo de excepciones**

## 🔧 Compilación

### Requisitos
- Compilador C++ con soporte para C++17
- OpenSSL (libssl-dev, libcrypto-dev)

### Instalación de dependencias (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential libssl-dev
```

### Compilar el proyecto
```bash
make clean
make
```

### Ejecutar
```bash
./encfile
```

## 🚀 Uso del Sistema

### 1. Registro de Usuario
- Selecciona opción 1
- Ingresa un nombre de usuario único
- Ingresa una contraseña (mínimo 6 caracteres)

### 2. Iniciar Sesión
- Selecciona opción 2
- Ingresa tu nombre de usuario y contraseña

### 3. Cifrar Archivo
- Una vez autenticado, selecciona opción 1
- Ingresa la ruta completa del archivo a cifrar
- Ingresa una clave para el cifrado
- El archivo cifrado se guardará en `data/tu_usuario/archivo.ext.enc`

### 4. Descifrar Archivo
- Selecciona opción 2
- Ingresa el nombre del archivo (sin .enc)
- Ingresa la clave de descifrado
- Elige dónde guardar:
  - **Opción 1**: En tu carpeta personal (automático)
  - **Opción 2**: En una ubicación específica que elijas

### 5. Listar Archivos Cifrados
- Selecciona opción 3 para ver todos tus archivos cifrados

### 6. Eliminar Archivo Cifrado
- Selecciona opción 4
- Ingresa el nombre del archivo a eliminar (sin .enc)

## 📁 Estructura del Proyecto

```
EncFile/
├── main.cpp              # Programa principal
├── Makefile             # Configuración de compilación
├── data/                # Datos de usuarios y archivos cifrados
│   ├── users.dat        # Base de datos de usuarios (binario)
│   └── [usuario]/       # Directorio personal de cada usuario
├── include/             # Archivos de cabecera
│   ├── User.h          # Declaración clase User
│   └── Vault.h         # Declaración clase Vault
├── src/                 # Implementaciones
│   ├── User.cpp        # Gestión de usuarios
│   └── Vault.cpp       # Gestión de archivos cifrados
└── test_file.txt       # Archivo de prueba
```

## 🔐 Aspectos de Seguridad

### Contraseñas
- Las contraseñas se almacenan usando hash SHA-256
- Nunca se guardan en texto plano
- Validación mínima de 6 caracteres

### Cifrado de Archivos
- Utiliza algoritmo XOR con clave proporcionada por el usuario
- Cada usuario tiene su directorio privado
- Los archivos cifrados tienen extensión `.enc`

### Almacenamiento
- Datos de usuario en formato binario eficiente
- Protección contra corrupción de datos
- Validaciones de tamaño y existencia

## 🛠️ Arquitectura Técnica

### Clase User
- Gestión de registro e inicio de sesión
- Hashing seguro de contraseñas
- Persistencia en archivo binario
- Validaciones de entrada

### Clase Vault
- Cifrado/descifrado de archivos
- Gestión de archivos por usuario
- Operaciones de archivo (listar, eliminar)
- Manejo de rutas y directorios

## 🧪 Pruebas

Para probar el sistema:

1. Ejecuta el script de prueba:
```bash
./test_project.sh
```

2. Prueba manual:
```bash
# Crear un archivo de prueba
echo "Hola mundo secreto" > mi_archivo.txt

# Ejecutar el programa
./encfile

# Seguir las instrucciones en pantalla
```

## 🐛 Problemas Resueltos

- ✅ **Error de compilación**: Métodos estáticos vs instancia corregidos
- ✅ **Interfaz inconsistente**: Parámetros de métodos corregidos
- ✅ **Rutas incorrectas**: Directorio por usuario implementado
- ✅ **Manejo de memoria**: Headers y namespaces corregidos
- ✅ **Validación de entrada**: Buffer clearing y getline implementado

## 📝 Mejoras Futuras

- [ ] Cifrado AES más robusto
- [ ] Compresión antes del cifrado
- [ ] Interfaz gráfica
- [ ] Base de datos SQL
- [ ] Recuperación de contraseñas
- [ ] Logs de actividad

## 👨‍💻 Desarrollo

El proyecto está completamente funcional y listo para usar. Todos los componentes han sido probados y funcionan correctamente.

### Autor
Proyecto EncFile - Sistema de archivos cifrados en C++