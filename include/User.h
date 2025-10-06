#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
 private:
  // Atributos
  string nombre;
  string password;

  // Métodos privados estáticos
  static string hashPassword(const string& password);
  static bool usuarioExiste(const string& nombre);

 public:
  // Constructor
  User(string nombre, string password);

  // Métodos estáticos (no requieren instancia)
  static User registrarUsuario();
  static User iniciarSesion(string nombre, string password);
  static bool verificarContraseña(const string& almacenada,
                                  const string& ingresada);

  // Métodos de instancia
  void guardarUsuario();

  // Getters
  string getNombre();
  string getContraseña();
};

#endif