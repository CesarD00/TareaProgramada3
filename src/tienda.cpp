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
}

Tienda::Tienda(){
    strcpy(this->nombre, "");
    strcpy(this->direccionInternet, "");
    strcpy(this->direccionFisica, "");
    strcpy(this->telefono, "");    
}

Tienda::~Tienda(){
    for(Producto* producto : this->productos) {
        delete producto;
    }
}

vector<Producto*> Tienda::obtenerProductos() {
    return this->productos;
}

void Tienda::insertarProducto(int unaId, string unNombre, int cantExistencias) {
    Producto* nuevoProducto = new Producto(unaId, unNombre, cantExistencias);

    this->productos.push_back(nuevoProducto);

}

void Tienda::insertarProducto(Producto* producto) {
    this->productos.push_back(producto);
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

void Tienda::cargarInformacionTiendaArchivoBinario(istream* entrada){
    entrada->seekg(0, ios::end);

    int cantidadBytes = entrada->tellg();
    int cantidadProductos = (cantidadBytes - 71) / sizeof(Producto);

    entrada->seekg(0, ios::beg);

    entrada->read(this->nombre, sizeof(this->nombre));
    entrada->read(this->direccionInternet, sizeof(this->direccionInternet));
    entrada->read(this->direccionFisica, sizeof(this->direccionFisica));
    entrada->read(this->telefono, sizeof(this->telefono));

    for(int i = 0; i < cantidadProductos; i++){
        Producto* nuevoProducto = new Producto();

        entrada->read((char*)nuevoProducto, sizeof(Producto));

        this->insertarProducto(nuevoProducto);
    }

}

char* Tienda::obtenerNombre(){
    return this->nombre;
}

char* Tienda::obtenerDireccionInternet(){
    return this->direccionInternet;
}

char* Tienda::obtenerDireccionFisica(){
    return this->direccionFisica;
}

char* Tienda::obtenerTelefono(){
    return this->telefono;
}

