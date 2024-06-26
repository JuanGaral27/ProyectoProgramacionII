#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

// Definimos un tipo para almacenar los usuarios y contraseñas
unordered_map<string, string> usuarios;

// Función para verificar si un usuario ya existe
bool existeUsuario(const string& usuario) {
    return usuarios.find(usuario) != usuarios.end();
}

// Función para agregar un nuevo usuario y contraseña
void agregarUsuario(const string& usuario, const string& clave) {
    usuarios[usuario] = clave;
    cout << "Usuario registrado correctamente." << endl;
}

// Función para verificar la contraseña de un usuario
bool verificarClave(const string& usuario, const string& clave) {
    if (existeUsuario(usuario)) {
        return usuarios[usuario] == clave;
    }
    return false;
}

int main() {
    string usuario, clave;
    char opcion;

    // Ejemplo de uso inicial
    usuarios["usuario1"] = "clave1";
    usuarios["usuario2"] = "clave2";

    do {
        cout << "Bienvenido al sistema de login" << endl;
        cout << "1. Ingresar" << endl;
        cout << "2. Registrarse" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese la opción deseada: ";
        cin >> opcion;

        switch (opcion) {
            case '1': {
                cout << "Ingrese su usuario: ";
                cin >> usuario;
                cout << "Ingrese su clave: ";
                cin >> clave;

                if (verificarClave(usuario, clave)) {
                    cout << "Inicio de sesión exitoso." << endl;
                } else {
                    cout << "Usuario o clave incorrectos." << endl;
                }
                break;
            }
            case '2': {
                cout << "Ingrese el usuario que desea registrar: ";
                cin >> usuario;

                if (existeUsuario(usuario)) {
                    cout << "El usuario ya existe. Pruebe con otro." << endl;
                } else {
                    cout << "Ingrese la clave para el usuario " << usuario << ": ";
                    cin >> clave;
                    agregarUsuario(usuario, clave);
                }
                break;
            }
            case '3': {
                cout << "Saliendo del programa." << endl;
                break;
            }
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != '3');

    return 0;
}
