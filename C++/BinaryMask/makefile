all:example
example:main.o binarymask.o
	g++ main.o binarymask.o -o example
main.o:main.C binarymask.h
	g++ -c main.C -o main.o
vect.o:vect.C binarymask.h
	g++ -c binarymask.C -o binarymask.o
clean:
	rm *~ *.o example
