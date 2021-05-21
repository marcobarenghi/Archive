#include <iostream>
#include "vect.h"
#include <chrono>
#include <cstring>
using namespace std;
using namespace std::chrono;

int main(){
		
	int N = 10;
	int n[N] = {100, 200, 500, 700, 1000, 2000, 5000, 7000, 10000, 20000};
	
	for (int i = 0; i < N; i++)
	{
		vect a = vect(n[i]);
		vect b = vect(n[i]);
			
		auto start = high_resolution_clock::now();
		a.stdSorting();
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);   
		       
		auto start2 = high_resolution_clock::now();
		b.mergeSorting();
		auto stop2 = high_resolution_clock::now();
		auto duration2 = duration_cast<microseconds>(stop2 - start2);
		cout << "Duration (us) of std sorting vs merge sorting of " << n[i] << " elements " << endl;
		cout << duration.count() << " | " <<  duration2.count() << endl;
	}

	return 0;
}
