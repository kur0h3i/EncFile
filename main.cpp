#include <exception>
#include <iostream>
#include <string>

#include "User.h"
#include "Vault.h"

using namespace std;

int main() {
  int opcion = 0;
  User user("", "");  // Usuario vacío inicial
  bool autenticado = false;

  do {
    std::cout << "1. Registrarse" << '\n'
              << "2. Iniciar Sesion" << '\n'
              << "3. Salir" << '\n'
              << ">> ";
    std::cin >> opcion;

    // Panel Autenticacion
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
          autenticado = true;
          std::cout << "Login OK\n";
        } catch (std::exception& e) {
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

    // Autenticado - Crear instancia de Vault para el usuario
    while (autenticado) {
      string nombreUsuario = user.getNombre();
      Vault vault(nombreUsuario);

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
        case 1: {
          // Cifrar Archivos
          string rutaArchivo, clave;
          cout << "Ingrese la ruta completa del archivo a cifrar: ";
          cin.ignore();  // Limpiar buffer
          getline(cin, rutaArchivo);
          cout << "Ingrese la clave para cifrar: ";
          getline(cin, clave);

          try {
            vault.cifrarArchivo(rutaArchivo, clave);
            cout << "Archivo cifrado exitosamente.\n";
          } catch (const exception& e) {
            cout << "Error al cifrar el archivo: " << e.what() << "\n";
          }
          break;
        }
        case 2: {
          // Descifrar Archivos
          string nombreArchivo, clave;
          int opcionDestino;

          cout << "Ingrese el nombre del archivo cifrado (sin .enc): ";
          cin.ignore();  // Limpiar buffer
          getline(cin, nombreArchivo);
          cout << "Ingrese la clave para descifrar: ";
          getline(cin, clave);

          cout << "\n¿Dónde desea guardar el archivo descifrado?\n";
          cout << "1. En mi carpeta personal (data/" << user.getNombre()
               << "/)\n";
          cout << "2. En una ubicación específica\n";
          cout << ">> ";
          cin >> opcionDestino;

          try {
            if (opcionDestino == 1) {
              // Descifrar en la carpeta del usuario
              vault.descifrarArchivo(nombreArchivo, clave);
              cout << "Archivo descifrado exitosamente en data/"
                   << user.getNombre() << "/" << nombreArchivo << "\n";
            } else {
              // Descifrar en ubicación específica
              string rutaDestino;
              cout << "Ingrese la ruta donde guardar el archivo descifrado: ";
              cin.ignore();  // Limpiar buffer
              getline(cin, rutaDestino);
              vault.descifrarArchivo(nombreArchivo, clave, rutaDestino);
              cout << "Archivo descifrado exitosamente en " << rutaDestino
                   << "\n";
            }
          } catch (const exception& e) {
            cout << "Error al descifrar el archivo: " << e.what() << "\n";
          }
          break;
        }
        case 3: {
          // Listar Archivos Cifrados
          try {
            cout << "Archivos cifrados:\n";
            vault.listarArchivosCifrados();
          } catch (const exception& e) {
            cout << "Error al listar archivos: " << e.what() << "\n";
          }
          break;
        }
        case 4: {
          // Eliminar Archivo
          string nombreArchivo;
          cout << "Ingrese el nombre del archivo a eliminar (sin .enc): ";
          cin.ignore();  // Limpiar buffer
          getline(cin, nombreArchivo);

          try {
            vault.eliminarArchivo(nombreArchivo);
            cout << "Archivo eliminado exitosamente.\n";
          } catch (const exception& e) {
            cout << "Error al eliminar el archivo: " << e.what() << "\n";
          }
          break;
        }
        case 5:
          // Cerrar Sesion
          autenticado = false;
          std::cout << "Sesión cerrada.\n";
          break;
        default:
          std::cout << "Opción no válida.\n";
          break;
      }
    }
  } while (opcion != 3);

  return 0;
}
