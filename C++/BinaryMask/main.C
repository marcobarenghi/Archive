#include <iostream>
#include"binarymask.h"
using namespace std; 

int main()
{
	
	binarymask bin;
	bin = binarymask(0.1, 50, 50);
	bin.printToFile("input.bin");
	bin.dilate(1,1);
	bin.printToFile("afterDilation.bin");
	bin.erode(1,1);
	bin.printToFile("afterErosion.bin");
	bin.closegap(3,3);
	bin.printToFile("afterCloseGap.bin");
	return 0;
}
