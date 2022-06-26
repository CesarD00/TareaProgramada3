#ifndef TIENDA_H
#define TIENDA_H

#include<string>
#include<vector>
#include<iostream>
#include<map>

#include "producto.h"

using namespace std;

namespace AdministradorExistencias {

    class Tienda {
        char nombre[15];
        char direccionInternet[24];
        char direccionFisica[24];
        char telefono[8];
        map<int, Producto*> productos {};

        public:
        Tienda(string unNombre, string unaDireccionI, string unaDireccionF, string unTelefono);
        Tienda();
        ~Tienda();
        map<int, Producto*> obtenerProductos();
        void insertarProducto(int unaId, string unNombre, int cantExistencias);
        void insertarProducto(Producto* nuevoProducto);
        void modificarProducto(int unaId, string unNombre, int cantExistencias);
        void eliminarProducto(int unaId);
        void guardarInformacionTiendaArchivoBinario(ostream* salida);
        void cargarInformacionTiendaArchivoBinario(istream* entrada);
        void cargarProductoDesdeArchivoBinario(istream* entrada, int posicion);
        char* obtenerNombre();
        char* obtenerDireccionInternet();
        char* obtenerDireccionFisica();
        char* obtenerTelefono();
        string toString();

    };

    
}

#endif