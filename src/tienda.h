#ifndef TIENDA_H
#define TIENDA_H

#include<string>

using namespace std;

namespace AdministradorExistencias {

    class Tienda {
        char nombre[15];
        char direccionInternet[24];
        char direccionFisica[24];
        char telefono[8];

        public:
        Tienda(char unNombre, char unaDireccionI, char unaDireccionF, char unTelefono);

    };
}

#endif