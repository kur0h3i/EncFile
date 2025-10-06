#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
 private:
  // Atributos
  string nombre;
  string password;

 public:
  // Constructor
  User(string nombre, string password);
  // Metodos
  static User registarUsuario();
  static bool iniciarSesion(string nombre, string password);
  void guardarUsuario();
  // Getters
  string getNombre();
  string getContraseña();
};

#endif