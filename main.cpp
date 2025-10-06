#include <iostream>

#include "User.h"

int main() {
  int opcion = 0;
  User user("", "");  // Usuario vacío inicial
  bool autenticado = false;

  do {
    cout << "1. Registrarse" << '\n'
         << "2. Iniciar Sesion" << '\n'
         << "3. Salir" << '\n'
         << ">> ";
    cin >> opcion;

    // Panel Autenticacion
    switch (opcion) {
      case 1: {
        // Registro: crea y guarda el usuario
        user = user.registrarUsuario();
        break;
      }
      case 2: {
        // Login: pedir credenciales y verificar
        string nombre, contrasena;
        cout << "Usuario: ";
        cin >> nombre;
        cout << "Contrasena: ";
        cin >> contrasena;
        try {
          user = user.iniciarSesion(nombre, contrasena);
          autenticado = true;
          cout << "Login OK\n";
        } catch (exception& e) {
          cout << e.what() << "\n";
        }
        break;
      }
      case 3:
        cout << "Saliendo...\n";
        break;
      default:
        cout << "Opcion no valida\n";
        break;
    }

    // Autenticad
    while (autenticado) {
      int subOpcion = 0;
      cout << "--------------------\n"
           << "Usuario : " << user.getNombre() << '\n'
           << "------- Menú -------\n"
           << "1. Cifrar Archivo\n"
           << "2. Descifrar archivo\n"
           << "3. Listar archivos cifrados\n"
           << "4. Eliminar archivo\n"
           << "5. Cerrar sesión\n"
           << ">> ";
      cin >> subOpcion;

      // Menu
      switch (subOpcion) {
        case 1:
          // Cifrar Archivos
          break;
        case 2:
          // Descifrar Archivos
          break;
        case 3:
          // Listar Archivos Cifrados
          break;
        case 4:
          // Eliminar Archivo
          break;
        case 5:
          // Cerrar Sesion
          autenticado = false;
          cout << "Sesión cerrada.\n";
          break;
        default:
          cout << "Opción no válida.\n";
          break;
      }
    }
  } while (opcion != 3);

  return 0;
}
