#ifndef _functions_h_
#define _functions_h_
#include <climits>
#include <iostream>
using namespace std;

void loadMatrix(int *, float, int, int);
void printMatrix(int *, int, int);
void doUnion(int *, int, int);
void unionCoords(int *, int, int, int, int, int, int, int , int);
void clustering(int *, int, int, bool);
int getNumberOfRegions(int *, int, int);


void loadMatrix(int *v, float p,int sizex, int sizey)
{
    srand(10);
    for (int i = 0; i < sizex*sizey; i++) 
    {
  		 float r = (float) rand()/RAND_MAX;
		 if (r > p)
		 {
			 v[i] = int(0);
		 }
		 else
		 {
			 v[i] = int(1);
		 }
	}
}

void printMatrix(int *v ,int sizex, int sizey)
{
    for (int i = 0; i < sizex; i++)
    {
		for (int j = 0; j < sizey; j++) 
		{
			cout << v[i*sizey+j] << " "; 
		}
		cout << endl;
    }
}

void doUnion(int* component, int a, int b)
{
    // get the root component of a and b, and set the one's parent to the other
    while (component[a] != a)
        a = component[a];
    while (component[b] != b)
        b = component[b];
    component[b] = a;
}

void unionCoords(int *component, int val1, int val2, int x, int y, int x2, int y2, int h, int w)
{
    if (y2 < h && x2 < w && val1 && val2)
        doUnion(component, x*h + y, x2*h + y2);
}

void clustering(int *array ,int w, int h,bool four)
{
	int component[w*h];

    for (int i = 0; i < w*h; i++)
        component[i] = i;
    for (int x = 0; x < w; x++)
    {
		for (int y = 0; y < h; y++)
		{
			if (four == true)
			{
				unionCoords(component, array[x*h+y], array[(x+1)*h+y], x, y, x+1, y, h, w);
				unionCoords(component, array[x*h+y], array[x*h+(y+1)], x, y, x, y+1, h, w);
			}
			else
			{
				unionCoords(component, array[x*h+y], array[(x+1)*h+y], x, y, x+1, y, h, w);
				unionCoords(component, array[x*h+y], array[x*h+(y+1)], x, y, x, y+1, h, w);
				unionCoords(component, array[x*h+y], array[(x+1)*h+(y+1)], x, y, x+1, y+2, h, w);
				unionCoords(component, array[x*h+y], array[(x+1)*h+(y+1)], x, y, x+1, y+1, h, w);
			}
		}
	}
	
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            if (array[x*h+y] == 0)
            {
                continue;
            }
            
            int c = x*h + y;
            while (component[c] != c){
				c = component[c];
			}
			array[x*h+y] = c; 
        }
    }
}

int getNumberOfRegions(int* matrix, int w, int h){
	
	int dim = 1;
	double * v = new double[dim];
	v[0]=0;
	
	for (int k = 0; k < w; k++){
		for (int l = 0; l < h; l++){
			int count2 = 0;
			for(int d = 0; d < dim; d++){
				if(v[d] != matrix[k*h+l]){
					count2++;
				}	
			}
			if (count2 == dim){	
				v[dim] = matrix[k*h+l];
				dim++;
			}
		}
	}
	delete[] v;
	return dim-1;
}



#endif //_functions_h_
