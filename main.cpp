#include <iostream>

#include "User.h"

int main() {
  int opcion = 0;
  User user("", "");  // Usuario vacío inicial

  do {
    std::cout << "1. Registrarse" << '\n'
              << "2. Iniciar Sesion" << '\n'
              << "3. Salir" << '\n'
              << ">> ";
    std::cin >> opcion;

    switch (opcion) {
      case 1: {
        // Registro: crea y guarda el usuario
        user = user.registrarUsuario();
        break;
      }
      case 2: {
        // Login: pedir credenciales y verificar
        std::string nombre, contrasena;
        std::cout << "Usuario: ";
        std::cin >> nombre;
        std::cout << "Contrasena: ";
        std::cin >> contrasena;
        try {
          user = user.iniciarSesion(nombre, contrasena);
          std::cout << "Login OK\n";
        } catch (const std::exception& e) {
          std::cout << e.what() << "\n";
        }
        break;
      }
      case 3:
        std::cout << "Saliendo...\n";
        break;
      default:
        std::cout << "Opcion no valida\n";
        break;
    }
  } while (opcion != 3);

  return 0;
}
