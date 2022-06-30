FLAGS = -g -c --std=c++17

all:
	mkdir -p obj
	mkdir -p bin
	g++ $(FLAGS) -fPIC src/producto.cpp -o obj/producto.o
	g++ $(FLAGS) -fPIC src/tienda.cpp -o obj/tienda.o
	g++ -shared  -o bin/libtienda.so obj/tienda.o obj/producto.o
	mkdir -p bin/include

	cp src/excepcionNumeroNegativo.h ./bin/include
	cp src/excepcionPosicionNoExistente.h ./bin/include
	cp src/excepcionStringTamanoExcedido.h ./bin/include
	cp src/excepcionIdNoEncontrada.h ./bin/include
	cp src/producto.h ./bin/include
	cp src/tienda.h ./bin/include

test:
	mkdir -p bin
	g++ $(FLAGS) tests/tienda_tests.cpp -o bin/tienda_tests.o
	g++ $(FLAGS) tests/producto_tests.cpp -o bin/producto_tests.o
	g++ $(FLAGS) src/tienda.cpp -o bin/tienda.o
	g++ $(FLAGS) src/producto.cpp -o bin/producto.o
	g++ -g -o bin/tests bin/tienda_tests.o bin/producto_tests.o bin/tienda.o bin/producto.o -lgtest -lgtest_main -lpthread		

clean:
	rm -Rf bin	