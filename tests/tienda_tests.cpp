#include <gtest/gtest.h>
#include "../src/tienda.h"
#include "../src/producto.h"

#include "../src/excepcionStringTamanoExcedido.h"
#include "../src/excepcionNumeroNegativo.h"
#include "../src/excepcionPosicionNoExistente.h"
#include "../src/excepcionIdNoEncontrada.h"

#include<fstream>
#include<cstring>
#include<string>
#include<iostream>
#include<map>

using namespace AdministradorExistencias;
using namespace std;

namespace {
    TEST(Tienda_Tests, Obtencion_Datos){

        /// AAA

        // Arange - se configura el escenario

        string nombreTienda = "Verduleria";
        string dInternet = "verduleria.com";
        string dFisica = "Cinco Esquinas, Tibas";
        string telefono = "88888888"; 

        Tienda* tienda = new Tienda(nombreTienda, dInternet, dFisica, telefono);

        // Act - se ejecuta la operación

        // Assert - se validan los resultados

        EXPECT_EQ(tienda->obtenerNombre(), nombreTienda);
        EXPECT_EQ(tienda->obtenerDireccionInternet(), dInternet);
        EXPECT_EQ(tienda->obtenerDireccionFisica(), dFisica);
        EXPECT_EQ(tienda->obtenerTelefono(), telefono);
           
    }

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

    TEST(Tienda_Tests, Modificar_Producto){
        /// AAA

        // Arange - se configura el escenario
        string nuevoNombre = "Zanahoria";
        int nuevaExistencia = 5000; 

        Tienda* tienda = new Tienda("Verduleria", "verduleria.com", "Cinco Esquinas, Tibás", "88888888");
        Producto* producto = new Producto(1, "sanaoria", 1000);

        tienda->insertarProducto(producto);

        // Act - se ejecuta la operación

        tienda->modificarProducto(1, nuevoNombre, nuevaExistencia);

        // Assert - se validan los resultados

        EXPECT_EQ(nuevoNombre, tienda->obtenerProductos().at(1)->obtenerNombre());          
        EXPECT_EQ(nuevaExistencia, tienda->obtenerProductos().at(1)->obtenerNumExistencias());          

        delete tienda;
    }
    
     TEST(Tienda_Tests, Eliminar_Producto){
        /// AAA

        // Arange - se configura el escenario

        Tienda* tienda = new Tienda("Verduleria", "verduleria.com", "Cinco Esquinas, Tibás", "88888888");
        Producto* producto = new Producto(1, "Zanahoria", 1000);

        tienda->insertarProducto(producto);

        // Act - se ejecuta la operación

        tienda->eliminarProducto(1);

        // Assert - se validan los resultados

        EXPECT_THROW({
            Producto* producto = tienda->obtenerProductos().at(1);
        }, out_of_range);

        delete tienda;
    }

    TEST(Tienda_Tests, Consultar_Productos){

        /// AAA

        // Arange - se configura el escenario
        Tienda* tienda = new Tienda("Verdulería", "verduleria.com", "San Pedro", "88888888");
        Producto* producto = new Producto(1, "Zanahoria", 1000);
        Producto* producto2 = new Producto(4, "Manzana", 7000);
        Producto* producto3 = new Producto(7, "Papa", 4000);

        tienda->insertarProducto(producto);
        tienda->insertarProducto(producto2);
        tienda->insertarProducto(producto3);

        // Act - se ejecuta la operación

        string productos = tienda->consultarProductos();
        string listaEsperada = string("Producto 1\nId: 1\nNombre: Zanahoria\nCantidad de existencias: 1000\n") +
            string("Producto 2\nId: 4\nNombre: Manzana\nCantidad de existencias: 7000\n") +
            string("Producto 3\nId: 7\nNombre: Papa\nCantidad de existencias: 4000\n");
        
        delete tienda;

        // Assert - se validan los resultados
        
        EXPECT_EQ(productos, listaEsperada);

    }

    

