Testing with a vector-like class two research techniques.
In order to do so, the arrays must be already sorted -> mergeSorting method is called for this purpose.
After that, each time, for each array size, we pick a random value at a random position of the vect object and search for it with both methods.

The linear research scans from the beginning of the array each element, until the one we are looking for is found.
The computational time goes as O(N).

The Binary research starts in the middle. If the value we are looking for is larger than v[middle], we scan the rightmost part, otherwise we scan the leftmost one. The process is repeated until the value if found.
The computational time goes as O(log(N)).

In main.C this property is tested by measuring the time required for both operations in NANOSECONDS.
