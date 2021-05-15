EXERCISE: have a ring-like buffer. If buffer is full and an additional element is loaded, the oldest is overwritten.
	Buffer must be able to deal with several data types: int, float, double, string
	
The ring-buffer class is able deal with several data types via the use of template <typename T>.
It has the 4 main functionalities: Size, Capacity, Get, Put. The method print also allows to print the buffer and see the eta of the added elements.
The class is in "buff.h"; main.C is just a script where some tests were run. Makefile was used to deal with the header file and the .C script.
The test is perfomed for integers.

In your terminal digit:
make example
./example
