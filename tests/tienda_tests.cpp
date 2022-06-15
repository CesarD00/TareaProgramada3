#include <gtest/gtest.h>
#include "../src/tienda.h"

#include "../src/producto.h"
#include<fstream>
#include<cstring>
#include<string>
#include<iostream>
#include<map>

using namespace AdministradorExistencias;
using namespace std;

namespace {
    TEST(Tienda_Tests, Insertar_Producto){

        /// AAA

        // Arange - se configura el escenario
        Tienda* tienda = new Tienda("Verduleria", "verduleria.com", "Cinco Esquinas, Tibás", "88888888");
        Producto* producto = new Producto(1, "Zanahoria", 1000);

        // Act - se ejecuta la operación
        tienda->insertarProducto(producto);

        map<int, Producto*> elProducto = tienda->obtenerProductos();

        Producto* esperada = elProducto.at(1);
        Producto* actual = producto;

        delete tienda;

        // Assert - se validan los resultados
        EXPECT_EQ(actual, esperada);

    }
    
    TEST(Tienda_Tests, Guardar_Informacion_Tienda_ArchivoBinario){

        /// AAA

        // Arange - se configura el escenario
        string nombreTienda = "Verduleria";
        string dInternet = "verduleria.com";
        string dFisica = "Cinco Esquinas, Tibas";
        string telefono = "88888888"; 

        int id1 = 1;
        string nombre1 = "Zanahoria";
        int existencias1 = 1000;
        int id2 = 2;
        string nombre2 = "Papa";
        int existencias2 = 750;

        Tienda* tienda = new Tienda(nombreTienda, dInternet, dFisica, telefono);
        Producto* producto1 = new Producto(id1, nombre1, existencias1);
        Producto* producto2 = new Producto(id2, nombre2, existencias2);

        tienda->insertarProducto(producto1);
        tienda->insertarProducto(producto2);

        ofstream archivoBinarioActual("informacionTienda.dat", ios::out|ios::binary);
        ofstream archivoBinarioEsperado("informacionTienda2.dat", ios::out|ios::binary);

        archivoBinarioEsperado.write(nombreTienda.c_str(), 15);
        archivoBinarioEsperado.write(dInternet.c_str(), 24);
        archivoBinarioEsperado.write(dFisica.c_str(), 24);
        archivoBinarioEsperado.write(telefono.c_str(), 8);
        archivoBinarioEsperado.write((char*)&id1, sizeof(int));
        archivoBinarioEsperado.write(nombre1.c_str(), 20);
        archivoBinarioEsperado.write((char*)&existencias1, sizeof(int));
        archivoBinarioEsperado.write((char*)&id2, sizeof(int));
        archivoBinarioEsperado.write(nombre2.c_str(), 20);
        archivoBinarioEsperado.write((char*)&existencias2, sizeof(int));

        // Act - se ejecuta la operación
        tienda->guardarInformacionTiendaArchivoBinario(&archivoBinarioActual);

        int resultadoActual = memcmp(&archivoBinarioActual, &archivoBinarioEsperado, sizeof(archivoBinarioActual));

        delete tienda;

        archivoBinarioActual.close();
        archivoBinarioEsperado.close();

        // Assert - se validan los resultados
        EXPECT_EQ(resultadoActual, 0);

    }

    
    TEST(Tienda_Tests, Cargar_Informacion_Tienda_ArchivoBinario){

        /// AAA

        // Arange - se configura el escenario
        string nombreTienda = "Verduleria";
        string dInternet = "verduleria.com";
        string dFisica = "Cinco Esquinas, Tibas";
        string telefono = "88888888"; 

        int id = 1;
        string nombre = "Zanahoria";
        int existencias = 1500;

        ofstream archivoBinario("informacion.dat", ios::out|ios::binary);

        archivoBinario.write(nombreTienda.c_str(), 15);
        archivoBinario.write(dInternet.c_str(), 24);
        archivoBinario.write(dFisica.c_str(), 24);
        archivoBinario.write(telefono.c_str(), 9);
        archivoBinario.write((char*)&id, sizeof(int));
        archivoBinario.write(nombre.c_str(), 20);
        archivoBinario.write((char*)&existencias, sizeof(int));

        archivoBinario.close();

        ifstream archivoBinarioLectura;

        archivoBinarioLectura.open("informacion.dat", ios::out|ios::binary);

        if(!archivoBinarioLectura.is_open()){
            cerr<<"Error";
        }

        Tienda* tienda = new Tienda();

        // Act - se ejecuta la operación

        tienda->cargarInformacionTiendaArchivoBinario(&archivoBinarioLectura);


        // Assert - se validan los resultados
        
        EXPECT_EQ(nombreTienda, string(tienda->obtenerNombre()));
        EXPECT_EQ(dInternet, string(tienda->obtenerDireccionInternet()));
        EXPECT_EQ(dFisica, string(tienda->obtenerDireccionFisica()));
        EXPECT_EQ(telefono, string(tienda->obtenerTelefono()));
        EXPECT_EQ(id, tienda->obtenerProductos().at(1)->obtenerId());
        EXPECT_EQ(nombre, string(tienda->obtenerProductos().at(1)->obtenerNombre()));
        EXPECT_EQ(existencias, tienda->obtenerProductos().at(1)->obtenerNumExistencias());

        delete tienda;
    }

    /*
    TEST(Tienda_Tests, Consultar_Informacion_General){

        /// AAA

        // Arange - se configura el escenario
        Tienda* tienda = new Tienda("Verdulería", "verduleria.com", "San Pedro, 25m Este Fábrica factorio", "88888888");
        Producto* producto = new Producto(1, "Zanahoria", 1000);

        // Act - se ejecuta la operación
        tienda.añadirProducto(producto);

        // Assert - se validan los resultados
        

    }

    TEST(Tienda_Tests, Cargar_Productos_ArchivoBinario){

        /// AAA

        // Arange - se configura el escenario
        Tienda* tienda = new Tienda("Verdulería", "verduleria.com", "San Pedro, 25m Este Fábrica factorio", "88888888");
        Producto* producto = new Producto(1, "Zanahoria", 1000);

        // Act - se ejecuta la operación
        tienda.añadirProducto(producto);

        // Assert - se validan los resultados
        

    }

    TEST(Tienda_Tests, Modificar_Producto){

        /// AAA

        // Arange - se configura el escenario
        Tienda* tienda = new Tienda("Verdulería", "verduleria.com", "San Pedro, 25m Este Fábrica factorio", "88888888");
        Producto* producto = new Producto(1, "Zanahoria", 1000);

        // Act - se ejecuta la operación
        tienda.añadirProducto(producto);

        // Assert - se validan los resultados
        

    }

    TEST(Tienda_Tests, Eliminar_Producto){

        /// AAA

        // Arange - se configura el escenario
        Tienda* tienda = new Tienda("Verdulería", "verduleria.com", "San Pedro, 25m Este Fábrica factorio", "88888888");
        Producto* producto = new Producto(1, "Zanahoria", 1000);

        // Act - se ejecuta la operación
        tienda.añadirProducto(producto);

        // Assert - se validan los resultados
        

    }

    */

    
}