all:example
example:main.o particle.o astrobody.o
	g++ main.o particle.o astrobody.o -o example
main.o:main.C particle.h astrobody.h
	g++ -c main.C -o main.o
particle.o:particle.C particle.h
	g++ -c particle.C -o particle.o
astrobody.o:astrobody.C particle.h astrobody.h
	g++ -c astrobody.C -o astrobody.o
clean:
	rm *.o *~ example
