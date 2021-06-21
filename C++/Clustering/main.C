#include <iostream>
#include"functions.h"
using namespace std; 

int main()
{
	cout << endl;
	int sizex = 10;
	int sizey = 10;
	int matrix[sizex*sizey];
	loadMatrix(matrix,0.25,sizex, sizey);
	int matrix2[sizex*sizey];
	loadMatrix(matrix2,0.25,sizex, sizey);
	
	cout << "  Priting initial matrix" << endl;
	printMatrix(matrix,sizex,sizey);
	cout << endl;
	//four-connectivity
	clustering(matrix,sizex, sizey,true);
	cout << "  Priting clustered matrix: 4-connectivity" << endl;
	printPrettyMatrix(matrix,sizex,sizey);
	cout << "  Number of clustered regions: " << getNumberOfRegions(matrix,sizex,sizey) << endl;
	cout << endl;
	//eight-connectivity
	
	clustering(matrix2,sizex, sizey,false);
	cout << "  Priting clustered matrix: 8-connectivity" << endl;
	printPrettyMatrix(matrix2,sizex,sizey);
	cout << "  Number of clustered regions: " << getNumberOfRegions(matrix2,sizex,sizey) << endl;
	
    cout << endl;
	
	return 0;
}
