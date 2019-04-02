CPPFLAGS= -c -g -Iinc -Wall -pedantic

__start__: prog
	./prog

prog: obj/main.o 
	g++ -Wall -pedantic -o prog obj/main.o 

obj/main.o: src/main.cpp inc/Tablica.hpp
	g++ ${CPPFLAGS} -o obj/main.o src/main.cpp 

clean:
	rm -f obj/*.o times.txt output_M.txt output_B.txt output_Q.txt prog input.txt
