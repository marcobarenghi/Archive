#include"binarymask.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

binarymask::binarymask(){
	m_col = 0;
	m_row = 0;
};

binarymask::binarymask(float p, int col, int row){
	m_col = col;
	m_row = row;
	m_grid=new unsigned int[m_col*m_row];
	srand(10);
	for (int i = 0; i < m_col*m_row; i++)
	{
  		float r = (float) rand()/RAND_MAX;
		if (r > p)
		{
			m_grid[i] = int(0);
		}
		else
		{
			m_grid[i] = int(1);
		}
	}
		
};

binarymask::~binarymask(){
	//delete [] m_grid;
};

void binarymask::print(){
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			cout << m_grid[i*m_col+j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


void binarymask::printToFile(const std::string& name){
	uint8_t buffer[m_col*m_row];
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			if ( m_grid[i*m_col+j] > 0)
				buffer[i*m_col+j] = 0;
			else 
				buffer[i*m_col+j] = 255;
		}
	}
	cout << "Saving mask in " << name << endl;
	ofstream output(name, ios::out | ios::binary);
	output.write((char*)(&buffer), sizeof(buffer));
    output.close();
	cout << endl;
}

void binarymask::printToFile2(const std::string& name, int ratio){
	uint8_t buffer[m_col*m_row*ratio];
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			for (int ii = 0; ii < ratio; ii++)
			{
				for (int jj = 0; jj < ratio; jj++)
				{
					if ( m_grid[i*m_col+j] > 0)
						buffer[(i)*m_col*ratio + ii*m_col +j*ratio+jj] = 0;
					else 
						buffer[i*m_col+j] = 255;
				}
			}
		}
	}
	cout << "Saving mask in " << name << endl;
	ofstream output(name, ios::out | ios::binary);
	output.write((char*)(&buffer), sizeof(buffer));
    output.close();
	cout << endl;
}

void binarymask::dilate(int x, int y){
	unsigned int *buffer = new unsigned int[m_col*m_row];
	int len = sizeof(unsigned int)*m_col*m_row;
	memcpy(buffer, m_grid,len);
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			if (buffer[i*m_col+j] == 1)
			{
				for (int k = -y; k <= y; k++)
				{
					for (int l = -x; l <= x; l++)
					{
						if (i + k >= 0 && i + k < m_row && j + l >= 0 && j + l < m_col)
							m_grid[(i+k)*m_col + (j+l)] = 1;
					}
				}
			}
			
		}
	}
	delete [] buffer;
}

void binarymask::erode(int x, int y){
	unsigned int *buffer = new unsigned int[m_col*m_row];
	int len = sizeof(unsigned int)*m_col*m_row;
	memcpy(buffer, m_grid,len);
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			if (buffer[i*m_col+j] == 1)
			{
				for (int k = -y; k <= y; k++)
				{
					for (int l = -x; l <= x; l++)
					{
						if (i + k >= 0 && i + k < m_row && j + l >= 0 && j + l < m_col)
						{
							if (buffer[(i+k)*m_col + (j+l)] == 0)
							{
								m_grid[i*m_col+j] = 0;
							}
								
						}
					}
				}
			}
			
		}
	}
	delete [] buffer;
}

//THIS CLOSEGAP FUNCTION CAN PRODUCE MASKS WITH GAPS!
//THE CLOSEGAP FUNCTION IS INTENDED TO CLOSE SMALL GAPS BETWEEN LARGE REGIONS
void binarymask::closegap(int x, int y){
	unsigned int *buffer = new unsigned int[m_col*m_row];
	int len = sizeof(unsigned int)*m_col*m_row;
	memcpy(buffer, m_grid,len);
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			if (buffer[i*m_col+j] == 1)
			{
				//VERTICAL
				bool foundVer = false;
				int distVer = 0;
				for (int k = 1; k <= y+1; k++)
				{
					if (i + k >= 0 && i + k < m_col && buffer[(i+k)*m_col+j] == 1 )
					{
						foundVer = true;
						distVer = k+1;
					}	
				}
				if (foundVer == true)
				{
					for (int m = 1; m < distVer; m++)	
						m_grid[(i+m)*m_col+j] = 1;
				}
				
				//HORIZONTAL
				bool foundHor = false;
				int distHor = 0;
				for (int l = 1; l <= x+1; l++)
				{
					if (j + l >= 0 && j + l < m_col && buffer[i*m_col+j+l] == 1 )
					{
						foundHor = true;
						distHor = l+1;
					}	
				}
				if (foundHor == true)
				{
					for (int mm = 1; mm < distHor; mm++)
						m_grid[i*m_col+j+mm] = 1;
				}
			}
			
		}
	}
	delete [] buffer;
}
