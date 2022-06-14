#include "producto.h"

#include<cstring>
#include<string>

using namespace std;

Producto::Producto() {
    this->id = 0;
    strcpy(this->nombre, "");
    this->numExistencias = 0;
}

Producto::Producto(int unaId, string unNombre, int cantExistencias) {
    this->id = unaId;
    strcpy(this->nombre, unNombre.c_str());
    this->numExistencias = cantExistencias;
}


