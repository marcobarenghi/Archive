#include <iostream>
#include <cstdlib>
#include <string>
#include "buff.h"

using namespace std;

int main(){
	cout << endl << "  START TESTING RING BUFFER CLASS - int" << endl << endl;
	
	//init, capacity & size
	int cap = 4;
	buffer<int> myTest(cap);
	cout << "  Initialized ring buffer with capacity = " << cap << endl;
	cout << "  Testing Capacity method: returning buffer capacity = " << myTest.Capacity() << endl;
	cout << "  Testing Size method: returning buffer current size = " << myTest.Size() << endl << endl;
	
	//get - empty buffer
	cout << "  Testing Get method (empty buffer): (NULL value is assigned)"  << endl;
	int val = myTest.Get();
	cout << "  Printing returned value from Get() = " << val << endl << endl;

	//put & print. fill buffer
	cout << "  Testing Put method " << endl;
	myTest.Put(1);
	myTest.Print();
	myTest.Put(2);
	myTest.Print();
	myTest.Put(3);
	myTest.Print();
	cout << "  Returning buffer current size: " << myTest.Size() << endl;
	
	
	cout << "\n  Testing Get method" << endl;
	val = myTest.Get();
	cout << "  Printing returned value from Get() = " << val << endl;
	myTest.Print();
	val = myTest.Get();
	cout << "  Printing returned value from Get() = " << val << endl;
	myTest.Print();
	val = myTest.Get();
	cout << "  Printing returned value from Get() = " << val << endl;
	cout << endl;
	
	cout << "  Filling buffer again" << endl;
	myTest.Put(1);
	myTest.Put(2);
	myTest.Put(3);
	myTest.Put(4);
	myTest.Print();
	cout << "  Returning buffer current size: " << myTest.Size() << endl << endl;

	//put with full buffer
	cout << "  Buffer is now full" << endl;
	cout << "  Testing Put method (full buffer)" << endl;
	cout << "  Oldest element is replaced each time" << endl;
	myTest.Put(5);
	myTest.Print();
	myTest.Put(6);
	myTest.Print();
	myTest.Put(7);
	myTest.Print();
	myTest.Put(8);
	myTest.Print();
	myTest.Put(9);
	myTest.Print();
	myTest.Put(10);
	myTest.Print();
	cout << endl;
	
	//get with non-empty buffer
	cout << "  Testing Get method (full buffer)" << endl;
	val = myTest.Get();
	cout << "  Printing returned value from Get() = " << val << endl;
	myTest.Print();
	val = myTest.Get();
	cout << "  Printing returned value from Get() = " << val << endl;
	myTest.Print();
	val = myTest.Get();
	cout << "  Printing returned value from Get() = " << val << endl;
	myTest.Print();
	val = myTest.Get();
	cout << "  Printing returned value from Get() = " << val << endl << endl;
	myTest.Print(); 
	cout << endl;

	cout << "  TEST IS OVER!" << endl << endl;
	
	return 0;
}
