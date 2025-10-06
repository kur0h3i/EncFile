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
User User::registarUsuario() {
  string nombre;
  string password;

  cout << "Nombre : ";
  cin >> nombre;
  cout << "Contraseña : ";
  cin >> password;

  User u(nombre, password);
  if (iniciarSesion(nombre, password)) {
    cout << "Usuario ya existe";
  } else {
    u.guardarUsuario();
    cout << "Registrado Correctamente\n";
    }
  return u;
}

bool User::iniciarSesion(string nombre, string password) {
  // Abrir el archivo binario de usuarios
  ifstream in("data/users.dat", ios::binary);
  if (!in) return false;

  while (true) {
    size_t lonN, lonP;
    string n, p;

    // Leer la longitud del nombre
    in.read(reinterpret_cast<char *>(&lonN), sizeof(lonN));
    if (in.eof()) break;

    // Deserialización binaria:
    // Leemos primero la longitud y luego el nombre en binario
    n.resize(lonN);
    in.read(&n[0], lonN);

    // Leer la longitud de la contraseña
    in.read(reinterpret_cast<char *>(&lonP), sizeof(lonP));
    if (in.eof()) break;

    // Deserialización binaria:
    // Leemos primero la longitud y luego la contraeña en binario
    p.resize(lonP);
    in.read(&p[0], lonP);

    if (n == nombre && p == password) return true;
  }
  return false;
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
