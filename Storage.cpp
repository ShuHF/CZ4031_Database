#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "Storage.h"
using namespace std;

int blockSize=100;
unsigned char * diskspace= ( unsigned char * )malloc( 100000000 * sizeof( unsigned char ) );

Storage::Storage(int blockSize) {     // Constructor
  blockSize = blockSize;
}

int Storage::getDiskCapacitySize()
{
  return sizeof(diskspace);
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
// void Storage::readData() //for by line -> issue string spilt
// {
//   string line;
//   int count =0;
//   char character = 0;
//   char temp;
//   ifstream filename("C:\\data.tsv");
//   filename.ignore(10000,'\n');
  
//   while (getline (filename, line)) {
//   // Output the text from the file
//     vector<string> parts;
//     split(parts, line, boost::is_any_of("\t"));

//     for(int i=0; i<parts[i].length(); i++){
//       char char_array[parts[i].length()];
//       strcpy(char_array, parts[i].c_str());
//        for (int k = 0; k < parts[i].length(); k++)
//         diskspace[count]=char_array[k];
//         count++;
//     }
    
    
//   }
//   filename.close();
// }
void Storage::readData(){ //read by char -> issue havent ignored the headers
  string myText;
  int count =0;
  unsigned char character=0;
  string filename("C:\\data.tsv");

FILE* input_file = fopen(filename.c_str(), "r");
    if (input_file == nullptr) {
       cout <<"Failure to read" <<endl;
    }
while (!feof(input_file)) {
       character = getc(input_file);
       diskspace[count]=character;
       count++;
    }

}
void Storage::freeDisk(){
  free(diskspace);
}
void Storage::printContents(){
  int diskSize = getDiskCapacitySize();
  int i=0;
  do{
      cout << diskspace[i];
      i++;
  }while(diskspace[i] != NULL);
    
  }


   

    
