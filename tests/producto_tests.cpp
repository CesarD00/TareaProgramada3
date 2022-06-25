#include <gtest/gtest.h>
#include "../src/tienda.h"

#include "../src/producto.h"
#include "../src/excepcionStringTamanoExcedido.h"
#include "../src/excepcionNumeroNegativo.h"

namespace {
    TEST(Producto_Tests, Asignacion_Y_Obtencion_Datos){

        /// AAA

        // Arange - se configura el escenario
        int id = 1;
        string nombre = "Zanahoria";
        int existencias = 1000;

        Producto* producto = new Producto();

        // Act - se ejecuta la operación
        
        producto->asignarId(id);
        producto->asignarNombre(nombre);
        producto->asignarExistencias(existencias);

        // Assert - se validan los resultados
        EXPECT_EQ(producto->obtenerId(), id);
        EXPECT_EQ(producto->obtenerNombre(), nombre);
        EXPECT_EQ(producto->obtenerNumExistencias(), existencias);

        delete producto;

    }

    TEST(Producto_Tests, Asignacion_Nombre_Con_Tamano_Excedido){

        /// AAA

        // Arange - se configura el escenario
        string nombre = "000000000000000000000000000000000";

        Producto* producto = new Producto();

        // Act - se ejecuta la operación
        
        // Assert - se validan los resultados

        EXPECT_THROW({
            producto->asignarNombre(nombre);
        }, ExcepcionStringTamanoExcedido);

        delete producto;

    }

    TEST(Producto_Tests, Asignacion_Id_Y_Existencias_Negativas){

        /// AAA

        // Arange - se configura el escenario
        int id = -21;
        int existencias = -520;
        Producto* producto = new Producto();

        // Act - se ejecuta la operación
        
        // Assert - se validan los resultados

        EXPECT_THROW({
            producto->asignarId(id);
        }, ExcepcionNumeroNegativo);

        EXPECT_THROW({
            producto->asignarExistencias(existencias);
        }, ExcepcionNumeroNegativo);

        delete producto;

    }

    TEST(Producto_Tests, Constructor_Nombre_Con_Tamano_Excedido){

        /// AAA

        // Arange - se configura el escenario

        // Act - se ejecuta la operación
        
        // Assert - se validan los resultados

        EXPECT_THROW({
            Producto* producto = new Producto(1, "000000000000000000000000000000000", 1000);
            delete producto;
        }, ExcepcionStringTamanoExcedido);

    }

    

    
}