    TEST(Tienda_Tests, Informacion_Completa_Tienda_ToString){

        /// AAA

        // Arange - se configura el escenario
        Tienda* tienda = new Tienda("Verdulería", "verduleria.com", "San Pedro", "88888888");
        Producto* producto = new Producto(1, "Zanahoria", 1000);
        Producto* producto2 = new Producto(4, "Manzana", 7000);
        Producto* producto3 = new Producto(7, "Papa", 4000);

        tienda->insertarProducto(producto);
        tienda->insertarProducto(producto2);
        tienda->insertarProducto(producto3);

        // Act - se ejecuta la operación

        string informacion = tienda->toString();
        string informacionEsperada = string("Datos de la tienda\nNombre: Verdulería\nDirección de Internet: verduleria.com\nDirección física: San Pedro\nNúmero de teléfono: 88888888\n\n") + 
            string("Productos\nProducto 1\nId: 1\nNombre: Zanahoria\nCantidad de existencias: 1000\n") +
            string("Producto 2\nId: 4\nNombre: Manzana\nCantidad de existencias: 7000\n") +
            string("Producto 3\nId: 7\nNombre: Papa\nCantidad de existencias: 4000\n");
        
        delete tienda;

        // Assert - se validan los resultados
        
        EXPECT_EQ(informacion, informacionEsperada);

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
        archivoBinario.write(telefono.c_str(), 8);
        archivoBinario.write((char*)&id, sizeof(int));
        archivoBinario.write(nombre.c_str(), 20);
        archivoBinario.write((char*)&existencias, sizeof(int));

        archivoBinario.close();

        ifstream archivoBinarioLectura;

        archivoBinarioLectura.open("informacion.dat", ios::in|ios::binary);

        if(!archivoBinarioLectura.is_open()){
            cerr<<"Error. No se pudo abrir el archivo para leer los datos.";
            FAIL();
        }

        Tienda* tienda = new Tienda();

        // Act - se ejecuta la operación

        tienda->cargarInformacionTiendaArchivoBinario(&archivoBinarioLectura);

        archivoBinarioLectura.close();

        int a = remove("informacion.dat");


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
    
    TEST(Tienda_Tests, Guardar_Informacion_Tienda_ArchivoBinario_InsercionProductos){

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

        ofstream archivoBinarioSalida;

        archivoBinarioSalida.open("archivo_test.dat", ios::out|ios::binary);

        if(!archivoBinarioSalida.is_open()){
            cerr<<"Error. No se pudo abrir el archivo para escribir los datos.";
            FAIL();
        }

        // Act - se ejecuta la operación
        tienda->guardarInformacionTiendaArchivoBinario(&archivoBinarioSalida);

        archivoBinarioSalida.close();

        ifstream archivoBinarioEntrada;

        archivoBinarioEntrada.open("archivo_test.dat", ios::in|ios::binary);

        if(!archivoBinarioEntrada.is_open()){
            cerr<<"Error. No se pudo abrir el archivo para leer los datos";
            FAIL();
        }

        Tienda* tiendaActual = new Tienda();

        tiendaActual->cargarInformacionTiendaArchivoBinario(&archivoBinarioEntrada);

        archivoBinarioEntrada.close();

        int a = remove("archivo_test.dat");

        string esperado = tienda->toString();
        string actual = tiendaActual->toString();

        delete tienda;
        delete tiendaActual;

        // Assert - se validan los resultados
        EXPECT_EQ(esperado, actual);

    }

    TEST(Tienda_Tests, Guardar_Informacion_Tienda_ArchivoBinario_ModificacionProductos){

        /// AAA

        // Arange - se configura el escenario
        string nombreTienda = "Verduleriaaaaa";
        string dInternet = "verduleria.com";
        string dFisica = "Cinco Esquinas, Tibas";
        string telefono = "88888888"; 

        int id1 = 1;
        string nombre1 = "Zanahoria";
        int existencias1 = 1000;
    
        Tienda* tienda = new Tienda(nombreTienda, dInternet, dFisica, telefono);

        ofstream archivoBinarioSalida;

        archivoBinarioSalida.open("informacionTienda.dat", ios::out|ios::binary);

        if(!archivoBinarioSalida.is_open()){
            cerr<<"Error. No se pudo abrir el archivo para escribir los datos";
            FAIL();
        }

        archivoBinarioSalida.write(nombreTienda.c_str(), 15);
        archivoBinarioSalida.write(dInternet.c_str(), 24);
        archivoBinarioSalida.write(dFisica.c_str(), 24);
        archivoBinarioSalida.write(telefono.c_str(), 8);
        archivoBinarioSalida.write((char*)&id1, sizeof(int));
        archivoBinarioSalida.write(nombre1.c_str(), 20);
        archivoBinarioSalida.write((char*)&existencias1, sizeof(int));

        archivoBinarioSalida.close();

        ifstream archivoBinarioEntrada;

        archivoBinarioEntrada.open("informacionTienda.dat", ios::in|ios::binary);

        if(!archivoBinarioEntrada.is_open()){
            cerr<<"Error. No se puedo abrir el archivo para leer los datos.";
            FAIL();
        }

        tienda->cargarInformacionTiendaArchivoBinario(&archivoBinarioEntrada);
        Tienda* tienda2 = new Tienda();

        // Act - se ejecuta la operación

        tienda->modificarProducto(1, "Manzana", 2500);

        archivoBinarioSalida.open("informacionTienda.dat", ios::out|ios::binary);

        if(!archivoBinarioSalida.is_open()){
            cerr<<"Error. No se pudo abrir el archivo para escribir los datos.";
            FAIL();
        }

        tienda->guardarInformacionTiendaArchivoBinario(&archivoBinarioSalida);

        archivoBinarioSalida.close();

        tienda2->cargarInformacionTiendaArchivoBinario(&archivoBinarioEntrada);

        archivoBinarioEntrada.close();

        int a = remove("informacionTienda.dat");

        // Assert - se validan los resultados
        EXPECT_EQ(tienda->toString(), tienda2->toString());

        delete tienda2;
        delete tienda;

    }

    TEST(Tienda_Tests, Guardar_Informacion_Tienda_ArchivoBinario_EliminacionProductos){

        /// AAA

        // Arange - se configura el escenario
        string nombreTienda = "Verduleria";
        string dInternet = "verduleria.com";
        string dFisica = "Cinco Esquinas, Tibas";
        string unTelefono = "8888888"; 

        int id1 = 1;
        string nombre1 = "Zanahoria";
        int existencias1 = 1000;
    
        Tienda* tienda = new Tienda(nombreTienda, dInternet, dFisica, unTelefono);

        ofstream archivoBinarioSalida;

        archivoBinarioSalida.open("informacionTienda.dat", ios::out|ios::binary);

        if(!archivoBinarioSalida.is_open()){
            cerr<<"Error. No se pudo abrir el archivo para escribir los datos.";
            FAIL();
        }

        archivoBinarioSalida.write(nombreTienda.c_str(), 15);
        archivoBinarioSalida.write(dInternet.c_str(), 24);
        archivoBinarioSalida.write(dFisica.c_str(), 24);
        archivoBinarioSalida.write(unTelefono.c_str(), 8);
        archivoBinarioSalida.write((char*)&id1, sizeof(int));
        archivoBinarioSalida.write(nombre1.c_str(), 20);
        archivoBinarioSalida.write((char*)&existencias1, sizeof(int));

        archivoBinarioSalida.close();

        ifstream archivoBinarioEntrada;

        archivoBinarioEntrada.open("informacionTienda.dat", ios::in|ios::binary);

        if(!archivoBinarioEntrada.is_open()){
            cerr<<"Error. No se pudo abrir el archivo para leer los datos.";
            FAIL();
        }

        tienda->cargarInformacionTiendaArchivoBinario(&archivoBinarioEntrada);
        Tienda* tienda2 = new Tienda();

        // Act - se ejecuta la operación

        tienda->eliminarProducto(1);

        archivoBinarioSalida.open("informacionTienda.dat", ios::out|ios::binary);

        if(!archivoBinarioSalida.is_open()){
            cerr<<"Error. No se pudo abrir el archivo para escribir los datos.";
            FAIL();
        }

        tienda->guardarInformacionTiendaArchivoBinario(&archivoBinarioSalida);

        archivoBinarioSalida.close();

        tienda2->cargarInformacionTiendaArchivoBinario(&archivoBinarioEntrada);

        archivoBinarioEntrada.close();

        int a = remove("informacionTienda.dat");

        //cout<<tienda->toString()<<endl;
        //cout<<tienda2->toString()<<endl;

        // Assert - se validan los resultados
        EXPECT_EQ(tienda->toString(), tienda2->toString());

        delete tienda2;
        delete tienda;

    }

    TEST(Tienda_Tests, CargarUnProducto_Desde_Archivo_Binario){

        /// AAA

        // Arange - se configura el escenario
        string nombreTienda = "Verduleria";
        string dInternet = "verduleria.com";
        string dFisica = "Cinco Esquinas, Tibas";
        string telefono = "88888888"; 

        int id1 = 001;
        string nombre1 = "Zanahoria";
        int existencias1 = 1000;
        int id2 = 002;
        string nombre2 = "Papa";
        int existencias2 = 750;

        Tienda* tiendaAuxiliar = new Tienda(nombreTienda, dInternet, dFisica, telefono);
        Producto* producto1 = new Producto(id1, nombre1, existencias1);
        Producto* producto2 = new Producto(id2, nombre2, existencias2);

        tiendaAuxiliar->insertarProducto(producto1);
        tiendaAuxiliar->insertarProducto(producto2);

        ofstream archivoBinarioSalida;

        archivoBinarioSalida.open("informacionTienda.dat", ios::out|ios::binary);

        if(!archivoBinarioSalida.is_open()){
            cerr<<"Error. No se pudo abrir el archivo para escribir los datos.";
            FAIL();
        }

        tiendaAuxiliar->guardarInformacionTiendaArchivoBinario(&archivoBinarioSalida);

        archivoBinarioSalida.close();

        Tienda* tiendaACargarProducto = new Tienda("a", "a", "a", "a");

        ifstream archivoBinarioEntrada;

        archivoBinarioEntrada.open("informacionTienda.dat", ios::in|ios::binary);

        if(!archivoBinarioEntrada.is_open()){
            cerr<<"Error. no se pudo abrir el archivo para leer los datos.";
            FAIL();
        }

        // Act - se ejecuta la operación
        
        tiendaACargarProducto->cargarProductoDesdeArchivoBinario(&archivoBinarioEntrada, 1);

        archivoBinarioEntrada.close();

        int a = remove("informacionTienda.dat");

        // Assert - se validan los resultados
        EXPECT_EQ(tiendaACargarProducto->obtenerProductos().at(002)->obtenerNombre(), nombre2);
        EXPECT_EQ(tiendaACargarProducto->obtenerProductos().at(002)->obtenerNumExistencias(), existencias2);

        delete tiendaAuxiliar;
        delete tiendaACargarProducto;

    }

    TEST(Tienda_Tests, CargarProducto_Posicion_Inexistente_Desde_Archivo_Binario){

        /// AAA

        // Arange - se configura el escenario
        string nombreTienda = "Verduleria";
        string dInternet = "verduleria.com";
        string dFisica = "Cinco Esquinas, Tibas";
        string telefono = "88888888"; 

        int id1 = 001;
        string nombre1 = "Zanahoria";
        int existencias1 = 1000;
        int id2 = 002;
        string nombre2 = "Papa";
        int existencias2 = 750;

        Tienda* tiendaAuxiliar = new Tienda(nombreTienda, dInternet, dFisica, telefono);
        Producto* producto1 = new Producto(id1, nombre1, existencias1);
        Producto* producto2 = new Producto(id2, nombre2, existencias2);

        tiendaAuxiliar->insertarProducto(producto1);
        tiendaAuxiliar->insertarProducto(producto2);

        ofstream archivoBinarioSalida;

        archivoBinarioSalida.open("informacionTienda.dat", ios::out|ios::binary);

        if(!archivoBinarioSalida.is_open()){
            cerr<<"Error. No se pudo abrir el archivo para escribir los datos.";
            FAIL();
        }

        tiendaAuxiliar->guardarInformacionTiendaArchivoBinario(&archivoBinarioSalida);

        archivoBinarioSalida.close();

        Tienda* tiendaACargarProducto = new Tienda("a", "a", "a", "a");

        ifstream archivoBinarioEntrada;

        archivoBinarioEntrada.open("informacionTienda.dat", ios::in|ios::binary);

        if(!archivoBinarioEntrada.is_open()){
            cerr<<"Error. No se pudo abrir el archivo para leer los datos.";
            FAIL();
        }

        // Act - se ejecuta la operación

        // Assert - se validan los resultados
        EXPECT_THROW({
            tiendaACargarProducto->cargarProductoDesdeArchivoBinario(&archivoBinarioEntrada, 2);

        }, ExcepcionPosicionNoExistente);

        archivoBinarioEntrada.close();

        delete tiendaAuxiliar;
        delete tiendaACargarProducto;

        int a = remove("informacionTienda.dat");

    }

    TEST(Tienda_Tests, CargarProducto_Posicion_Negativa_Desde_Archivo_Binario){

        /// AAA

        // Arange - se configura el escenario
        string nombreTienda = "Verduleria";
        string dInternet = "verduleria.com";
        string dFisica = "Cinco Esquinas, Tibas";
        string telefono = "88888888"; 

        int id1 = 001;
        string nombre1 = "Zanahoria";
        int existencias1 = 1000;

        Tienda* tiendaAuxiliar = new Tienda(nombreTienda, dInternet, dFisica, telefono);
        Producto* producto1 = new Producto(id1, nombre1, existencias1);

        tiendaAuxiliar->insertarProducto(producto1);

        ofstream archivoBinarioSalida;

        archivoBinarioSalida.open("informacionTienda.dat", ios::out|ios::binary);

        if(!archivoBinarioSalida.is_open()){
            cerr<<"Error. No se pudo abrir el archivo para escribir los datos.";
            FAIL();
        }

        tiendaAuxiliar->guardarInformacionTiendaArchivoBinario(&archivoBinarioSalida);

        archivoBinarioSalida.close();

        Tienda* tiendaACargarProducto = new Tienda("a", "a", "a", "a");

        ifstream archivoBinarioEntrada;

        archivoBinarioEntrada.open("informacionTienda.dat", ios::in|ios::binary);

        if(!archivoBinarioEntrada.is_open()){
            cerr<<"Error. No se pudo abrir el archivo para leer los datos.";
            FAIL();
        }

        // Act - se ejecuta la operación

        // Assert - se validan los resultados
        EXPECT_THROW({
            tiendaACargarProducto->cargarProductoDesdeArchivoBinario(&archivoBinarioEntrada, -2);

        }, ExcepcionNumeroNegativo);

        archivoBinarioEntrada.close();

        delete tiendaAuxiliar;
        delete tiendaACargarProducto;

        int a = remove("informacionTienda.dat");

    }

    TEST(Tienda_Tests, Datos_Tienda_Tamano_Excedido){

        /// AAA

        // Arange - se configura el escenario

        string nombreTienda = "000000000000000000000000000000000000000000000";
        string dInternet = "000000000000000000000000000000000000000000000";
        string dFisica = "000000000000000000000000000000000000000000000";
        string telefono = "000000000000000000000000000000000000000000000"; 

        Tienda* tienda;


        // Act - se ejecuta la operación

        // Assert - se validan los resultados

        EXPECT_THROW({
            tienda = new Tienda(nombreTienda, dInternet, dFisica, telefono);
        }, ExcepcionStringTamanoExcedido);
   
    }

    TEST(Tienda_Tests, Eliminacion_Producto_IdNegativa_Y_IdNoEncontrada){

        /// AAA

        // Arange - se configura el escenario

        Tienda* tienda = new Tienda("a", "a", "a", "a");
        tienda->insertarProducto(1, "a", 1000);
        tienda->insertarProducto(3, "a", 2000);
        tienda->insertarProducto(4, "a", 3000);

        // Act - se ejecuta la operación


        // Assert - se validan los resultados

        EXPECT_THROW({
            tienda->eliminarProducto(-4);
        }, ExcepcionNumeroNegativo);

        EXPECT_THROW({
            tienda->eliminarProducto(2);
        }, ExcepcionIdNoEncontrada);

    }

    



    
}