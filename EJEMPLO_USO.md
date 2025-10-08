# Ejemplo de Uso - Descifrado en Carpeta Personal

## Escenario
Un usuario llamado "Juan" quiere cifrar un archivo y luego descifrarlo directamente en su carpeta personal.

## Pasos:

### 1. Registro
```
1. Registrarse
Nombre: Juan
Contraseña: mipassword123
```

### 2. Iniciar Sesión
```
2. Iniciar Sesion
Usuario: Juan
Contrasena: mipassword123
```

### 3. Cifrar un Archivo
```
1. Cifrar Archivo
Ingrese la ruta completa del archivo a cifrar: /home/usuario/documento.txt
Ingrese la clave para cifrar: clavesecreta
```
*El archivo se guarda como: `data/Juan/documento.txt.enc`*

### 4. Descifrar en Carpeta Personal (NUEVA FUNCIONALIDAD)
```
2. Descifrar archivo
Ingrese el nombre del archivo cifrado (sin .enc): documento.txt
Ingrese la clave para descifrar: clavesecreta

¿Dónde desea guardar el archivo descifrado?
1. En mi carpeta personal (data/Juan/)         ← NUEVA OPCIÓN
2. En una ubicación específica
>> 1
```

**Resultado**: El archivo `documento.txt` se guarda automáticamente en `data/Juan/documento.txt`

### 5. Verificar Archivos
```
3. Listar archivos cifrados
```
**Salida**: 
- `documento.txt.enc` (archivo cifrado)

**En el directorio `data/Juan/`**:
- `documento.txt.enc` (cifrado)
- `documento.txt` (descifrado - ¡NUEVO!)

## Ventajas de esta funcionalidad:

✅ **Más conveniente**: No necesitas recordar rutas complejas
✅ **Más seguro**: Los archivos quedan en tu espacio personal
✅ **Más organizado**: Todo en una carpeta por usuario
✅ **Flexible**: Aún puedes elegir ubicación específica si lo deseas