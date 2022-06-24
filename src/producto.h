#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
#include<iostream>

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
    void asignarId(int unaId);
    void asignarNombre(string unNombre);
    void asignarExistencias(int cantExistencias);

};

#endif