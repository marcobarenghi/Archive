#include <iostream>
#include "vect.h"
#include "functions.h"
#include <chrono>
#include <cstring>
using namespace std;
using namespace std::chrono;

int main(){
		
	int Ntests = 20;
	int N = 10;
	int n[N] = {100, 200, 500, 700, 1000, 2000, 5000, 7000, 10000, 20000};
	int seed = 4274;
	
	for (int i = 0; i < N; i++)
	{
		double *stdSortingTime = new double[Ntests];
		double *mergeSortingTime = new double[Ntests];
		
		for (int j = 0; j < Ntests; j++)
		{
			vect a = vect(n[i], seed);
			vect b = vect(n[i], seed);
			seed++;
			
			auto start = high_resolution_clock::now();
			a.stdSorting();
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);   
		       
			auto start2 = high_resolution_clock::now();
			b.mergeSorting();
			auto stop2 = high_resolution_clock::now();
			auto duration2 = duration_cast<microseconds>(stop2 - start2);
			
			stdSortingTime[j] = duration.count();
			mergeSortingTime[j] = duration2.count();
		 
		}
		cout << "Duration (us) of std sorting vs merge sorting of " << n[i] 
		<< " elements " << endl;
	    cout << mean(stdSortingTime,Ntests) << " (+/-" << int(rms(stdSortingTime,Ntests))
	    <<") | "  <<  mean(mergeSortingTime,Ntests) << " (+/-" << int(rms(mergeSortingTime,Ntests))
	    <<")" << endl;
		
		delete [] stdSortingTime;
		delete [] mergeSortingTime;
	}
	return 0;
}
