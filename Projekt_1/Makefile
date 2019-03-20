CPPFLAGS= -c -g -Iinc -Wall -pedantic

__start__: prog
	./prog

prog: obj/main.o 
	g++ -Wall -pedantic -o prog obj/main.o 

obj/main.o: src/main.cpp inc/Stos.hpp inc/Lista.hpp inc/Kolejka.hpp inc/Kolejka_prio.hpp inc/Hasz_mapa.hpp
	g++ ${CPPFLAGS} -o obj/main.o src/main.cpp

clean:
	rm -f obj/*.o kod
