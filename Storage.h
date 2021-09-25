#include <iostream>
#include <fstream>
using namespace std;
class Storage {     // The class
  public:           // Access specifier
    int blockSize;
    int memory;
    unsigned int capacity;
    unsigned char * diskspace;
  public:  
    Storage(int blockSize, int memory);
    public: 

      int getDiskCapacitySize();
      int getDatabaseSize();
      void setBlockSize(int block);
      int getBlockSize();
      void readData();
      void freeDisk();
      void printContents();
      int getNumBlock();
      void calcBlocksUsed();
};