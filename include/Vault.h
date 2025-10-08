#ifndef VAULT_H
#define VAULT_H

#include <string>

using namespace std;

class Vault {
 private:
  string rutaUsuario;  // Ejemplo: "data/carlos/"

 public:
  // Constructor: recibe el nombre del usuario y crea su directorio
  Vault(string& nombreUsuario);

  // Cifra un archivo y lo guarda en la boveda del usuario
  // - rutaOrigen: ruta del archivo a cifrar (ej: "/home/user/documento.txt")
  // - clave: password para cifrar
  void cifrarArchivo(const string& rutaOrigen, const string& clave);

  // Descifra un archivo de la boveda
  // - nombreArchivo: nombre del .enc en la boveda (ej: "documento.txt.enc")
  // - clave: password para descifrar
  // - rutaDestino: donde guardar el archivo descifrado
  void descifrarArchivo(const string& nombreArchivo, const string& clave,
                        const string& rutaDestino);

  // Descifra un archivo y lo guarda en la carpeta del usuario
  // - nombreArchivo: nombre del .enc en la boveda (ej: "documento.txt")
  // - clave: password para descifrar
  void descifrarArchivo(const string& nombreArchivo, const string& clave);

  // Lista todos los archivos cifrados en la boveda del usuario
  void listarArchivosCifrados() const;

  // Elimina un archivo cifrado de la boveda
  // - nombreArchivo: nombre del .enc a eliminar
  void eliminarArchivo(const string& nombreArchivo);
};

#endif