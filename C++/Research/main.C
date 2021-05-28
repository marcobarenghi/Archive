#include <iostream>
#include "vect.h"
#include "functions.h"
#include <chrono>
#include <cstring>
#include <fstream> 
using namespace std;
using namespace std::chrono;

int main(){
	cout << endl;
	cout << "  Standard Sorting vs Merge Sorting" << endl << endl;;
	int Ntests = 50; 
	int N = 9;
	int n[N] = {10000,20000, 40000, 60000, 80000 ,100000, 200000, 400000, 1000000};
	int seed = 7895;
	for (int i = 0; i < N; i++)
	{
		double *linResearchTime = new double[Ntests];
		double *binResearchTime = new double[Ntests];
		
		for (int j = 0; j < Ntests; j++)
		{			
			vect a = vect(n[i], seed);
			seed++;
			a.mergeSorting();
			int randPos = int(rand() % n[i]);
			
			int x,y = 0;	
			auto start = high_resolution_clock::now();
			x = a.linearSearch(randPos);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<nanoseconds>(stop - start);  
			linResearchTime[j] = duration.count();
			
			auto start2 = high_resolution_clock::now();
			y = a.binarySearch(randPos);
			auto stop2 = high_resolution_clock::now();
			auto duration2 = duration_cast<nanoseconds>(stop2 - start2);   
			binResearchTime[j] = duration2.count();  
			

		}		
		cout << "  Duration (ns) of lin research vs bin research - " << n[i] << " elements " << endl;
	    cout << "  " << mean(linResearchTime,Ntests) << " (+/-" << rms(linResearchTime,Ntests) << ") | " 
	         << mean(binResearchTime,Ntests) << " (+/-" << rms(binResearchTime,Ntests) << ")" << endl;
		
		delete [] linResearchTime;
		delete [] binResearchTime;
	}
	cout << endl;
	return 0;
}
