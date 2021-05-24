#include"sudoku.h"
#include <iostream>
using namespace std;
#define N 9

sudoku::sudoku(){
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			m_grid[j][i] = 0;
	}
};

sudoku::~sudoku(){
};

//load sudoku
void sudoku::loadSudoku(int input[N][N]){
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			m_grid[j][i] = input[j][i];
	}
};

//print a very pretty sudoku scheme
void sudoku::prinPrettySudoku()
{
	cout << "- - - - - - - - - - - - - - - - - - - " << endl;
    for (int i = 0; i < N; i++)
    {
		cout << "| ";
        for (int j = 0; j < N; j++)
        {
			if (m_grid[i][j] == 0)
				cout << "  | ";
			else
				cout << m_grid[i][j] << " | ";
		}
        cout << endl << "- - - - - - - - - - - - - - - - - - - " << endl;
    }
    cout << endl;
}

// Check if it is ok to assign num to grid[col][row]
bool sudoku::isSafe(int row, int col, int num)
{
    for (int x = 0; x <= 8; x++)
        if (m_grid[row][x] == num)
            return false; 

    for (int x = 0; x <= 8; x++)
        if (m_grid[x][col] == num)
            return false;
 
    int startRow = row - row % 3,
            startCol = col - col % 3;
   
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (m_grid[i + startRow][j +
                            startCol] == num)
                return false;
 
    return true;
}
 
bool sudoku::solveSuduko(int row, int col)
{
    // if we arrived to the end
    if (row == N - 1 && col == N)	
    {
		return true;
	}
	
    if (col == N) {
        row++;
        col = 0;
    }
   
    if (m_grid[row][col] > 0)
        return solveSuduko(row, col + 1);
 
    for (int n = 1; n <= N; n++)
    {      
        //check if value can be assigned to grid
        if (isSafe(row, col, n))
        {  
            m_grid[row][col] = n;
           
            //check in next column
            if (solveSuduko(row, col + 1))
                return true;       
        }  
        //if it wasn't safe, try again
        m_grid[row][col] = 0;
    }
    
    return false; 
}

//solveSuduko does not deal with wrong input cases with repetions
//in col or rows, e.g. (3,3,0,1,3,4,2,6,8)
void sudoku::isReallySolved(){
	//ALWAYS call solveSuduko(0,0);
	bool attempt = solveSuduko(0,0);
	bool check = doubleCheck();
	
	if (attempt && check)
		cout << "SUDOKU IS SOLVED AND CHECKED" << endl;
	else if (attempt == true && check == false)
		cout << "SUDOKU CAN NOT BE SOLVED - CHECK YOUR INPUT" << endl;
	else
		cout << "CAN NOT BE SOLVED" << endl;
}

//double check checks final grid
bool sudoku::doubleCheck(){
	int countGoodLines = 0;
	for (int i = 0; i < N; i++)
	{
		int count = 1;
		for (int j = 1; j < N; j++)
		{
			if(m_grid[i][0] != m_grid[i][j])
				count++;
		}
		if (count == N)
			countGoodLines++;
	}
	if (countGoodLines == N)
		return true;
	else
		return false;
}
