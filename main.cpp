#include <iostream>
#include <fstream>
#include <string>
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
 
   movieRatingReview movieReview;
   vector <movieRatingReview> vectorOfMovies;
   string line;
   //Read from the data.tsv
   ifstream filename("C:\\data.tsv");
   //ignore the header
   filename.ignore(10000,'\n');
   int count = 0;

   cout << "***************************" << endl;
    cout << "|    Reading Data          |" << endl;
    cout << "| 1) Check Database size: " + to_string(databasesize()) + "|" << endl;
    cout << "| 2) Number of block used  "+ to_string(numBlockUsed()) +" |" << endl;
    cout << "***************************" << endl;

 

    //reading the tsv file the while loop is using the default delimiter (\n) line by line
    while (getline (filename, line)) {
        stringstream linestream(line);
        string row;
        getline(linestream, row, '\t');
        movieReview.movieName = row;
        linestream >> movieReview.averageRating >> movieReview.numVote;
        storeRecordintoBlock(20);
         cout << "This is the block id" + to_string(currentblockid) << endl;
         cout << "This is the size of the current block" + to_string(currentblockSize) << endl;
        //vectorOfMovies.push_back(movieReview);
        //can take out, experiment
        count++;
        if (count>=10)
            break;

    }

    filename.close();
    for (size_t i = 0; i < vectorOfMovies.size(); ++i) {
        //print as seen above, have to overload << operator
        cout << vectorOfMovies[i];
        //print only the movienames
        //cout << vectorOfMovies[i].moviename;
    }    
   

}