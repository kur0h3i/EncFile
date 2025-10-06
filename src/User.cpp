#include "User.h"

#include <filesystem>
#include <fstream>
#include <iostream>
using namespace std;

// Constructor
User::User(string nombre, string password) {
  this->nombre = nombre;
  this->password = password;
}

// Metodos
User User::registrarUsuario() {
  string nombre;
  string password;

  do {
    cout << "Nombre : ";
    cin >> nombre;
    if (nombre.empty()) {
      cout << "El nombre no puede estar vacío. Inténtalo de nuevo.\n";
    }
  } while (nombre.empty());

  do {
    cout << "Contraseña : ";
    cin >> password;
    if (password.empty()) {
      cout << "La contraseña no puede estar vacía. Inténtalo de nuevo.\n";
    }
  } while (password.empty());

  User u(nombre, password);
  u.guardarUsuario();
  cout << "Registrado Correctamente\n";
  return u;
}

User User::iniciarSesion(string nombre, string password) {
  // Abrir el archivo binario de usuarios
  ifstream in("data/users.dat", ios::binary);
  if (!in) {
    cerr << "ERROR: No se pudo abrir el archivo de usuarios.\n";
    throw runtime_error("No se pudo abrir el archivo de usuarios.");
  }

  while (true) {
    size_t lonN, lonP;
    string n, p;

    // Leer la longitud del nombre
    if (!in.read(reinterpret_cast<char *>(&lonN), sizeof(lonN))) break;
    n.resize(lonN);
    if (!in.read(&n[0], lonN)) break;

    // Leer la longitud de la contraseña
    if (!in.read(reinterpret_cast<char *>(&lonP), sizeof(lonP))) break;
    p.resize(lonP);
    if (!in.read(&p[0], lonP)) break;

    // Comparar credenciales
    if (n == nombre && p == password) {
      return User(n, p);  // Devolver el usuario encontrado
    }
  }

  throw invalid_argument("Credenciales inválidas o usuario no encontrado.");
}

void User::guardarUsuario() {
  filesystem::create_directories("data/" + nombre);
  ofstream out("data/users.dat", ios::binary | ios::app);

  if (!out) {
    cerr << "ERROR : No se pudo abrir el archivo";
    return;
  }

  // Guardar en Binario
  // reinterpret_cast<const char*> convierte el puntero de entero a bytes.

  size_t longitudNombre = nombre.size();
  // Serialización binaria: guardamos primero la longitud y luego el nombre en
  // binario
  out.write(reinterpret_cast<const char *>(&longitudNombre),
            sizeof(longitudNombre));          // longitud del nombre
  out.write(nombre.c_str(), longitudNombre);  // nombre en binario

  size_t longitudPassword = password.size();
  // Serialización binaria: guardamos primero la longitud y luego la contraseña
  // en binario
  out.write(reinterpret_cast<const char *>(&longitudPassword),
            sizeof(longitudPassword));            // longitud de la contraseña
  out.write(password.c_str(), longitudPassword);  // contraseña en binario
}

// Getters
string User::getNombre() { return nombre; }
string User::getContraseña() { return password; }
