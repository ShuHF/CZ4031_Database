#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
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
    cout << "| 7) Delete movies 'numVotes' = 1000                     |" << endl;
    cout << "*********************************************************|" << endl;
   
   Storage* memStorage = new Storage(100);
   string myText;
   int count =0;
   unsigned char character=0;
   string line;
   vector<char> v;
   vector<string> parts;
   ifstream filename("C:\\data.tsv");
   filename.ignore(10000,'\n');
  
    while (getline (filename, line)) {
    // Output the text from the file
        
        split(parts, line, boost::is_any_of("\t"));
        for(unsigned i = 0; i < parts.size(); i++)
        {
            cout <<parts.at(i);
        }
        // for(int i=0; i<3; i++){
        // // char char_array[sizeof(parts[i])];
        //     cout <<parts[i] <<endl;
        // // strcpy(char_array, parts[i].c_str());
        // //copy(parts[i].begin(), parts[i].end(), back_inserter(v));
        // // for (int k = 0; k < v.size(); k++){
        // //     memStorage->diskspace[count]=v[k];
        // //     count++;
        //  }
        //v.clear();
            
        //}
        //parts.clear();
        
        break;
    }
    filename.close();
   
   //memStorage->printContents();
   //Testing to get diskspace size
   //cout << "Char : " << memStorage->diskspace[8]<< endl;
   //memStorage->freeDisk();
}
