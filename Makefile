monedas: monedas.cpp
	g++ monedas.cpp -o monedas.o

testCambio: monedas
	./monedas.o

clean:
	rm *.o
