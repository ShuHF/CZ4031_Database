#include <iostream>
#include <fstream>
using namespace std;

class Storage {     // The class
  public:           // Access specifier
    int blockSize=100;
    string disk [100000000];
    Storage(int blockSize) {     // Constructor
      blockSize = blockSize;
    }
    public: 

      int getDiskCapacitySize()
      {
        return sizeof(disk);
      }

      int getDatabaseSize()
      {
        //Calcaluation added later
        return getDiskCapacitySize()-blockSize;
      }

      void setBlockSize(int block)
      {
          blockSize = block;
      }

      int getBlockSize()
      {
          return blockSize;
      }
      void readData()
      {
          
      }


};   

    
    
