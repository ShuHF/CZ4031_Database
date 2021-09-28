#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <tuple>
#include <vector>
#include "Storage.cpp"
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
    uint8_t *p = new uint8_t [500000000];
    uint8_t *checkPointer;
    int blkPos = 0;
    int count = 0;
    int offset = 1;
    int tempCount=1;
    int logicCount =0;
    int prevBlockID = 0;

    movieRatingReview movieReview;
    vector <movieRatingReview> vectorOfMovies;
    vector <tuple <string, void*>> recordsList;

    //Logical adress with all the physical address of block and offset added
    vector <tuple <uint8_t, tuple <void *, uint8_t>>> mappingTable;
    string line;

    //Read from the data.tsv
    ifstream filename("C:\\data.tsv");
    //ignore the header
    filename.ignore(10000,'\n');

    // strcpy( (char*) name, "Hello World" );
    // for(int i=0;i<sizeof(name);i++){
    //     p[count] = name[i]; 
    // }
    // p[0] = 9;
    // p[1] = 9;
    
    cout << "Start of Array Address: " << &p << endl; //0x5be25ff7f8
    cout << "Index 0 of array: " << &p+1 <<endl; //0x5be25ff800

    //reading the tsv file the while loop is using the default delimiter (\n) line by line
    while (getline (filename, line)) {
        stringstream linestream(line);
        string row;
        getline(linestream, row, '\t');
        movieReview.movieName = row;
        linestream >> movieReview.averageRating >> movieReview.numVote;
        int recordLength = movieReview.movieName.length()+ to_string(movieReview.averageRating).length() + to_string(movieReview.numVote).length();
        storeRecordintoBlock(recordLength);
         cout << "This is the block id: " + to_string(currentblockid) << endl;
         cout << "This is the size of the current block: " + to_string(currentblockSize) << endl;
    
        vectorOfMovies.push_back(movieReview);
        

        //check if block id has changed to determine offset per block address
        if(currentblockid != prevBlockID){
            prevBlockID=currentblockid;
            offset = 0;
            tempCount=0;
        }
        else if(currentblockSize>=sizeof(movieReview)){
            offset = currentblockSize;
            tempCount = currentblockSize;
        }

        //BlockTable holds the block adress and the offset for per record
        //blkPos increments accordingly to the current block
        //Offset starts at 0 ->need confirming
        blkPos = (currentblockid*blockSize);
        cout<<"Block position: "<< to_string(blkPos) << endl;
        tuple<void *, uint8_t> blockTable(&p+blkPos,offset);
        cout<< "Block Address: " << get<0>(blockTable) << endl;
        cout<< "Offset: " << to_string(get<1>(blockTable)) << endl;

        //Add the offset to the physical address 
        void *physicalAddress = (unsigned char *)get<0>(blockTable) + get<1>(blockTable);
        cout << "Block 0: " << get<0>(blockTable) << endl;
        cout << "Block 1: " << to_string(get<1>(blockTable)) << endl;

        //Create a tuple to store the current movie review id and physical address
        cout<< "Physical Address" << physicalAddress << endl;
        tuple< string,void *> recordAddress(movieReview.movieName, physicalAddress);

        //Mapping table input
        tuple <uint8_t, tuple <void *, uint8_t>> tableEntry(logicCount,blockTable);
        mappingTable.push_back(tableEntry);
        logicCount++;

        //Inserting the record into the memory space -> needs to checking
        //using len instead of sizeOf
        p+= recordLength;
        
        memcpy(p, &movieReview,recordLength);
       
        //Insert the current moview review into a record mapping table
        recordsList.push_back(recordAddress);
        tempCount+=0;
        cout << "Current memory used: " << to_string(tempCount) <<"\n" << endl;

        
        //can take out, experiment
         count++;
         if (count>=10)
             break;

    }
      cout << "***************************" << endl;
    cout << "|    Reading Data          |" << endl;
    cout << "| 1) Check Database size: " + to_string(databasesize()) + "|" << endl;
    cout << "| 2) Number of block used  "+ to_string(numBlockUsed()) +" |" << endl;
    cout << "***************************" << endl;


    filename.close();
     for (size_t i = 0; i < vectorOfMovies.size(); ++i) {
         cout << "The record ID: " << get<0>(recordsList[i])<< endl; 
        cout << "The address: " << get<1>(recordsList[i])<< endl;
        cout <<endl;
    //     //print as seen above, have to overload << operator
    //     cout << vectorOfMovies[i];
    //     //print only the movienames
    //     //cout << vectorOfMovies[i].moviename;
     } 
      //Mapping table output 
       for (size_t i = 0; i < mappingTable.size(); ++i) {
         cout << "The logical ID: " << to_string(get<0>(mappingTable[i]))<< endl; 
        //cout << "The address: " << get<1>(mappingTable[i])<< endl;
        cout <<endl;
       }
   

}