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

  // Métodos
  User registrarUsuario();
  User iniciarSesion(string nombre, string password);
  void guardarUsuario();

  // Getters
  string getNombre();
  string getContraseña();
};

#endif