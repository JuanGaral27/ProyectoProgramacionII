#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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