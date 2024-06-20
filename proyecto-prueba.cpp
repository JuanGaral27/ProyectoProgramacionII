#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Función para verificar el usuario y contraseña
bool verificarCredenciales(const string& usuario, const string& contrasena, const string& DataCSV) {
    ifstream archivo(DataCSV);  // Abrir el archivo CSV

    if (!archivo) {
        cerr << "No se pudo abrir el archivo " << DataCSV << endl;
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {  // Leer cada línea del archivo
        stringstream ss(linea);
        string usuarioArchivo, contrasenaArchivo;
        
        // Leer usuario y contraseña separados por coma
        getline(ss, usuarioArchivo, ',');
        getline(ss, contrasenaArchivo);
        
        // Comparar usuario y contraseña
        if (usuario == usuarioArchivo && contrasena == contrasenaArchivo) {
            archivo.close();
            return true;  // Si coinciden, retornar verdadero
        }
    }

    archivo.close();
    return false;  // Si no se encontró coincidencia, retornar falso
}

int main() {
    string usuario, contrasena;

    // Pedir al usuario que ingrese usuario y contraseña
    cout << "Ingrese su usuario: ";
    getline(cin, usuario);
    cout << "Ingrese su contrasena: ";
    getline(cin, contrasena);

    // Verificar credenciales usando la función
    if (verificarCredenciales(usuario, contrasena, "credenciales.csv")) {
        cout << "Inicio de sesion exitoso. Bienvenido!" << endl;
    } else {
        cout << "Credenciales incorrectas. Inicio de sesion fallido." << endl;
    }

    return 0;
}
