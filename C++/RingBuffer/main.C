#include<iostream>
#include<cstdlib>
#include<string>
#include"buff.h"

using namespace std;

int main(){
	cout << "START TESTING RING BUFFER CLASS - int" << endl << endl;
	
	//init, capacity & size
	int cap = 4;
	buffer<int> sensonic(cap);
	cout << "Initialized ring buffer with capacity = " << cap << endl;
	cout << "Testing Capacity: returning buffer capacity = " << sensonic.Capacity() << endl;
	cout << "Testing Size: returning buffer current size = " << sensonic.Size() << endl << endl;
	
	//get - empty buffer
	cout << "Testing Get with empty buffer: (NULL value is assigned)"  << endl;
	int val = sensonic.Get();
	cout << "Printing returned value from Get() = " << val << endl << endl;

	//put & print. fill buffer
	cout << "Testing Put: adding element in crescent order " << endl;
	cout << "Print(bool var) was designed to see buffer status.  " << endl;
	cout << "If var is set to true it also print the eta of each element" << endl;
	sensonic.Put(1);
	sensonic.Print(false);
	cout << "Returning buffer current size: " << sensonic.Size() << endl;
	sensonic.Put(2);
	sensonic.Print(false);
	cout << "Returning buffer current size: " << sensonic.Size() << endl;
	sensonic.Put(3);
	sensonic.Print(false);
	cout << "Returning buffer current size: " << sensonic.Size() << endl;
	sensonic.Put(4);
	sensonic.Print(false);
	cout << "Returning buffer current size: " << sensonic.Size() << endl << endl;

	//put with full buffer
	cout << "Buffer is now full. Let's see eta and further test Put" << endl;
	sensonic.Print(true);
	cout << "Add new element with Put: replace oldest member (highest eta)" << endl;
	sensonic.Put(5);
	sensonic.Print(true);
	cout << "Testing Size: Printing buffer current size: " << sensonic.Size() << endl;
	cout << "Add new element with Put: replace oldest member (highest eta)" << endl;
	sensonic.Put(6);
	sensonic.Print(true);
	cout << endl;
	
	//get with non-empty buffer
	cout << "Testing Get with non-empty buffer" << endl;
	cout << "Buffer initial status: ";
	sensonic.Print(false);
	val = sensonic.Get();
	cout << "Printing returned value from Get() = " << val << endl;
	sensonic.Print(false);
	val = sensonic.Get();
	cout << "Printing returned value from Get() = " << val << endl;
	sensonic.Print(false);
	val = sensonic.Get();
	cout << "Printing returned value from Get() = " << val << endl;
	sensonic.Print(false);
	val = sensonic.Get();
	cout << "Printing returned value from Get() = " << val << endl;
	sensonic.Print(false); 
	cout << endl;

	cout << "TEST IS OVER!" << endl;
	
	return 0;
}
