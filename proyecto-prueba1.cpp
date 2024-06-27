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
