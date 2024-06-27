#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_USUARIOS = 200;
const int MAX_LIBROS = 200;

// Definición de estructuras
struct Usuario {
    string nombre;
    string apellido;
    string cedula;
    string username;
    string password;
    string accState;
    string role;
    float balance;
};

struct Libro {
    string titulo;
    string autor;
    int año;
    string genero;
    float precio_renta;
    float precio_compra;
    int codigo;
    string estado;
    string rentedBy; // Usuario que ha retirado el libro
};

// Prototipos de funciones
void cargarUsuarios(Usuario usuarios[], int &numUsuarios);
void guardarUsuarios(const Usuario usuarios[], int numUsuarios);
void cargarLibros(Libro libros[], int &numLibros);
void guardarLibros(const Libro libros[], int numLibros);
bool autenticarUsuario(const string &username, const string &password, const Usuario usuarios[], int numUsuarios, int &indiceUsuario);
void registrarNuevoUsuario(Usuario usuarios[], int &numUsuarios);
void menuPrincipal(const Usuario &currentUser, Usuario usuarios[], int numUsuarios, Libro libros[], int numLibros);
void menuAdmin(const Usuario &currentUser, Usuario usuarios[], int numUsuarios, Libro libros[], int numLibros);
void menuEmpleado(const Usuario &currentUser, Usuario usuarios[], int numUsuarios, Libro libros[], int numLibros);
void menuCliente(const Usuario &currentUser, Usuario usuarios[], int numUsuarios, Libro libros[], int numLibros);
void comprarLibro(const Usuario &currentUser, Libro libros[], int numLibros);
void retirarLibro(const Usuario &currentUser, Libro libros[], int numLibros);
void devolverLibro(const Usuario &currentUser, Libro libros[], int numLibros);

// Función principal
int main() {
    Usuario usuarios[MAX_USUARIOS];
    Libro libros[MAX_LIBROS];
    int numUsuarios = 0;
    int numLibros = 0;
    string username, password;
    int indiceUsuario = -1;

    cargarUsuarios(usuarios, numUsuarios);
    cargarLibros(libros, numLibros);

    // Inicio de sesión
    cout << "Bienvenido a la Biblioteca!" << endl;
    cout << "Ingrese su nombre de usuario y contraseña:" << endl;
    cout << "Usuario: ";
    cin >> username;
    cout << "Contraseña: ";
    cin >> password;

    // Autenticación del usuario
    if (!autenticarUsuario(username, password, usuarios, numUsuarios, indiceUsuario)) {
        cout << "Usuario o contraseña incorrectos. Inténtelo nuevamente." << endl;
        return 1;
    }

    // Menú principal según el rol del usuario
    menuPrincipal(usuarios[indiceUsuario], usuarios, numUsuarios, libros, numLibros);

    // Guardar datos al salir del programa
    guardarUsuarios(usuarios, numUsuarios);
    guardarLibros(libros, numLibros);

    return 0;
}

// Función para cargar usuarios desde el archivo
void cargarUsuarios(Usuario usuarios[], int &numUsuarios) {
    ifstream archivo("./assets/dataProject.csv");
    string linea;

    if (archivo.is_open()) {
        getline(archivo, linea); // Ignorar la primera línea (cabecera)

        while (getline(archivo, linea) && numUsuarios < MAX_USUARIOS) {
            stringstream ss(linea);
            getline(ss, usuarios[numUsuarios].nombre, ',');
            getline(ss, usuarios[numUsuarios].apellido, ',');
            getline(ss, usuarios[numUsuarios].cedula, ',');
            getline(ss, usuarios[numUsuarios].username, ',');
            getline(ss, usuarios[numUsuarios].password, ',');
            getline(ss, usuarios[numUsuarios].accState, ',');
            getline(ss, usuarios[numUsuarios].role, ',');
            ss >> usuarios[numUsuarios].balance;

            numUsuarios++;
        }

        archivo.close();
    }
}

// Función para guardar usuarios en el archivo
void guardarUsuarios(const Usuario usuarios[], int numUsuarios) {
    ofstream archivo("./assets/dataProject.csv");
    archivo << "nombre,apellido,cedula,username,password,accState,role,balance\n";

    for (int i = 0; i < numUsuarios; ++i) {
        archivo << usuarios[i].nombre << ','
                << usuarios[i].apellido << ','
                << usuarios[i].cedula << ','
                << usuarios[i].username << ','
                << usuarios[i].password << ','
                << usuarios[i].accState << ','
                << usuarios[i].role << ','
                << fixed << setprecision(2) << usuarios[i].balance << '\n';
    }

    archivo.close();
}

