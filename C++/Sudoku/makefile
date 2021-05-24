all:example
example:main.o sudoku.o
	g++ main.o sudoku.o -o example
main.o:main.C sudoku.h
	g++ -c main.C -o main.o
vect.o:sudoku.C sudoku.h
	g++ -c sudoku.C -o sudoku.o
clean:
	rm *~ *.o example
