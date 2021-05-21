all:example
example:main.o vect.o
	g++ main.o vect.o -o example
main.o:main.C vect.h
	g++ -c main.C -o main.o
vect.o:vect.C vect.h
	g++ -c vect.C -o vect.o
clean:
	rm *~ *.o example
