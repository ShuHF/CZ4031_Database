#include <iostream>
#include <fstream>
using namespace std;
struct movieRatingReview{
    string movieName;
    float averageRating;
    unsigned int numVote;
    };
class Storage {     // The class
  public:
    
  private:
      int blockSize;
      int disksize;
      int blockid;
      int currentblockid;
      int numberofavaliableblock;
      int currentblockSize;
      int totalSpaceUsed;    
     
  public: 
      Storage(int disksize, int blocksize);
      void storeRecordintoBlock(int recordSize);
      int avaliableBlockleft();
      int databasesize();
      int numBlockUsed();
     
   };