// Función para cargar libros desde el archivo
void cargarLibros(Libro libros[], int &numLibros) {
    ifstream archivo("./assets/books.csv");
    string linea;

    if (archivo.is_open()) {
        getline(archivo, linea); // Ignorar la primera línea (cabecera)

        while (getline(archivo, linea) && numLibros < MAX_LIBROS) {
            stringstream ss(linea);
            getline(ss, libros[numLibros].titulo, ',');
            getline(ss, libros[numLibros].autor, ',');
            ss >> libros[numLibros].año;
            ss.ignore(); // Ignorar la coma
            getline(ss, libros[numLibros].genero, ',');
            ss >> libros[numLibros].precio_renta;
            ss.ignore(); // Ignorar la coma
            ss >> libros[numLibros].precio_compra;
            ss.ignore(); // Ignorar la coma
            ss >> libros[numLibros].codigo;
            getline(ss, libros[numLibros].estado, ',');
            getline(ss, libros[numLibros].rentedBy);

            numLibros++;
        }

        archivo.close();
    }
}

// Función para guardar libros en el archivo
void guardarLibros(const Libro libros[], int numLibros) {
    ofstream archivo("./assets/books.csv");
    archivo << "titulo,autor,año,genero,precio_renta,precio_compra,codigo,estado,rentedBy\n";

    for (int i = 0; i < numLibros; ++i) {
        archivo << libros[i].titulo << ','
                << libros[i].autor << ','
                << libros[i].año << ','
                << libros[i].genero << ','
                << fixed << setprecision(2) << libros[i].precio_renta << ','
                << fixed << setprecision(2) << libros[i].precio_compra << ','
                << libros[i].codigo << ','
                << libros[i].estado << ','
                << libros[i].rentedBy << '\n';
    }

    archivo.close();
}

// Función para autenticar usuario
bool autenticarUsuario(const string &username, const string &password, const Usuario usuarios[], int numUsuarios, int &indiceUsuario) {
    for (int i = 0; i < numUsuarios; ++i) {
        if (usuarios[i].username == username && usuarios[i].password == password) {
            indiceUsuario = i;
            return true;
        }
    }
    return false;
}

// Función para registrar un nuevo usuario
void registrarNuevoUsuario(Usuario usuarios[], int &numUsuarios) {
    if (numUsuarios >= MAX_USUARIOS) {
        cout << "No se pueden agregar más usuarios. Capacidad máxima alcanzada." << endl;
        return;
    }

    Usuario nuevoUsuario;

    cout << "Ingrese el nombre del nuevo usuario: ";
    cin >> nuevoUsuario.nombre;
    cout << "Ingrese el apellido del nuevo usuario: ";
    cin >> nuevoUsuario.apellido;
    cout << "Ingrese la cédula del nuevo usuario: ";
    cin >> nuevoUsuario.cedula;
    cout << "Ingrese el nombre de usuario para esta cuenta: ";
    cin >> nuevoUsuario.username;
    cout << "Ingrese la contraseña a utilizar por esta cuenta: ";
    cin >> nuevoUsuario.password;
    nuevoUsuario.accState = "activo";
    cout << "Ingrese el tipo de usuario a ser registrado (cliente, empleado, administrador): ";
    cin >> nuevoUsuario.role;
    cout << "Ingrese el saldo inicial del usuario: ";
    cin >> nuevoUsuario.balance;

    usuarios[numUsuarios] = nuevoUsuario;
    numUsuarios++;

    guardarUsuarios(usuarios, numUsuarios);

    cout << "Usuario registrado exitosamente." << endl;
}

// Menú principal según el rol del usuario
void menuPrincipal(const Usuario &currentUser, Usuario usuarios[], int numUsuarios, Libro libros[], int numLibros) {
    cout << "Bienvenido, " << currentUser.nombre << "!" << endl;
    cout << "Rol: " << currentUser.role << endl;

    if (currentUser.role == "administrador") {
        menuAdmin(currentUser, usuarios, numUsuarios, libros, numLibros);
    } else if (currentUser.role == "empleado") {
        menuEmpleado(currentUser, usuarios, numUsuarios, libros, numLibros);
    } else if (currentUser.role == "cliente") {
        menuCliente(currentUser, usuarios, numUsuarios, libros, numLibros);
    }
}

