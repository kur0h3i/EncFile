#include "Vault.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

Vault::Vault(string& nombreUsuario) {
  rutaUsuario = "data/" + nombreUsuario + "/";
  filesystem::create_directories(rutaUsuario);
}

void Vault::cifrarArchivo(const string& rutaOrigen, const string& clave) {
  // 1. Verificar si existe el archivo
  if (!filesystem::exists(rutaOrigen)) {
    throw runtime_error("El archivo no existe: " + rutaOrigen);
  }

  // 2. Extraer nombre archivo
  string nombreArchivo = filesystem::path(rutaOrigen).filename().string();

  // 3. Leer archivo completo
  ifstream archivoEntrada(rutaOrigen, ios::binary);
  if (!archivoEntrada) {
    throw runtime_error("No se pudo abrir el archivo para lectura: " +
                        rutaOrigen);
  }
  vector<char> contenido((istreambuf_iterator<char>(archivoEntrada)),
                         istreambuf_iterator<char>());
  archivoEntrada.close();

  // 4. Cifrar con XOR
  for (size_t i = 0; i < contenido.size(); ++i) {
    contenido[i] ^= clave[i % clave.size()];
  }

  // 5. Construir ruta destino en el directorio del usuario
  string rutaDestino = rutaUsuario + nombreArchivo + ".enc";

  // 6. Guardar archivo cifrado
  ofstream archivoSalida(rutaDestino, ios::binary);
  if (!archivoSalida) {
    throw runtime_error("No se pudo abrir el archivo para escritura: " +
                        rutaDestino);
  }
  archivoSalida.write(contenido.data(), contenido.size());
  archivoSalida.close();
}

void Vault::descifrarArchivo(const string& nombreArchivo, const string& clave,
                             const string& rutaDestino) {
  // 1. Construir ruta del archivo cifrado en el directorio del usuario
  string rutaCifrado = rutaUsuario + nombreArchivo + ".enc";

  // 2. Verificar si existe el archivo cifrado
  if (!filesystem::exists(rutaCifrado)) {
    throw runtime_error("El archivo cifrado no existe: " + rutaCifrado);
  }

  // 3. Leer archivo cifrado
  ifstream archivoEntrada(rutaCifrado, ios::binary);
  if (!archivoEntrada) {
    throw runtime_error("No se pudo abrir el archivo cifrado para lectura: " +
                        rutaCifrado);
  }
  vector<char> contenido((istreambuf_iterator<char>(archivoEntrada)),
                         istreambuf_iterator<char>());
  archivoEntrada.close();

  // 4. Descifrar con XOR
  for (size_t i = 0; i < contenido.size(); ++i) {
    contenido[i] ^= clave[i % clave.size()];
  }

  // 5. Guardar archivo descifrado
  ofstream archivoSalida(rutaDestino, ios::binary);
  if (!archivoSalida) {
    throw runtime_error("No se pudo abrir el archivo para escritura: " +
                        rutaDestino);
  }
  archivoSalida.write(contenido.data(), contenido.size());
  archivoSalida.close();
}

// Sobrecarga para descifrar en la carpeta del usuario
void Vault::descifrarArchivo(const string& nombreArchivo, const string& clave) {
  // 1. Construir ruta del archivo cifrado en el directorio del usuario
  string rutaCifrado = rutaUsuario + nombreArchivo + ".enc";

  // 2. Verificar si existe el archivo cifrado
  if (!filesystem::exists(rutaCifrado)) {
    throw runtime_error("El archivo cifrado no existe: " + rutaCifrado);
  }

  // 3. Leer archivo cifrado
  ifstream archivoEntrada(rutaCifrado, ios::binary);
  if (!archivoEntrada) {
    throw runtime_error("No se pudo abrir el archivo cifrado para lectura: " +
                        rutaCifrado);
  }
  vector<char> contenido((istreambuf_iterator<char>(archivoEntrada)),
                         istreambuf_iterator<char>());
  archivoEntrada.close();

  // 4. Descifrar con XOR
  for (size_t i = 0; i < contenido.size(); ++i) {
    contenido[i] ^= clave[i % clave.size()];
  }

  // 5. Guardar archivo descifrado en la carpeta del usuario
  string rutaDestino = rutaUsuario + nombreArchivo;
  ofstream archivoSalida(rutaDestino, ios::binary);
  if (!archivoSalida) {
    throw runtime_error("No se pudo abrir el archivo para escritura: " +
                        rutaDestino);
  }
  archivoSalida.write(contenido.data(), contenido.size());
  archivoSalida.close();
}

void Vault::listarArchivosCifrados() const {
  // 1. Verificar si el directorio del usuario existe
  if (!filesystem::exists(rutaUsuario) ||
      !filesystem::is_directory(rutaUsuario)) {
    cout << "No hay archivos cifrados para este usuario.\n";
    return;
  }

  // 2. Iterar sobre los archivos en el directorio del usuario
  bool hayArchivos = false;
  for (const auto& entry : filesystem::directory_iterator(rutaUsuario)) {
    if (entry.is_regular_file() && entry.path().extension() == ".enc") {
      // 3. Imprimir el nombre del archivo cifrado
      cout << entry.path().filename().string() << endl;
      hayArchivos = true;
    }
  }

  if (!hayArchivos) {
    cout << "No hay archivos cifrados para este usuario.\n";
  }
}

void Vault::eliminarArchivo(const string& nombreArchivo) {
  // 1. Construir la ruta del archivo cifrado en el directorio del usuario
  string rutaArchivo = rutaUsuario + nombreArchivo + ".enc";

  // 2. Verificar si el archivo existe
  if (!filesystem::exists(rutaArchivo)) {
    throw runtime_error("El archivo no existe: " + rutaArchivo);
  }

  // 3. Eliminar el archivo
  if (!filesystem::remove(rutaArchivo)) {
    throw runtime_error("No se pudo eliminar el archivo: " + rutaArchivo);
  }

  cout << "Archivo eliminado: " << nombreArchivo << ".enc" << endl;
}
