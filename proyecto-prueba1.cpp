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
