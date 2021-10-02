#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <tuple>
#include <vector>
#include "Storage.cpp"
#include "bplus-tree.h"
#include "bplus-tree-insert.cpp"
#include "bplus-tree-remove.cpp"
#include "bplus-tree-search.cpp"
#include "bplus-tree-display.cpp"

using namespace std;


  std::ostream &operator<< (std::ostream &out, const movieRatingReview& object)
        {
            std::cout << "How it appears" << std::endl;
            out << object.movieName << "\t" << object.averageRating << "\t" << object.numVote << std::endl;
            return out;
        }

int main()
{
    //unsigned char name[10];
    movieRatingReview movieReview;
    unsigned char *disk = nullptr;
    disk = new unsigned char [disksize];
    unsigned char *blkPointer = nullptr;
    int blkPos = 0;
    int count = 0;
    int offset = 0;
    int newoffset =0;
    int tempCount=0;
    int logicCount =0;
    int prevBlockID = 0;
    int prevBlockSize = 0;
    int prev=0;

    
    vector <movieRatingReview> vectorOfMovies;
    vector <tuple <int, void*>> recordsList;
    vector <tuple <void *, unsigned char>> recordsList_Test;
    vector <void *> test_address;
    //Storage(500000000,100);
    blkPointer = disk;

    //Logical adress with all the physical address of block and offset added
    vector <tuple <unsigned char, void *>> mappingTable;
    string line;

    //Read from the data.tsv
    ifstream filename("C:\\data.tsv");
    //ignore the header
    filename.ignore(10000,'\n');

    //reading the tsv file the while loop is using the default delimiter (\n) line by line
    while (getline (filename, line)) {
        
        stringstream linestream(line);
        string row;
        getline(linestream, row, '\t');
        strcpy(movieReview.movieName, row.c_str());
        linestream >> movieReview.averageRating >> movieReview.numVote;
        int currentid = storeRecordintoBlock(sizeof(movieReview));
        // cout << "Size of movie record "<< to_string(sizeof(movieReview)) << endl;
         //cout << "This is the block id: " + to_string(currentblockid) << endl;
         //cout << "This is the size of the current block: " + to_string(currentblockSize) << endl;
    
        vectorOfMovies.push_back(movieReview);
        

        //check if block id has changed to determine offset per block address
        if(currentid != prevBlockID){
            offset = 0;
            prev = sizeof(movieReview);
            tempCount=0;
            newoffset = 0;
            prevBlockID=currentid;
        }
        else
        {
            if(tempCount == 0)
            {
                offset = 0;
                prev = sizeof(movieReview);
            }
            else
            { //double check offset
                    offset += prev;
                
            }
        }
      
        //blkPos increments accordingly to the current block
        //Offset starts at 0 ->need confirming
        blkPos = (currentid*blockSize);

        blkPointer = (unsigned char *)disk + blkPos;
        tuple<void *, unsigned char> blockTable(&blkPointer,offset);
     
        //Offset to storage
        uint8_t curPos = offset + blkPos; 

        //Add the offset to the physical address 
        void *physicalAddress = blkPointer+offset;

        //Mapping table input
        tuple <unsigned char, void *> tableEntry(logicCount,physicalAddress);
        mappingTable.push_back(tableEntry);
        logicCount++;

        //Storing the moviewreview object into the physical address      
        memcpy(physicalAddress, &movieReview,sizeof(movieReview));
       
        tempCount++;
               //can take out, experiment
         count++;
        if (count>60)
        {
            physicalAddress = NULL;
            break;
        }

    }
   


    filename.close();

        
          vector<tuple <unsigned char, void *>>::iterator iterator;
        // Print out 
        //    for (iterator = mappingTable.begin(); iterator != mappingTable.end(); ++iterator) {
        //        void *blockAddress = get<1>(* iterator);
        //        cout << "Record: " << ((*(movieRatingReview *) blockAddress).movieName) <<  "\t" << to_string((*(movieRatingReview*) blockAddress).averageRating) << "\t" << to_string((*(movieRatingReview *) blockAddress).numVote) << "\t at " << blockAddress << '\n';
        //    }

    //Experiment 1/
    cout << "***************************" << endl;
    cout << "| After reading Data          |" << endl;
    cout << "| -------------------         |" << endl;
    cout << "| 1) Fixed block size: " + to_string(blockSize) + "|" << endl;
    cout << "| 2) Check Database size: " + to_string(databasesize()) + "|" << endl;
    cout << "| 3) Num of avaliable block: " + to_string(avaliableBlockleft()) + "|" << endl;
    cout << "| 4) Number of block used  "+ to_string(numBlockUsed()) +" |" << endl;
    cout << "***************************" << endl;    

    cout << "completed" <<endl;

    /*** Experiment 2***/
    //Create Tree
    BPTree bptree = BPTree();
     for (iterator = mappingTable.begin(); iterator != mappingTable.end(); ++iterator) {
        void *blockAddress = get<1>(* iterator);
        //bptree.insert((*(movieRatingReview *) blockAddress).numVote);

        float numVotes = (*(movieRatingReview *) blockAddress).numVote;
        key_record record;
        record.value = numVotes;
        record.add_vect.push_back(blockAddress);
        bptree.insert(record);
    }

    

    cout << "***************************" << endl;
    cout << "|    B+ Tree               |" << endl;
    cout << "| 1) Parameter n of B+ Tree: " + to_string(bptree.getmaxKeys()) + "|" << endl;
    cout << "| 2) Number of nodes  "+ to_string(bptree.getnumNodes()) +" |" << endl;
    cout << "| 3) Height of Tree  "+ to_string(bptree.height(bptree.getRoot())) +" |" << endl;
    cout << "| 4) Root node and its child node  " << endl;
    bptree.display(bptree.getRoot());
    cout << "***************************" << endl;
    
    //Experiement 3
    // bptree.search(51);

    bptree.search(15);
    





    disk = NULL;
    blkPointer = nullptr;
    recordsList.clear();
    recordsList_Test.clear();
    vectorOfMovies.clear();
    mappingTable.clear();
    delete disk;
    delete blkPointer;

   

}