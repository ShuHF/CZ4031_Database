#include <iostream>
class Storage {     // The class
  public:           // Access specifier
    int diskCapacity;
    int blockSize;
    Storage(int diskCapacity, int blockSize);
};   

    Storage::Storage(int diskCapacity, int blockSize) {     // Constructor
      cout << "Hello World!";
    }
    
