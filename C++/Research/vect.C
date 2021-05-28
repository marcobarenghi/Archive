#include"vect.h"
#include <stdio.h>      
#include <stdlib.h>    
#include <time.h> 
#include <iostream> 
using namespace std;

int binfunction(double* v, int low, int high, double x){
  
	// Repeat until the pointers low and high meet each other
  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (v[mid] == x)
      return mid;

    if (v[mid] < x)
      low = mid + 1;

    else
      high = mid - 1;
  }

  return -1;
}

void Merge(double *a, int low, int high, int mid)
{
	// We have low to mid and mid+1 to high already sorted.
	int i, j, k;
	double tmp[high-low+1];
	i = low;
	k = 0;
	j = mid + 1;
 
	// Merge the two parts into tmp[].
	while (i <= mid && j <= high)
	{
		if (a[i] < a[j])
		{
			tmp[k] = a[i];
			k++;
			i++;
		}
		else
		{
			tmp[k] = a[j];
			k++;
			j++;
		}
	}
 
	// Insert all the remaining values from i to mid into tmp[].
	while (i <= mid)
	{
		tmp[k] = a[i];
		k++;
		i++;
	}
 
	// Insert all the remaining values from j to high into tmp[].
	while (j <= high)
	{
		tmp[k] = a[j];
		k++;
		j++;
	}
 
	// Assign sorted data stored in tmp[] to a[].
	for (i = low; i <= high; i++)
		a[i] = tmp[i-low];
};
void MergeSort(double *a, int low, int high)
{
	int mid;
	if (low < high)
	{
		mid=(low+high)/2;
		// Split the data into two half. -> outcalling itself!
		MergeSort(a, low, mid);
		MergeSort(a, mid+1, high);
 
		// Merge them to get sorted output
		Merge(a, low, high, mid);
	}
};

vect::vect(){
	m_N=0;
	m_v=new double [m_N];
	for(int i=0;i<m_N;i++)
		m_v[i]=0;
};
vect::vect(int N, int seed){
	m_N=N;
	srand (seed);
	m_v=new double [N];
	for(int i=0;i<N;i++)
		m_v[i]= rand() / double(RAND_MAX);
};
vect::~vect(){
	delete[] m_v;
};
unsigned int vect::getN()const{
	return m_N;
};
void vect::mergeSorting(){
	MergeSort(m_v, 0, m_N);
	return;
};
int vect::linearSearch(int pos){
	double tmp = m_v[pos];
	for (int i = 0; i < m_N; i++)
	{
		if(tmp == m_v[i])
			return pos;
	}
	cout << "Lin - not found" << endl;
	return -1;
}
int vect::binarySearch(int pos){
	double tmp = m_v[pos];
	int supp = binfunction(m_v, 0, m_N-1, tmp);
	if(supp == pos)
		return pos;
	else
	{
		cout << "Bin - not found" << endl;
		return -1;
	}
}
