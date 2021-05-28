#include <iostream>
#include <cmath>

using namespace std;

int rms(double*, int);
int mean(double*, int);

int mean(double *array, int N){
	float mean = 0;
	for (int i = 0; i < N; i++)	
	{
		mean = mean + array[i];
	}
	mean = mean/N;	
	return int(mean);		
};

int rms(double *array2, int N){
	float mean = 0;
	float rms = 0;
	for (int i = 0; i < N; i++)	
	{
		mean = mean + array2[i];
	}
	mean = mean/N;
	
	for (int i = 0; i < N; i++)	
	{
		rms = rms + (mean - array2[i])*(mean - array2[i]);
	}
	rms = sqrt(rms/N);
	return int(rms);	
}; 
