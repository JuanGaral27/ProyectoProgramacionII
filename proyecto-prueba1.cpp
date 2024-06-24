#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Enumeración para los roles de usuario
enum class Rol { ADMINISTRADOR, EMPLEADO, CLIENTE };

// Función para verificar el usuario y contraseña y determinar el rol
Rol verificarCredenciales(const string& usuario, const string& contrasena, const string& DataCSV) {
    ifstream archivo(DataCSV);  // Abrir el archivo CSV

    if (!archivo) {
        cerr << "No se pudo abrir el archivo " << DataCSV << endl;
        return Rol::CLIENTE;  // En caso de error, se considera cliente por defecto
    }

    string linea;
    while (getline(archivo, linea)) {  // Leer cada línea del archivo
        stringstream ss(linea);
        string usuarioArchivo, contrasenaArchivo, rolArchivo;
        
        // Leer usuario, contraseña y rol separados por coma
        getline(ss, usuarioArchivo, ',');
        getline(ss, contrasenaArchivo, ',');
        getline(ss, rolArchivo);
        
        // Comparar usuario y contraseña
        if (usuario == usuarioArchivo && contrasena == contrasenaArchivo) {
            archivo.close();
            
            // Determinar el rol del usuario
            if (rolArchivo == "administrador") {
                return Rol::ADMINISTRADOR;
            } else if (rolArchivo == "empleado") {
                return Rol::EMPLEADO;
            } else {
                return Rol::CLIENTE;
            }
        }
    }

    archivo.close();
    return Rol::CLIENTE;  // Si no se encontró coincidencia, se considera cliente por defecto
}

// Función para agregar un libro a un archivo CSV
void agregarLibro(const Libro& libro, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::app); // Abrir el archivo en modo append

    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    archivo << libro.obtenerDatosCSV() << endl;
    archivo.close();

    cout << "Libro agregado correctamente." << endl;
}

// Función para modificar un libro en un archivo CSV
void modificarLibro(int id, const Libro& libro, const string& nombreArchivo) {
    ifstream archivoEntrada(nombreArchivo);
    ofstream archivoSalida("temp.csv"); // Archivo temporal para escribir los datos modificados

    if (!archivoEntrada || !archivoSalida) {
        cerr << "Error al abrir los archivos" << endl;
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivoEntrada, linea)) {
        stringstream ss(linea);
        string token;
        getline(ss, token, ',');

        int idActual = stoi(token); // Convertir el ID a entero

        if (idActual == id) {
            archivoSalida << libro.obtenerDatosCSV() << endl;
            encontrado = true;
        } else {
            archivoSalida << linea << endl;
        }
    }

    archivoEntrada.close();
    archivoSalida.close();

    // Renombrar el archivo temporal al original
    remove(nombreArchivo.c_str());
    rename("temp.csv", nombreArchivo.c_str());

    if (!encontrado) {
        cout << "Libro no encontrado con ID " << id << endl;
    } else {
        cout << "Libro modificado correctamente." << endl;
    }
}

// Función para eliminar un libro de un archivo CSV
void eliminarLibro(int id, const string& nombreArchivo) {
    ifstream archivoEntrada(nombreArchivo);
    ofstream archivoSalida("temp.csv"); // Archivo temporal para escribir los datos sin el libro eliminado

    if (!archivoEntrada || !archivoSalida) {
        cerr << "Error al abrir los archivos" << endl;
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivoEntrada, linea)) {
        stringstream ss(linea);
        string token;
        getline(ss, token, ',');

        int idActual = stoi(token); // Convertir el ID a entero

        if (idActual != id) {
            archivoSalida << linea << endl;
        } else {
            encontrado = true;
        }
    }

    archivoEntrada.close();
    archivoSalida.close();

    // Renombrar el archivo temporal al original
    remove(nombreArchivo.c_str());
    rename("temp.csv", nombreArchivo.c_str());

    if (!encontrado) {
        cout << "Libro no encontrado con ID " << id << endl;
    } else {
        cout << "Libro eliminado correctamente." << endl;
    }
}

// Función para agregar un usuario a un archivo CSV
void agregarUsuario(const string& usuario, const string& contrasena, const string& rol, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::app); // Abrir el archivo en modo append

    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    archivo << usuario << "," << contrasena << "," << rol << endl;
    archivo.close();

    cout << "Usuario agregado correctamente." << endl;
}

// Función para suspender un usuario en un archivo CSV
void suspenderUsuario(const string& usuario, const string& nombreArchivo) {
    ifstream archivoEntrada(nombreArchivo);
    ofstream archivoSalida("temp.csv"); // Archivo temporal para escribir los datos modificados

    if (!archivoEntrada || !archivoSalida) {
        cerr << "Error al abrir los archivos" << endl;
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivoEntrada, linea)) {
        stringstream ss(linea);
        string usuarioArchivo, contrasenaArchivo, rolArchivo;

        getline(ss, usuarioArchivo, ',');
        getline(ss, contrasenaArchivo, ',');
        getline(ss, rolArchivo);

        if (usuario == usuarioArchivo) {
            archivoSalida << usuarioArchivo << "," << contrasenaArchivo << "," << "suspendido" << endl;
            encontrado = true;
        } else {
            archivoSalida << linea << endl;
        }
    }

    archivoEntrada.close();
    archivoSalida.close();

    // Renombrar el archivo temporal al original
    remove(nombreArchivo.c_str());
    rename("temp.csv", nombreArchivo.c_str());

    if (!encontrado) {
        cout << "Usuario no encontrado: " << usuario << endl;
    } else {
        cout << "Usuario suspendido correctamente." << endl;
    }
}

