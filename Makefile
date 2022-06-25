FLAGS = -g -c --std=c++17

all:
	mkdir -p bin
	g++ $(FLAGS) src/tienda.cpp -o bin/tienda.o
	g++ $(FLAGS) src/producto.cpp -o bin/producto.o
	g++ -g -o bin/administrarExistencias bin/tienda.o bin/producto.o 
test:
	mkdir -p bin
	g++ $(FLAGS) tests/tienda_tests.cpp -o bin/tienda_tests.o
	g++ $(FLAGS) tests/producto_tests.cpp -o bin/producto_tests.o
	g++ $(FLAGS) src/tienda.cpp -o bin/tienda.o
	g++ $(FLAGS) src/producto.cpp -o bin/producto.o
	g++ -g -o bin/tests bin/tienda_tests.o bin/producto_tests.o bin/tienda.o bin/producto.o -lgtest -lgtest_main -lpthread		

clean:
	rm -Rf bin	