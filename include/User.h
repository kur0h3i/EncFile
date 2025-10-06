#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
 private:
  // Atributos
  string nombre;
  string contraseña;

 public:
  // Constructor
  User(string nombre, string& contraseña);
  // Metodos
  User registarUsuario();
  bool iniciarSesion();
  void guardarUsuario();  // Getters
  string getNombre();
  string getContraseña();
};

#endif