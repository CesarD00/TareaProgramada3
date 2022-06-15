#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

using namespace std;

class Producto {
    int id;
    char nombre[20];
    int numExistencias;
    
    public:
    Producto();
    Producto(int unaId, string unNombre, int cantExistencias);
    ~Producto();
    int obtenerId();
    int obtenerNumExistencias();
    char* obtenerNombre();
};

#endif