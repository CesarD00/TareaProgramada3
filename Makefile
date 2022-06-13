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
	g++ $(FLAGS) tests/tests_empleado_nomina.cpp -o bin/tests_empleado_nomina.o
	g++ $(FLAGS) src/empleadoNomina.cpp -o bin/empleadoNomina.o
	g++ $(FLAGS) tests/tests_profesional_horas.cpp -o bin/tests_profesional_horas.o
	g++ $(FLAGS) src/profesionalPorHoras.cpp -o bin/profesionalPorHoras.o
	g++ $(FLAGS) tests/tests_planilla.cpp -o bin/tests_planilla.o
	g++ $(FLAGS) src/planilla.cpp -o bin/planilla.o
	g++ $(FLAGS) tests/tests_empleado.cpp -o bin/tests_empleado.o
	g++ $(FLAGS) src/empleado.cpp -o bin/empleado.o
	g++ $(FLAGS) tests/tests_reporte.cpp -o bin/tests_reporte.o
	g++ $(FLAGS) src/reporte.cpp -o bin/reporte.o
	g++ -g -o bin/tests bin/tests_empleado_nomina.o bin/empleadoNomina.o bin/tests_profesional_horas.o bin/profesionalPorHoras.o bin/tests_planilla.o bin/planilla.o bin/tests_empleado.o bin/empleado.o bin/tests_reporte.o bin/reporte.o -lgtest -lgtest_main -lpthread		

clean:
	rm -Rf bin	