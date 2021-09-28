#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Storage.h"
using namespace std;

/*block size to either 100Mb/ 500Mb
 *disk size = disk storage or disk capacity
 * blockid = which record is assign to which block
 * currentblockid = for checking size of block
 * numberofavaliableblock = find out how many block can be created based on the disksize
 * currentblockSize = get the current block size that is using
 * totalSpaceUsed = total space used up by the record*/
int blockSize=100;
  int disksize = 100000000;
  int blockid = 0;
  int currentblockid = 0;
  int numberofavaliableblock = disksize / blockSize;
  int currentblockSize = 0;
  int totalSpaceUsed = 0;
  

//Constructor to initialize the class
Storage::Storage(int disksize, int blocksize )
{
  this->blockSize=100;
  this->disksize = 100000000;
  this->blockid = 0;
  this->currentblockid = 0;
  this->numberofavaliableblock = disksize / blockSize;
  this->currentblockSize = 0;
  this->totalSpaceUsed = 0;

}

/*
 *This function is used to figure out how to store the record in the diskplace based on the 4 scenario
 *1. Reject if the record is bigger then the blocksize specified
 *2. Reject if there is no more avaliable block size
 *3. Add the record into a new block if the record cant fit in the current block
 *4. Add the record into current block 
 *
 * According to the lecture to refer to a record required address, block id
 **/
void storeRecordintoBlock(int recordSize)
{
  if(recordSize == 0)
  {
    cout<< "No record to be added!"<< endl;
  }
  //Scenario 1 where the record size is greater then the blocksize
  if(recordSize > blockSize)
  {
    cout<< "The record size excceed the block size specified!" <<endl;
  }
  //Scenario 2 if record size cant be fit in the current blk and there are no more avaliable block 
  else if(((currentblockSize + recordSize) > blockSize) && (currentblockid == numberofavaliableblock))
  {
    cout<< "Unable to store record as there are no avaliable space in the disk!" <<endl;
  }
  //scenario 3 if the record size + current block id size is more than the block size and there are avaliable block
  else if((currentblockSize + recordSize) > blockSize)
  {
    //Change to new block 
    currentblockid ++;
    /*
    * CODES HERE TO STORE IT
    */
    numberofavaliableblock --;
    currentblockSize = 0;
    currentblockSize += recordSize;
  }
 //Scenario 4 ample space to fit the record in the current block without exceeding the block size specified 
 else
 {
   /**
    * CODES HERE TO STORE IT INTO THE BLOCK
    * */
   currentblockSize += recordSize;
 }
 totalSpaceUsed += recordSize;
}

/* 
*This function is returning number of avaliable blocks left (excluding the current one)
*/
int avaliableBlockleft()
{
  return numberofavaliableblock;
}

/*
*The total space used up by storing the record
*/
int databasesize()
{
  return totalSpaceUsed;
}

/**
 * This function is return the number of blocks used up (including current block)
 **/
int numBlockUsed()
{
   return currentblockid + 1;
}
void delerecord(uint8_t logical_address, vector<tuple <uint8_t, tuple <void *, uint8_t>>> mappingTable, uint8_t offset, int size)
{
  for(int i=0;i<mappingTable.size();i++){
    if(logical_address == get<0>(mappingTable[i]))
       {

         get<0>(get<1>(mappingTable[i])) = nullptr;
         currentblockSize -= size;
         totalSpaceUsed -= size;
       }

  }
       
} 

