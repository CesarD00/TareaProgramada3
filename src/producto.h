#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

using namespace std;

class Producto {
    int id;
    int numExistencias;
    char nombre[20];
    
    public:
    Producto();
    Producto(int unaId, string unNombre, int cantExistencias);
    ~Producto();
};

#endif