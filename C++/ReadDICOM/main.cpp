#include <Magick++.h> 
#include <iostream> 
#include <fstream>
#include <dirent.h>
#include <cstring>
#include <list>
using namespace Magick; 
using namespace std;

void DICOMto8bitRBG(string FileName);
void LoadDICOMVol(char* DirPath, uint8_t *vol);
void AddSlicetoVol(string entryname, uint8_t *vol, int nSLice);
int countFile(char* DirPath);
void printCoronalSlice(uint8_t *vol, int slice, int zDim);
void printSagittalSlice(uint8_t *vol, int slice, int zDim);
void printTransaxialSlice(uint8_t *vol, int slice, int zDim);

#define xDim 512
#define yDim 512

int main(int argc,char **argv) 
{ 
   // Initialise ImageMagick library
   InitializeMagick(*argv);

   // Read dicom and convert to 8bit image (.bin file)
   cout << "DICOM COLLECTION OF SAGGITAL CRANIAL SLICES from: " << endl;
   cout << "http://www.theobjects.com/dragonfly/learn-sample-datasets.html" << endl;
   cout << "------------------------------------------------------------------------------" << endl << endl;
   
   cout << "Read a test slice (DICOM) and convert to 8-bit BW image (.bin file)" << endl;
   string InputName = "slice-test";
   DICOMto8bitRBG(InputName);
   cout << "------------------------------------------------------------------------------" << endl << endl;
   
   //Part 2
   cout << "Loading all .dcm files (512x512) from directory and extract slices" << endl;
   char InputDir[200] = "/home/marcobarenghi/Desktop/MyGitArchive/C++/ReadDICOM/512x512";
   int nFiles = countFile(InputDir);
   cout << "Number of files read: " << nFiles << endl;
   
   //CAN NOT BE DECLARED AS DYNAMIC DUE TO LARGE SIZE -> COUNT FILES FIRST
   unsigned long nVoxels = xDim*yDim*nFiles;
   cout << "Number of total voxels " << nVoxels << endl;
   uint8_t* vol = new uint8_t[nVoxels];

   // Load volume and get slices
   LoadDICOMVol(InputDir, vol);
   
   int sagSlice = 100;
   int corSlice = 250;
   int traSlice = 150;
   printSagittalSlice(vol, sagSlice, nFiles);
   printCoronalSlice(vol, corSlice, nFiles);
   printTransaxialSlice(vol, traSlice, nFiles);
   cout << "------------------------------------------------------------------------------" << endl << endl;

   cout << "RETURNING" << endl;
   delete [] vol;
   return 0;
}

void DICOMto8bitRBG(string FileName)
{
   cout << "Reading file" << endl;
   Image image(FileName+".dcm"); 

   // Get dimensions with GM -> nice to have
   int w = image.columns(); 
   int h = image.rows();
   cout << "Dimensions: " << w << "x" << h << endl;
	
   // Create RBG image
   PixelPacket *pixels = image.getPixels(0, 0, w, h);
   int maxRed = 0;
   int maxGreen = 0;
   int maxBlue = 0;

   // Find maxs -> rescale later
   for(int y=0; y<h; y++)
   {
      for(int x=0; x<w; x++)
      {
         Color color = pixels[w * y + x];
         if (color.redQuantum() > maxRed)
         {
			 maxRed = color.redQuantum();
		 }
		 if (color.blueQuantum() > maxBlue)
         {
			 maxBlue = color.blueQuantum();
		 }
		 if (color.greenQuantum() > maxGreen)
         {
			 maxGreen = color.greenQuantum();
		 }
      }
   } 
   
   //convert to 8bit image (arbitraty - save memory)
   //RBG -> grayscale via average method
   string outputName = FileName+"-out.bin";
   ofstream output(outputName, ios::out | ios::binary);
   uint8_t outarray[w * h];
   for(int y=0; y<h; y++)
   {
      for(int x=0; x<w; x++)
      {
		  Color color = pixels[w * y + x];
		  outarray[w * y + x] = ((((color.redQuantum() * 255 / maxRed) + (color.blueQuantum() * 255 / maxBlue) + (color.greenQuantum()  * 255/ maxGreen)) / 3)) ;
	  }
   }
   output.write((char*)(&outarray), sizeof(outarray));
   output.close();
   cout << "DICOM converted to 8bit .bin" << endl;
   cout << "To convert to .png type:" << endl;
   cout << "gm convert -depth 8 -size 512x512 gray:slice-test-out.bin " << FileName << "-out.png" << endl;
}

