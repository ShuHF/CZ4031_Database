#include <iostream>
#include <fstream>
#include <string>
#include "Storage.h"
using namespace std;

int blockSize=100;
unsigned char * diskspace= ( unsigned char * )malloc( 100000000 * sizeof( unsigned char ) );

Storage::Storage(int blockSize) {     // Constructor
  blockSize = blockSize;
}

int Storage::getDiskCapacitySize()
{
  return 0;
}

int Storage::getDatabaseSize()
{
  //Calcaluation added later
  return Storage::getDiskCapacitySize()-blockSize;
}

void Storage::setBlockSize(int block)
{
  Storage::blockSize = block;
}

int Storage::getBlockSize()
{
  return blockSize;
}
void Storage::readData()
{
  string myText;
  int count =0;
  ifstream filename("C:\\data.tsv");

//  while (getline (inFile, myText)) {
//   // Output the text from the file
//   if (count <){
//     cout << myText << endl;
//     count++;
//   }
    
// //   }
// FILE* input_file = fopen(filename.c_str(), "r");
//     if (input_file == nullptr) {
//        return 0;
//     }
// while (!feof(filename)) {
//        character = getc(input_file);
//        cout << character << "-";
//     }

}
void Storage::freeDisk(){
  free(diskspace);
}
   

    
