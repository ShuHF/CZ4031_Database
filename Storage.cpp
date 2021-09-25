#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include <boost/algorithm/string.hpp>
#include "Storage.h"
using namespace std;

int blockSize=100;
unsigned char * diskspace;

Storage::Storage(int blockSize) {     // Constructor
  this->blockSize = blockSize;
  diskspace = ( unsigned char * )malloc( 100000000 * sizeof( unsigned char ) );
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
  this->blockSize = block;
}

int Storage::getBlockSize()
{
  return blockSize;
}
int Storage::getNumBlock()
{
  return 10000000/this->blockSize;
}
// void Storage::readData() //for by line -> issue string spilt
// {
//   string line;
//   int count =0;
//   char character = 0;
//   char temp;
//   vector<char> v;
//   vector<string> parts;
//   ifstream filename("C:\\data.tsv");
//   filename.ignore(10000,'\n');
  
//   while (getline (filename, line)) {
//   // Output the text from the file
    
//     split(parts, line, boost::is_any_of("\t"));

//     for(int i=0; i<parts[i].size(); i++){
//       // char char_array[parts[i].length()];
//       // strcpy(char_array, parts[i].c_str());
//       copy(parts[i].begin(), parts[i].end(), back_inserter(v));
//        for (int k = 0; k < v.size(); k++){
//          diskspace[count]=v[k];
//          count++;
//        }
//        v.clear();
        
//     }
//     parts.clear();
    
    
//   }
//   filename.close();
// }
// void Storage::readData(){ //read by char -> issue havent ignored the headers
//   string myText;
//   int count =0;
//   unsigned char character=0;
//   string filename("C:\\data.tsv");

// FILE* input_file = fopen(filename.c_str(), "r");
//     if (input_file == nullptr) {
//        cout <<"Failure to read" <<endl;
//     }
// while (!feof(input_file)) {
//        character = getc(input_file);
//       if(count>29) //temp solution to ignore headers
//        diskspace[count-30]=character;
//       count++;
//     }

// }

void Storage::freeDisk(){
  free(diskspace);
}

//print all the records in database, Change condition from NULL to any number for content checking
void Storage::printContents(){ 
  int diskSize = getDiskCapacitySize();
  int i=0;
  do{
      cout << diskspace[i];
      i++;
  }while(i<60);  //change to i < 60 for 3 record showing, last tconstant is tt9916778 -> (diskspace[i] != NULL)
  }

  


   

    
