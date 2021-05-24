The naive approach is to generate all possible configurations of numbers 
from 1 to 9 to fill the empty cells. Try every configuration one by one
until the correct configuration is found, i.e. for every unassigned position
fill the position with a number from 1 to 9. After filling all the unassigned 
position check if the matrix is safe or not. If safe print else recurs for other cases.

EXERCISE: solve sudoku!

Try to fill each empty cell with 1-9 numbers until the correct config is found.
Three cases must be distinguished in the solution.
- correct and solvable input: solveSudoku and doubleCheck return true
- incorrect input (with NO repetetions in lines and columns): solveSudoku return false and doubleCheck return false
- incorrect input (WITH repetetions in lines and columns): solveSudoku return true and doubleCheck return false

Therefore the function isReallySolved is called.
