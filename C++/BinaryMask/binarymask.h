#ifndef _binarymask_h_
#define _binarymask_h_
#include <iostream>

class binarymask{
public:
        binarymask();
        binarymask(float, int, int);
        ~binarymask();
        void print();
        void printToFile(const std::string&);
        void dilate(int, int);
        void erode(int, int);
        void closegap(int, int);
        
private:
        unsigned int* m_grid;
        int m_col;
        int m_row;
};

#endif

