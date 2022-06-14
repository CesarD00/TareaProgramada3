FLAGS = -g -c --std=c++17

all:
	mkdir -p bin
	g++ $(FLAGS) src/planilla.cpp -o bin/planilla.o
	g++ $(FLAGS) src/empleado.cpp -o bin/empleado.o
	g++ $(FLAGS) src/empleadoNomina.cpp -o bin/empleadoNomina.o
	g++ $(FLAGS) src/profesionalPorHoras.cpp -o bin/profesionalPorHoras.o
	g++ $(FLAGS) src/reporte.cpp -o bin/reporte.o
	g++ $(FLAGS) src/main.cpp -o bin/main.o
	g++ -g -o bin/generarReporte bin/main.o bin/planilla.o bin/empleado.o bin/empleadoNomina.o bin/profesionalPorHoras.o bin/reporte.o

test:
	mkdir -p bin
	g++ $(FLAGS) tests/tienda_tests.cpp -o bin/tienda_tests.o
	g++ $(FLAGS) src/tienda.cpp -o bin/tienda.o
	g++ $(FLAGS) src/producto.cpp -o bin/producto.o
	g++ -g -o bin/tests bin/tienda_tests.o bin/tienda.o bin/producto.o -lgtest -lgtest_main -lpthread		

clean:
	rm -Rf bin	