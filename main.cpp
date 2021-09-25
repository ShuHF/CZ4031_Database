#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
// #include <boost/algorithm/string.hpp>
#include "Storage.cpp"
using namespace std;

int main()
{
    cout << "*********************************************************|" << endl;
    cout << "| 1) Check Database size                                 |" << endl;
    cout << "| 2) Number of block used                                |" << endl;
    cout << "| 3) Set block size                                      |" << endl;
    cout << "| 4) Build B+ tree on 'numVote'                          |" << endl;
    cout << "| 5) Retrieve movies 'numVotes' = 500                    |" << endl;
    cout << "| 6) Retrieve movies 'numVotes' between to 30000 to 40000|" << endl; 
    cout << "| 7) Deldete movies 'numVotes' = 1000                     |" << endl;
    cout << "*********************************************************|" << endl;
   
   Storage* memStorage = new Storage(100);
   string myText;
   int count =0;
   int index =0;
   unsigned char character=0;
   string line;
   vector<char> v;
   vector<string> parts;
   ifstream filename("C:\\data.tsv");
   filename.ignore(10000,'\n');
  
   //delimiter by tab 
    while (getline (filename, line, '\t')) {
        if(count < 3){
            cout << index << endl;
        }
        else
        {
            count = 0;
        }
        count++;
        
    }
    filename.close();
   

}
