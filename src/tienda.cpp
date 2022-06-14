#include "tienda.h"
#include <iostream>
#include <cstring>
#include "producto.h"

using namespace std;
using namespace AdministradorExistencias;

Tienda::Tienda(string unNombre, string unaDireccionI, string unaDireccionF, string unTelefono){
    strcpy(this->nombre, unNombre.c_str());
    strcpy(this->direccionInternet, unaDireccionI.c_str());
    strcpy(this->direccionFisica, unaDireccionF.c_str());
    strcpy(this->telefono, unTelefono.c_str());

    this->productos = {};
}

vector<Producto*> Tienda::obtenerProductos() {
    return this->productos;
}

void Tienda::insertarProducto(int unaId, string unNombre, int cantExistencias) {
    Producto* nuevoProducto = new Producto(unaId, unNombre, cantExistencias);

    this->productos.push_back(nuevoProducto);

    delete nuevoProducto;
}

void Tienda::insertarProducto(Producto* nuevoProducto) {
    this->productos.push_back(nuevoProducto);
}

void Tienda::guardarInformacionTiendaArchivoBinario(ostream* salida) {
    // Escritura de la información general de la tienda
    salida->write(this->nombre, 15);
    salida->write(this->direccionInternet, 24);
    salida->write(this->direccionFisica, 24);
    salida->write(this->telefono, 8);

    // Escritura de los productos de la tienda
    for(Producto* producto : this->productos){
        salida->write((char *)producto, sizeof(Producto));
    }
}