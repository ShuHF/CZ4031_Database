#include <iostream>
#include <fstream>
using namespace std;
class Storage {     // The class
  public:           // Access specifier
    int blockSize;
    char disk [];
  public:  
    Storage(int blockSize);
    public: 

      int getDiskCapacitySize();
      int getDatabaseSize();
      void setBlockSize(int block);
      int getBlockSize();
      void readData();
      void freeDisk();
}; 
