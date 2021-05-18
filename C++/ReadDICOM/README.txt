!!Install GraphicsMagick!!
run with: g++ main.cpp -o sample $(Magick++-config --cppflags --cxxflags --ldflags --libs)

EXERCISE: reading DICOM file and/or volume (multiple DICOM files)
1- load dicom file and convert to 8bit BW image (in your folder)
2- load a volume and get slices. Again, convert to 8bit image. Place data in a folder.
   NOTE: distorsion will be visible due to different pixel size!