// Función para eliminar un usuario de un archivo CSV
void eliminarUsuario(const string& usuario, const string& nombreArchivo) {
    ifstream archivoEntrada(nombreArchivo);
    ofstream archivoSalida("temp.csv"); // Archivo temporal para escribir los datos sin el usuario eliminado

    if (!archivoEntrada || !archivoSalida) {
        cerr << "Error al abrir los archivos" << endl;
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(archivoEntrada, linea)) {
        stringstream ss(linea);
        string usuarioArchivo, contrasenaArchivo, rolArchivo;

        getline(ss, usuarioArchivo, ',');
        getline(ss, contrasenaArchivo, ',');
        getline(ss, rolArchivo);

        if (usuario != usuarioArchivo) {
            archivoSalida << linea << endl;
        } else {
            encontrado = true;
        }
    }

    archivoEntrada.close();
    archivoSalida.close();

    // Renombrar el archivo temporal al original
    remove(nombreArchivo.c_str());
    rename("temp.csv", nombreArchivo.c_str());

    if (!encontrado) {
        cout << "Usuario no encontrado: " << usuario << endl;
    } else {
        cout << "Usuario eliminado correctamente." << endl;
    }
}

int main() {
    string usuario, contrasena;
    Rol rolUsuario;

    // Pedir al usuario que ingrese usuario y contraseña
    cout << "Ingrese su usuario: ";
    getline(cin, usuario);
    cout << "Ingrese su contrasena: ";
    getline(cin, contrasena);

    // Verificar credenciales y obtener el rol del usuario
    rolUsuario = verificarCredenciales(usuario, contrasena, "credenciales.csv");

    switch (rolUsuario) {
        case Rol::ADMINISTRADOR:
            cout << "Inicio de sesion exitoso como Administrador. Bienvenido!" << endl;
            break;
        case Rol::EMPLEADO:
            cout << "Inicio de sesion exitoso como Empleado. Bienvenido!" << endl;
            break;
        case Rol::CLIENTE:
            cout << "Inicio de sesion exitoso como Cliente. Bienvenido!" << endl;
            break;
    }

    string opcion;

    do {
        cout << "Menu:" << endl;
        if (rolUsuario == Rol::ADMINISTRADOR) {
            cout << "1. Agregar libro" << endl;
            cout << "2. Modificar libro" << endl;
            cout << "3. Eliminar libro" << endl;
            cout << "4. Agregar usuario" << endl;
            cout << "5. Suspender usuario" << endl;
            cout << "6. Eliminar usuario" << endl;
            cout << "7. Salir" << endl;
        } else if (rolUsuario == Rol::EMPLEADO) {
            cout << "1. Agregar libro" << endl;
            cout << "2. Modificar libro" << endl;
            cout << "3. Eliminar libro" << endl;
            cout << "4. Salir" << endl;
        } else { // Rol::CLIENTE
            cout << "1. Comprar libro" << endl;
            cout << "2. Retirar libro" << endl;
            cout << "3. Salir" << endl;
        }
        cout << "Ingrese opción: ";
        getline(cin, opcion);

        if (rolUsuario == Rol::ADMINISTRADOR) {
            if (opcion == "1") {
                // Lógica para agregar libro (ya implementado)
            } else if (opcion == "2") {
                // Lógica para modificar libro (ya implementado)
            } else if (opcion == "3") {
                // Lógica para eliminar libro (ya implementado)
            } else if (opcion == "4") {
                // Lógica para agregar usuario (ya implementado)
            } else if (opcion == "5") {
                // Lógica para suspender usuario (ya implementado)
            } else if (opcion == "6") {
                // Lógica para eliminar usuario (ya implementado)
            } else if (opcion != "7") {
                cout << "Opción no válida. Intente de nuevo." << endl;
            }
        } else if (rolUsuario == Rol::EMPLEADO) {
            if (opcion == "1") {
                // Lógica para agregar libro (ya implementado)
            } else if (opcion == "2") {
                // Lógica para modificar libro (ya implementado)
            } else if (opcion == "3") {
                // Lógica para eliminar libro (ya implementado)
            } else if (opcion != "4") {
                cout << "Opción no válida. Intente de nuevo." << endl;
            }
        } else { // Rol::CLIENTE
            if (opcion == "1") {
                // Lógica para comprar libro
            } else if (opcion == "2") {
                // Lógica para retirar libro
            } else if (opcion != "3") {
                cout << "Opción no válida. Intente de nuevo." << endl;
            }
        }

        cout << endl;

    } while (opcion != "3" && !(rolUsuario == Rol::EMPLEADO && opcion == "4")); // Salir para empleados solo con opción 4

    return 0;
}
