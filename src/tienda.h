#ifndef TIENDA_H
#define TIENDA_H

#include<string>
#include<vector>
#include<iostream>

#include "producto.h"

using namespace std;

namespace AdministradorExistencias {

    class Tienda {
        char nombre[15];
        char direccionInternet[24];
        char direccionFisica[24];
        char telefono[8];
        vector<Producto *> productos;

        public:
        Tienda(string unNombre, string unaDireccionI, string unaDireccionF, string unTelefono);
        Tienda();
        ~Tienda();
        vector<Producto*> obtenerProductos();
        void insertarProducto(int unaId, string unNombre, int cantExistencias);
        void insertarProducto(Producto* nuevoProducto);
        void guardarInformacionTiendaArchivoBinario(ostream* salida);
        void cargarInformacionTiendaArchivoBinario(istream* entrada);
        char* obtenerNombre();
        char* obtenerDireccionInternet();
        char* obtenerDireccionFisica();
        char* obtenerTelefono();

    };
}

#endif