// Menú de opciones para administrador
void menuAdmin(const Usuario &currentUser, Usuario usuarios[], int numUsuarios, Libro libros[], int numLibros) {
    int opcion;

    do {
        cout << "\nMenú Administrador:" << endl;
        cout << "1. Registrar nuevo usuario" << endl;
        cout << "2. Listar todos los usuarios" << endl;
        cout << "3. Listar todos los libros" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarNuevoUsuario(usuarios, numUsuarios);
                break;
            case 2:
                cout << "\nListado de Usuarios:" << endl;
                for (int i = 0; i < numUsuarios; ++i) {
                    cout << usuarios[i].nombre << " " << usuarios[i].apellido << " - " << usuarios[i].role << endl;
                }
                break;
            case 3:
                cout << "\nListado de Libros:" << endl;
                for (int i = 0; i < numLibros; ++i) {
                    cout << libros[i].titulo << " by " << libros[i].autor << " - " << libros[i].estado << endl;
                }
                break;
            case 4:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }
    } while (opcion != 4);
}
// Menú de opciones para empleado
void menuEmpleado(const Usuario &currentUser, Usuario usuarios[], int numUsuarios, Libro libros[], int numLibros) {
    int opcion;

    do {
        cout << "\nMenú Empleado:" << endl;
        cout << "1. Listar todos los libros" << endl;
        cout << "2. Retirar libro" << endl;
        cout << "3. Devolver libro" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\nListado de Libros:" << endl;
                for (int i = 0; i < numLibros; ++i) {
                    cout << libros[i].titulo << " by " << libros[i].autor << " - " << libros[i].estado << endl;
                }
                break;
            case 2:
                retirarLibro(currentUser, libros, numLibros);
                break;
            case 3:
                devolverLibro(currentUser, libros, numLibros);
                break;
            case 4:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }
    } while (opcion != 4);
}

// Menú de opciones para cliente
void menuCliente(const Usuario &currentUser, Usuario usuarios[], int numUsuarios, Libro libros[], int numLibros) {
    int opcion;

    do {
        cout << "\nMenú Cliente:" << endl;
        cout << "1. Listar todos los libros" << endl;
        cout << "2. Comprar libro" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\nListado de Libros:" << endl;
                for (int i = 0; i < numLibros; ++i) {
                    cout << libros[i].titulo << " by " << libros[i].autor << " - " << libros[i].estado << endl;
                }
                break;
            case 2:
                comprarLibro(currentUser, libros, numLibros);
                break;
            case 3:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }
    } while (opcion != 3);
}

// Función para comprar un libro
void comprarLibro(const Usuario &currentUser, Libro libros[], int numLibros) {
    int codigoLibro;
    bool libroEncontrado = false;

    cout << "Ingrese el código del libro que desea comprar: ";
    cin >> codigoLibro;

    for (int i = 0; i < numLibros; ++i) {
        if (libros[i].codigo == codigoLibro && libros[i].estado == "disponible") {
            libros[i].estado = "vendido";
            libroEncontrado = true;
            cout << "Libro comprado exitosamente!" << endl;
            break;
        }
    }

    if (!libroEncontrado) {
        cout << "Libro no encontrado o no disponible para compra." << endl;
    }

    guardarLibros(libros, numLibros);
}

// Función para retirar un libro
void retirarLibro(const Usuario &currentUser, Libro libros[], int numLibros) {
    int codigoLibro;
    bool libroEncontrado = false;

    cout << "Ingrese el código del libro que desea retirar: ";
    cin >> codigoLibro;

    for (int i = 0; i < numLibros; ++i) {
        if (libros[i].codigo == codigoLibro && libros[i].estado == "disponible") {
            libros[i].estado = "retirado";
            libros[i].rentedBy = currentUser.username;
            libroEncontrado = true;
            cout << "Libro retirado exitosamente!" << endl;
            break;
        }
    }

    if (!libroEncontrado) {
        cout << "Libro no encontrado o no disponible para retirar." << endl;
    }

    guardarLibros(libros, numLibros);
}

// Función para devolver un libro
void devolverLibro(const Usuario &currentUser, Libro libros[], int numLibros) {
    int codigoLibro;
    bool libroEncontrado = false;

    cout << "Ingrese el código del libro que desea devolver: ";
    cin >> codigoLibro;

    for (int i = 0; i < numLibros; ++i) {
        if (libros[i].codigo == codigoLibro && libros[i].estado == "retirado" && libros[i].rentedBy == currentUser.username) {
            libros[i].estado = "disponible";
            libros[i].rentedBy = "";
            libroEncontrado = true;
            cout << "Libro devuelto exitosamente!" << endl;
            break;
        }
    }

    if (!libroEncontrado) {
        cout << "Libro no encontrado o no pertenece a este usuario." << endl;
    }

    guardarLibros(libros, numLibros);
}