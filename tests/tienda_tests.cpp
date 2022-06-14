#include <gtest/gtest.h>
#include "../src/tienda.h"

#include "../src/producto.h"
#include<fstream>
#include<cstring>

using namespace AdministradorExistencias;
using namespace std;

namespace {
    TEST(Tienda_Tests, Insertar_Producto){

        /// AAA

        // Arange - se configura el escenario
        Tienda* tienda = new Tienda("Verdulería", "verduleria.com", "San Pedro, 25m Este Fábrica factorio", "88888888");
        Producto* producto = new Producto(1, "Zanahoria", 1000);

        // Act - se ejecuta la operación
        tienda->insertarProducto(producto);

        Producto* esperada = tienda->obtenerProductos()[0];
        Producto* actual = producto;

        delete producto;
        delete tienda;

        // Assert - se validan los resultados
        EXPECT_EQ(actual, esperada);

    }
    
    TEST(Tienda_Tests, Guardar_Informacion_Tienda_ArchivoBinario){

        /// AAA

        // Arange - se configura el escenario
        Tienda* tienda = new Tienda("Verdulería", "verduleria.com", "San Pedro, 25m Este Fábrica factorio", "88888888");
        Producto* producto1 = new Producto(1, "Zanahoria", 1000);
        Producto* producto2 = new Producto(2, "Papa", 750);
        Producto* producto3 = new Producto(3, "Cebolla", 250);

        tienda->insertarProducto(producto1);
        tienda->insertarProducto(producto2);
        tienda->insertarProducto(producto3);

        ofstream archivoBinarioActual("informacionTienda.dat", ios::out|ios::binary);
        ofstream archivoBinarioEsperado("informacionTienda2.dat", ios::out|ios::binary);

        archivoBinarioEsperado.write("Verdulería", 15);
        archivoBinarioEsperado.write("verduleria.com", 24);
        archivoBinarioEsperado.write("San Pedro, 25m Este Fábrica factorio", 24);
        archivoBinarioEsperado.write("88888888", 8);
        archivoBinarioEsperado.write((char *)1, sizeof(int));
        archivoBinarioEsperado.write("Zanahoria", 20);
        archivoBinarioEsperado.write((char *)1000, sizeof(int));
        archivoBinarioEsperado.write((char *)2, sizeof(int));
        archivoBinarioEsperado.write("Papa", 20);
        archivoBinarioEsperado.write((char *)750, sizeof(int));
        archivoBinarioEsperado.write((char *)3, sizeof(int));
        archivoBinarioEsperado.write("Cebolla", 20);
        archivoBinarioEsperado.write((char *)250, sizeof(int));
        

        // Act - se ejecuta la operación
        tienda->guardarInformacionTiendaArchivoBinario(&archivoBinarioActual);

        int resultadoActual = memcmp(archivoBinarioActual.c_str(), archivoBinarioEsperado.c_str(), sizeof(archivoBinarioActual));

        // Assert - se validan los resultados
        EXPECT_EQ(resultadoActual, 0);

    }

    TEST(Tienda_Tests, Consultar_Productos){

        /// AAA

        // Arange - se configura el escenario
        Tienda* tienda = new Tienda("Verdulería", "verduleria.com", "San Pedro, 25m Este Fábrica factorio", "88888888");
        Producto* producto = new Producto(1, "Zanahoria", 1000);

        // Act - se ejecuta la operación
        tienda.añadirProducto(producto);

        // Assert - se validan los resultados
        

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