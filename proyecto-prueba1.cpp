#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Enumeración para los roles de usuario
enum class Rol { ADMINISTRADOR, EMPLEADO, CLIENTE };

// Clase para representar un libro
class Libro {
private:
    int id;
    string titulo;
    string autor;
    string genero;

public:
    // Constructor
    Libro(int id, const string& titulo, const string& autor, const string& genero)
        : id(id), titulo(titulo), autor(autor), genero(genero) {}

    // Método para obtener los datos del libro como cadena CSV
    string obtenerDatosCSV() const {
        stringstream ss;
        ss << id << "," << titulo << "," << autor << "," << genero;
        return ss.str();
    }

    // Método para imprimir los datos del libro
    void imprimirDatos() const {
        cout << "ID: " << id << ", Título: " << titulo << ", Autor: " << autor << ", Género: " << genero << endl;
    }

    // Getters
    int getId() const { return id; }
    string getTitulo() const { return titulo; }
    string getAutor() const { return autor; }
    string getGenero() const { return genero; }
};

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

// Función para realizar la compra de un libro por parte de un cliente
void comprarLibro(const Libro& libro, const string& nombreArchivo) {
    // Aquí se simularía la lógica de compra del libro, por ejemplo, marcar como vendido en el sistema
    cout << "Libro comprado: ";
    libro.imprimirDatos();
}

// Función para retirar un libro por parte de un cliente
void retirarLibro(const Libro& libro, const string& nombreArchivo) {
    // Aquí se simularía la lógica de retirar el libro, por ejemplo, marcar como prestado en el sistema
    cout << "Libro retirado: ";
    libro.imprimirDatos();
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
                // Lógica para agregar libro
                int id;
                string titulo, autor, genero;

                cout << "Ingrese ID del libro: ";
                cin >> id;
                cin.ignore(); // Limpiar el buffer
                cout << "Ingrese título del libro: ";
                getline(cin, titulo);
                cout << "Ingrese autor del libro: ";
                getline(cin, autor);
                cout << "Ingrese género del libro: ";
                getline(cin, genero);

                Libro nuevoLibro(id, titulo, autor, genero);
                agregarLibro(nuevoLibro, "biblioteca.csv");

            } else if (opcion == "2") {
                // Lógica para modificar libro
                int id;
                string titulo, autor, genero;

                cout << "Ingrese ID del libro a modificar: ";
                cin >> id;
                cin.ignore(); // Limpiar el buffer

                // Simular recuperación de datos actuales del libro y edición
                cout << "Ingrese nuevo título del libro: ";
                getline(cin, titulo);
                cout << "Ingrese nuevo autor del libro: ";
                getline(cin, autor);
                cout << "Ingrese nuevo género del libro: ";
                getline(cin, genero);

                Libro libroModificado(id, titulo, autor, genero);
                modificarLibro(id, libroModificado, "biblioteca.csv");

            } else if (opcion == "3") {
                // Lógica para eliminar libro
                int id;
                cout << "Ingrese ID del libro a eliminar: ";
                cin >> id;
                cin.ignore(); // Limpiar el buffer

                eliminarLibro(id, "biblioteca.csv");

            } else if (opcion == "4") {
                // Lógica para agregar usuario
                string nuevoUsuario, nuevaContrasena, rol;

                cout << "Ingrese nuevo usuario: ";
                getline(cin, nuevoUsuario);
                cout << "Ingrese nueva contraseña: ";
                getline(cin, nuevaContrasena);
                cout << "Ingrese rol (administrador, empleado, cliente): ";
                getline(cin, rol);

                agregarUsuario(nuevoUsuario, nuevaContrasena, rol, "credenciales.csv");

            } else if (opcion == "5") {
                // Lógica para suspender usuario
                string usuarioSuspender;

                cout << "Ingrese usuario a suspender: ";
                getline(cin, usuarioSuspender);

                suspenderUsuario(usuarioSuspender, "credenciales.csv");

            } else if (opcion == "6") {
                // Lógica para eliminar usuario
                string usuarioEliminar;

                cout << "Ingrese usuario a eliminar: ";
                getline(cin, usuarioEliminar);

                eliminarUsuario(usuarioEliminar, "credenciales.csv");

            } else if (opcion != "7") {
                cout << "Opción no válida. Intente de nuevo." << endl;
            }
        } else if (rolUsuario == Rol::EMPLEADO) {
            if (opcion == "1") {
                // Lógica para agregar libro
                int id;
                string titulo, autor, genero;

                cout << "Ingrese ID del libro: ";
                cin >> id;
                cin.ignore(); // Limpiar el buffer
                cout << "Ingrese título del libro: ";
                getline(cin, titulo);
                cout << "Ingrese autor del libro: ";
                getline(cin, autor);
                cout << "Ingrese género del libro: ";
                getline(cin, genero);

                Libro nuevoLibro(id, titulo, autor, genero);
                agregarLibro(nuevoLibro, "biblioteca.csv");

            } else if (opcion == "2") {
                // Lógica para modificar libro
                int id;
                string titulo, autor, genero;

                cout << "Ingrese ID del libro a modificar: ";
                cin >> id;
                cin.ignore(); // Limpiar el buffer

                // Simular recuperación de datos actuales del libro y edición
                cout << "Ingrese nuevo título del libro: ";
                getline(cin, titulo);
                cout << "Ingrese nuevo autor del libro: ";
                getline(cin, autor);
                cout << "Ingrese nuevo género del libro: ";
                getline(cin, genero);

                Libro libroModificado(id, titulo, autor, genero);
                modificarLibro(id, libroModificado, "biblioteca.csv");

            } else if (opcion == "3") {
                // Lógica para eliminar libro
                int id;
                cout << "Ingrese ID del libro a eliminar: ";
                cin >> id;
                cin.ignore(); // Limpiar el buffer

                eliminarLibro(id, "biblioteca.csv");

            } else if (opcion != "4") {
                cout << "Opción no válida. Intente de nuevo." << endl;
            }
        } else { // Rol::CLIENTE
            if (opcion == "1") {
                // Lógica para comprar libro
                int id;
                cout << "Ingrese ID del libro a comprar: ";
                cin >> id;
                cin.ignore(); // Limpiar el buffer

                // Simular recuperación de datos del libro y realizar la compra
                Libro libroComprar(id, "Título del libro", "Autor del libro", "Género del libro");
                comprarLibro(libroComprar, "biblioteca.csv");

            } else if (opcion == "2") {
                // Lógica para retirar libro
                int id;
                cout << "Ingrese ID del libro a retirar: ";
                cin >> id;
                cin.ignore(); // Limpiar el buffer

                // Simular recuperación de datos del libro y retirarlo
                Libro libroRetirar(id, "Título del libro", "Autor del libro", "Género del libro");
                retirarLibro(libroRetirar, "biblioteca.csv");

            } else if (opcion != "3") {
                cout << "Opción no válida. Intente de nuevo." << endl;
            }
        }

        cout << endl;

    } while (opcion != "3" && !(rolUsuario == Rol::EMPLEADO && opcion == "4")); // Salir para empleados solo con opción 4

    return 0;
}