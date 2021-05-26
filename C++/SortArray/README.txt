Testing with a vector-like class two sorting techniques.

stdSorting sort an array in the "commom way" -> 2 for loops running through all elements.
For this the computational time grows as O(n^2).

mergeSorting uses a different approach: it splits the array into halves and keeps doing so until the array only has singular elements.
The elements are then sorted and swapped using the standard technique. In the end, the array is merged back together.
This approach is characterized by a computational time that goes as O(nlog(n)).

In main.C this property is tested by measuring the time required to sort arrays of different sizes.

##############
second commit:
The class vect was updated, the random seed is passed when an object is initialized.
In functions.h tthere are wo quick functions to calculate mean and standard deviation of an array.
The timing test is now repeated Ntests times for each given number of members of the array, in order to calculate mean and std.
Better statistics are displayed. 
