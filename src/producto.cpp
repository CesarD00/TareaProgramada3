#include "producto.h"

#include<cstring>
#include<string>
#include<iostream>

using namespace std;

Producto::Producto() {
    this->id = {0};
    strcpy(this->nombre, "");
    this->numExistencias = {0};
}

Producto::Producto(int unaId, string unNombre, int cantExistencias) {
    this->id = unaId;
    strcpy(this->nombre, unNombre.c_str());
    this->numExistencias = cantExistencias;
}

Producto::~Producto(){
    
}

int Producto::obtenerId(){
    return this->id;
}

int Producto::obtenerNumExistencias(){
    return this->numExistencias;
}

char* Producto::obtenerNombre(){
    return this->nombre;
}

void Producto::asignarId(int unaId) {
    this->id = unaId;
}

void Producto::asignarNombre(string unNombre) {
    strcpy(this->nombre, unNombre.c_str());   
}

void Producto::asignarExistencias(int cantExistencias) {
    this->numExistencias = cantExistencias;
}

