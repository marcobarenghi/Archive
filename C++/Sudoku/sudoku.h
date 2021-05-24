#ifndef _sudoku_h_
#define _sudoku_h_
#define N 9
class sudoku{
public:
	sudoku();
	~sudoku();
	void loadSudoku(int input[N][N]);
	void prinPrettySudoku();
	bool isSafe(int, int, int);
	bool solveSuduko(int,int);
	bool doubleCheck();
	void isReallySolved();
private:
	unsigned int m_grid[N][N];
};
#endif
 

