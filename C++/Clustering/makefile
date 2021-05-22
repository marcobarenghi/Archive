all:example
example:main.o
	g++ main.o -o example
main.o:main.C functions.h
	g++ -c main.C -o main.o
clean:
	rm *.o example
