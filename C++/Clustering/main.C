#include <iostream>
#include"functions.h"
using namespace std; 

int main()
{
	cout << endl;
	
	int sizex = 20;
	int sizey = 25;
	int matrix[sizex*sizey];
	loadMatrix(matrix,0.3,sizex, sizey);
	int matrix2[sizex*sizey];
	loadMatrix(matrix2,0.3,sizex, sizey);
	
	cout << "Priting initial matrix" << endl;
	printMatrix(matrix,sizex,sizey);
	cout << endl;
	//four-connectivity
	clustering(matrix,sizex, sizey,true);
	cout << "Priting clustered matrix: 4-connectivity" << endl;
	printMatrix(matrix,sizex,sizey);
	cout << "Number clustered regions " << getNumberOfRegions(matrix,sizex,sizey) << endl;
	cout << endl;
	//eight-connectivity
	clustering(matrix2,sizex, sizey,false);
	cout << "Priting clustered matrix: 8-connectivity" << endl;
	printMatrix(matrix2,sizex,sizey);
	cout << "Number clustered regions " << getNumberOfRegions(matrix2,sizex,sizey) << endl;
	
	return 0;
}
