#include "tienda.h"
#include <iostream>
#include <cstring>
#include "producto.h"

#include "excepcionStringTamanoExcedido.h"
#include "excepcionNumeroNegativo.h"
#include "excepcionPosicionNoExistente.h"
#include "excepcionIdNoEncontrada.h"

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

    if(unaDireccionF.length() > sizeof(this->direccionFisica)){
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

    this->productos.clear();

}

Tienda::Tienda(){
    strcpy(this->nombre, "");
    strcpy(this->direccionInternet, "");
    strcpy(this->direccionFisica, "");
    strcpy(this->telefono, ""); 

    this->productos.clear();
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
    bool encontrado = false;

    if(unaId < 0){
        throw ExcepcionNumeroNegativo();
    }

    for(const auto &producto : this->productos){
        if(producto.second->obtenerId() == unaId){
            encontrado = true;
        }
    }

    if(!encontrado){
        throw ExcepcionIdNoEncontrada();
    }

    this->productos.erase(unaId);
}

string Tienda::consultarProductosString(){
    int contador = 0;
    string informacion = "";

    for(const auto &producto : this->productos){
        contador++;

        informacion += "Producto " + to_string(contador) + "\n";

        informacion += "Id: " + to_string(producto.second->obtenerId()) + "\n";
        informacion += "Nombre: " + string(producto.second->obtenerNombre()) + "\n";
        informacion += "Cantidad de existencias: " + to_string(producto.second->obtenerNumExistencias()) + "\n";
    }

    return informacion;
}

map<int, Producto*> Tienda::consultarProductos(){
    return this->productos;
}

void Tienda::guardarInformacionTiendaArchivoBinario(ostream* salida) {
    // Escritura de la información general de la tienda
    salida->write(this->nombre, 15);
    salida->write(this->direccionInternet, 24);
    salida->write(this->direccionFisica, 24);
    salida->write(this->telefono, 8);

    // Escritura de los productos de la tienda
    for(const auto &producto : this->productos){
        salida->write((char *)producto.second, sizeof(Producto));
    }
}

void Tienda::cargarInformacionTiendaArchivoBinario(istream* entrada) {

    entrada->seekg(0, ios::end);

    int cantidadBytes = entrada->tellg();
    int cantidadProductos = (cantidadBytes - 71) / sizeof(Producto);

    entrada->seekg(0, ios::beg);

    entrada->read(this->nombre, 15);
    entrada->read(this->direccionInternet, 24);
    entrada->read(this->direccionFisica, 24);
    entrada->read(this->telefono, 8);

    this->productos.clear();

    entrada->seekg(71);

    for(int i = 0; i < cantidadProductos; i++){
        Producto* nuevoProducto = new Producto();

        entrada->read((char*)nuevoProducto, sizeof(Producto));

        this->insertarProducto(nuevoProducto);
    }

}

void Tienda::cargarProductoDesdeArchivoBinario(istream* entrada, int posicion) {
    entrada->seekg(0, ios::end);

    int cantidadBytes = entrada->tellg();
    int cantidadProductos = (cantidadBytes - 71) / sizeof(Producto);

    if(posicion < 0) {
        throw ExcepcionNumeroNegativo();
    }

    if(cantidadProductos <= posicion) {
        throw ExcepcionPosicionNoExistente();
    }

    entrada->seekg(71 + (sizeof(Producto) * posicion));

    Producto* producto = new Producto();

    entrada->read((char* )producto, sizeof(Producto));

    this->productos.clear();

    this->insertarProducto(producto); 
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
    int contador = 0;

    informacion = string("Datos de la tienda\n") + string("Nombre: ") + string(this->nombre) + "\n" + "Dirección de Internet: " + string(this->direccionInternet) + "\n" + "Dirección física: " + string(this->direccionFisica) + "\n" + "Número de teléfono: " + string(this->telefono) + "\n\n";

    informacion += "Productos\n";

    for(const auto &producto : this->productos){
        contador++;

        informacion += "Producto " + to_string(contador) + "\n";

        informacion += "Id: " + to_string(producto.second->obtenerId()) + "\n";
        informacion += "Nombre: " + string(producto.second->obtenerNombre()) + "\n";
        informacion += "Cantidad de existencias: " + to_string(producto.second->obtenerNumExistencias()) + "\n";
    }

    return informacion;
}

