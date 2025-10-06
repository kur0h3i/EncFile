#include "User.h"

#include <openssl/sha.h>

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

// Función para hashear con SHA-256
string User::hashPassword(const string& password) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256((unsigned char*)password.c_str(), password.size(), hash);

  stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << hex << setw(2) << setfill('0') << (int)hash[i];
  }
  return ss.str();
}

// Verificar si un usuario ya existe
bool User::usuarioExiste(const string& nombre) {
  ifstream in("data/users.dat", ios::binary);
  if (!in) {
    return false;  // Si no existe el archivo, el usuario no existe
  }

  while (in.good() && !in.eof()) {
    size_t lonN, lonP;
    string n, p;

    if (!in.read(reinterpret_cast<char*>(&lonN), sizeof(lonN))) break;
    if (lonN > 10000) break;  // Protección contra datos corruptos

    n.resize(lonN);
    if (!in.read(&n[0], lonN)) break;

    if (!in.read(reinterpret_cast<char*>(&lonP), sizeof(lonP))) break;
    if (lonP > 10000) break;  // Protección contra datos corruptos

    p.resize(lonP);
    if (!in.read(&p[0], lonP)) break;

    if (n == nombre) {
      in.close();
      return true;
    }
  }

  in.close();
  return false;
}

// Constructor
User::User(string nombre, string password) {
  this->nombre = nombre;
  this->password = password;
}

// Métodos
User User::registrarUsuario() {
  string nombre;
  string password;

  do {
    cout << "Nombre : ";
    cin.ignore();          // Limpiar buffer
    getline(cin, nombre);  // Usar getline para permitir espacios

    if (nombre.empty()) {
      cout << "El nombre no puede estar vacío. Inténtalo de nuevo.\n";
    } else if (usuarioExiste(nombre)) {
      cout << "El nombre de usuario ya existe. Elige otro.\n";
      nombre.clear();  // Forzar repetición del bucle
    }
  } while (nombre.empty());

  do {
    cout << "Contraseña : ";
    getline(cin, password);  // Usar getline en lugar de cin >>

    if (password.empty()) {
      cout << "La contraseña no puede estar vacía. Inténtalo de nuevo.\n";
    } else if (password.length() < 6) {
      cout << "La contraseña debe tener al menos 6 caracteres.\n";
      password.clear();
    }
  } while (password.empty());

  // Hashear la contraseña antes de crear el usuario
  string hashedPassword = hashPassword(password);
  User u(nombre, hashedPassword);
  u.guardarUsuario();
  cout << "Registrado Correctamente\n";
  return u;
}

User User::iniciarSesion(string nombre, string password) {
  // Hashear la contraseña ingresada para compararla
  string hashedPassword = hashPassword(password);

  ifstream in("data/users.dat", ios::binary);
  if (!in) {
    cerr << "ERROR: No se pudo abrir el archivo de usuarios.\n";
    throw runtime_error("No se pudo abrir el archivo de usuarios.");
  }

  bool encontrado = false;
  while (in.good() && !in.eof()) {
    size_t lonN, lonP;
    string n, p;

    // Leer con validación
    if (!in.read(reinterpret_cast<char*>(&lonN), sizeof(lonN))) break;
    if (lonN > 10000) {  // Protección contra datos corruptos
      in.close();
      throw runtime_error("Archivo de usuarios corrupto.");
    }

    n.resize(lonN);
    if (!in.read(&n[0], lonN)) break;

    if (!in.read(reinterpret_cast<char*>(&lonP), sizeof(lonP))) break;
    if (lonP > 10000) {  // Protección contra datos corruptos
      in.close();
      throw runtime_error("Archivo de usuarios corrupto.");
    }

    p.resize(lonP);
    if (!in.read(&p[0], lonP)) break;

    // Comparar credenciales
    if (n == nombre && verificarContraseña(p, hashedPassword)) {
      encontrado = true;
      in.close();
      // NO devolver el hash, crear usuario sin contraseña en memoria
      return User(n, "");
    }
  }

  in.close();

  if (!encontrado) {
    throw invalid_argument("Credenciales inválidas o usuario no encontrado.");
  }

  // Esta línea nunca debería ejecutarse, pero evita warnings
  throw invalid_argument("Error inesperado en inicio de sesión.");
}

void User::guardarUsuario() {
  // Crear directorio si no existe
  try {
    filesystem::create_directories("data");
    if (!nombre.empty()) {
      filesystem::create_directories("data/" + nombre);
    }
  } catch (const filesystem::filesystem_error& e) {
    cerr << "ERROR al crear directorios: " << e.what() << endl;
    return;
  }

  ofstream out("data/users.dat", ios::binary | ios::app);
  if (!out) {
    cerr << "ERROR: No se pudo abrir el archivo para guardar\n";
    return;
  }

  // Guardar en Binario
  size_t longitudNombre = nombre.size();
  out.write(reinterpret_cast<const char*>(&longitudNombre),
            sizeof(longitudNombre));
  out.write(nombre.c_str(), longitudNombre);

  size_t longitudPassword = password.size();
  out.write(reinterpret_cast<const char*>(&longitudPassword),
            sizeof(longitudPassword));
  out.write(password.c_str(), longitudPassword);

  out.close();  // Cerrar explícitamente

  if (!out.good()) {
    cerr << "ERROR: Fallo al escribir en el archivo\n";
  }
}

// Función auxiliar para verificar contraseñas
bool User::verificarContraseña(const string& almacenada,
                               const string& ingresada) {
  return almacenada == ingresada;
}

// Getters
string User::getNombre() { return nombre; }
string User::getContraseña() { return password; }