#include "tienda.h"
#include <iostream>
#include <cstring>
#include "producto.h"

#include "excepcionStringTamanoExcedido.h"
#include "excepcionNumeroNegativo.h"

using namespace std;
using namespace AdministradorExistencias;

Tienda::Tienda(string unNombre, string unaDireccionI, string unaDireccionF, string unTelefono){
    
    if(unNombre.length() > sizeof(this->nombre)){
        throw ExcepcionStringTamanoExcedido();
    }
    else{
        strcpy(this->nombre, unNombre.c_str());    
    }

    if(unaDireccionI.length() > sizeof(this->direccionInternet)){
        throw ExcepcionStringTamanoExcedido();
    }
    else{
        strcpy(this->direccionInternet, unaDireccionI.c_str());     
    }  

    if(unNombre.length() > sizeof(this->nombre)){
        throw ExcepcionStringTamanoExcedido();
    }
    else{
        strcpy(this->direccionFisica, unaDireccionF.c_str());  
    }  

    if(unTelefono.length() > sizeof(this->telefono)){
        throw ExcepcionStringTamanoExcedido();
    }
    else{
        strcpy(this->telefono, unTelefono.c_str());    
    }    
}

Tienda::Tienda(){
    strcpy(this->nombre, "");
    strcpy(this->direccionInternet, "");
    strcpy(this->direccionFisica, "");
    strcpy(this->telefono, ""); 
}

Tienda::~Tienda(){
    for(const auto &producto : this->productos){
        delete producto.second;
    }
}

map<int, Producto*> Tienda::obtenerProductos() {
    return this->productos;
}

void Tienda::insertarProducto(int unaId, string unNombre, int cantExistencias) {
    try{
        Producto* nuevoProducto = new Producto(unaId, unNombre, cantExistencias);
        this->productos.insert(pair<int, Producto*>(unaId, nuevoProducto));
    }
    catch(ExcepcionStringTamanoExcedido ex){
        ex.what();
    }
    catch(ExcepcionNumeroNegativo ex){
        ex.what();
    }
    
}

void Tienda::insertarProducto(Producto* producto) {
    this->productos.insert(pair<int, Producto*>(producto->obtenerId(), producto));
}

void Tienda::modificarProducto(int unaId, string unNombre, int cantExistencias) {
    try{
        this->productos.at(unaId)->asignarNombre(unNombre);
        this->productos.at(unaId)->asignarExistencias(cantExistencias);   
    }
    catch(ExcepcionStringTamanoExcedido ex){
        ex.what();
    }
    catch(ExcepcionNumeroNegativo ex){
        ex.what();
    }
}

void Tienda::eliminarProducto(int unaId) {
    this->productos.erase(unaId);
}

void Tienda::guardarInformacionTiendaArchivoBinario(ostream* salida) {
    // Escritura de la información general de la tienda
    salida->write(this->nombre, sizeof(this->nombre));
    salida->write(this->direccionInternet, sizeof(this->direccionInternet));
    salida->write(this->direccionFisica, sizeof(this->direccionFisica));
    salida->write(this->telefono, sizeof(this->telefono));

    // Escritura de los productos de la tienda
    for(const auto &producto : this->productos){
        salida->write((char *)producto.second, sizeof(Producto));
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

string Tienda::toString() {
    string informacion = "";

    informacion += string(this->nombre) + " " + string(this->direccionInternet) + " " + string(this->direccionFisica) + " " + string(this->telefono);

    for(const auto &producto : this->productos){
        informacion += producto.second->obtenerId() + " ";
        informacion += string(producto.second->obtenerNombre()) + " ";
        informacion += producto.second->obtenerNumExistencias() + " ";
    }

    return informacion;
}