void LoadDICOMVol(char *DirPath, uint8_t *vol){
	DIR *pDIR;
	cout << "Loading volume from: "<<  DirPath << endl;
    int count = 0;
    struct dirent *entry;

    list<string> mylist;
    list<string>::iterator it; 
     
    //C++ does not read files in alphabetical order -> read, load list and sort 
    if( pDIR=opendir(DirPath))
    {
       while(entry = readdir(pDIR))
       {				
           if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
           {
              //cout << entry->d_name << "\n";
              string IN = string(DirPath) +  "/" +string(entry->d_name);
              mylist.push_back(IN);			  
	       }
       }
       closedir(pDIR);
    }
    
	//with sorted list call AddSlicetoVol    
    mylist.sort();
    for (it=mylist.begin(); it!=mylist.end(); ++it)
    {	
		AddSlicetoVol(*it, vol, count);
		count++;	
	}
	
	cout << "Volume is loaded!" << endl;
}

void AddSlicetoVol(string EntryName, uint8_t *vol , int nSLice){
   Image image(EntryName); 

   // Get dimensions
   int w = image.columns();
   int h = image.rows();
	
   // Create RBG image
   PixelPacket *pixels = image.getPixels(0, 0, w, h);
   int maxRed = 0;
   int maxGreen = 0;
   int maxBlue = 0;

   // Find maxs -> rescale later
   for(int y=0; y<h; y++)
   {
      for(int x=0; x<w; x++)
      {
         Color color = pixels[w * y + x];
         if (color.redQuantum() > maxRed)
         {
			 maxRed = color.redQuantum();
		 }
		 if (color.blueQuantum() > maxBlue)
         {
			 maxBlue = color.blueQuantum();
		 }
		 if (color.greenQuantum() > maxGreen)
         {
			 maxGreen = color.greenQuantum();
		 }
      }
   }   
   
   //convert to 8bit image (arbitraty - save memory)
   //RBG -> grayscale via average method
   for(int y=0; y<h; y++)
   {
      for(int x=0; x<w; x++)
      {  
		  Color color = pixels[w * y + x];
		  vol[w * y + x + (nSLice*w*h)] = ((((color.redQuantum() * 255 / maxRed) + (color.blueQuantum() * 255 / maxBlue) + (color.greenQuantum()  * 255/ maxGreen)) / 3)) ;
	  }
   }

}

int countFile(char* DirPath){
        DIR *pDIR;
        int count = 0;
        struct dirent *entry;
        if( pDIR=opendir(DirPath)){
                while(entry = readdir(pDIR)){
					
                        if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
                        {
                        count++;
					}       
                }
                closedir(pDIR);
        }
        return count;
}

void printCoronalSlice(uint8_t *vol, int slice, int zDim){
   cout << "Printing Coronal slice n:  " << slice << endl;
   ofstream outputtest("coronalSlice.bin", ios::out | ios::binary);
   uint8_t outarraytest[xDim * zDim];
   
   //coronal 
   //BECOMES METHOD
   for (int i = 0; i < zDim; i++)
   {
	   for (int l = 0; l < xDim; l++)
	   {
			outarraytest[i + l*zDim] = vol[slice + i * yDim*xDim + l * xDim];
	   }
   }
   outputtest.write((char*)(&outarraytest), sizeof(outarraytest));
   outputtest.close();
   cout << "To convert to .png type:" << endl;
   cout << "gm convert -depth 8 -size 192x512 gray:coronalSlice.bin coronalSlice.png" << endl;
   
}

void printSagittalSlice(uint8_t *vol, int slice, int zDim){
   cout << "Printing Sagittal slice n:  " << slice << endl;
   ofstream outputtest("sagittalSlice.bin", ios::out | ios::binary);
   uint8_t outarraytest[xDim * yDim];
   
   //coronal 
   //BECOMES METHOD
   for (int i = 0; i < yDim; i++)
   {
	   for (int l = 0; l < xDim; l++)
	   {
			outarraytest[i + l*xDim] = vol[i + l*xDim + xDim*yDim*slice];
	   }
   }
   outputtest.write((char*)(&outarraytest), sizeof(outarraytest));
   outputtest.close();
   cout << "To convert to .png type:" << endl;
   cout << "gm convert -depth 8 -size 512x512 gray:sagittalSlice.bin sagittalSlice.png" << endl;
   
}

void printTransaxialSlice(uint8_t *vol, int slice, int zDim){
   cout << "Printing Transaxial slice n:  " << slice << endl;
   ofstream outputtest("transaxialSlice.bin", ios::out | ios::binary);
   uint8_t outarraytest[yDim * zDim];
   
   //coronal 
   //BECOMES METHOD
   for (int i = 0; i < zDim; i++)
   {
	   for (int l = 0; l < xDim; l++)
	   {
			outarraytest[i + l*zDim] = vol[slice * xDim + i * yDim*xDim + l];
	   }
   }
   outputtest.write((char*)(&outarraytest), sizeof(outarraytest));
   outputtest.close();
   cout << "To convert to .png type:" << endl;
   cout << "gm convert -depth 8 -size 192x512 gray:transaxialSlice.bin transaxialSlice.png" << endl;
}


