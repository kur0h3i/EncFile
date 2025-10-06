#include <iostream>

#include "User.h"

int main() {
  User u = User::registarUsuario();

  std::string n, c;
  std::cout << "Login > usuario: ";
  std::cin >> n;
  std::cout << "Login > contrasena: ";
  std::cin >> c;

  if (User::iniciarSesion(n, c))
    std::cout << "Login OK\n";
  else
    std::cout << "Credenciales invalidas\n";
}
