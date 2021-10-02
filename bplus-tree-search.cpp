// Search keys in a B+ tree
#include <iostream>

#include "bplus-tree.h"
using namespace std;

Node* BPTree::search(int key, bool flag, bool rangeflag, int key2){
    // if tree is empty
    if (root == NULL)
        cout << "B+ Tree is empty!\n";
    else // else, traverse through the nodes
    {
        Node *cursor = root;

        // traverse till we reach a leaf node
        while(cursor->is_leaf == false)
        {
            for(int i=0; i < cursor->size; i++){
                if(key < cursor->keys[i].value)
                {
                    cursor = cursor->ptr[i];
                    break;
                }
                if(i == cursor->size - 1) // if reach end of keys in this node
                {
                    cursor = cursor->ptr[i+1];
                    break;
                }
            }
        }
        // traverse to find node with key
        int sumDataBlock = 0;
        int counter = 0;
        float avgTotalAvgRating = 0;
        for(int i=0; i< cursor->size; i++){
           if(rangeflag == false)
           {
                if(cursor->keys[i].value == key)
                {
                    if(flag == true)
                    {
                        cout << to_string(cursor->keys[i].value) +  " Found!\n";
                        for (int j = 0; j < cursor->keys[i].add_vect.size(); ++j) {
                            if(counter <= 4)
                            {
                                    printf("\n");
                                    printf("tconst: ");
                                    cout << (*(movieRatingReview *) cursor->keys[i].add_vect[j]).movieName << "\n";
                            }
                            avgTotalAvgRating += (*(movieRatingReview *) cursor->keys[i].add_vect[j]).averageRating;
                            counter++;
                            sumDataBlock++;
                        }
                        cout << to_string((avgTotalAvgRating/sumDataBlock)) <<endl;
                        cout << to_string(sumDataBlock) << endl;
                        cout << to_string(cursor->keys[i].add_vect.size())<<endl;
                    }
                
                    return cursor;
                }
           }
           //Only for range searching
           else if(rangeflag == true && flag == true)
           {
               if (cursor->keys[i].value >= key && cursor->keys[i].value <= key2)
               {
                        for (int j = 0; j < cursor->keys[i].add_vect.size(); ++j) {
                            if(counter <= 4)
                            {
                                    printf("\n");
                                    printf("tconst: ");
                                    cout << (*(movieRatingReview *) cursor->keys[i].add_vect[j]).movieName << "\n";
                            }
                            avgTotalAvgRating += (*(movieRatingReview *) cursor->keys[i].add_vect[j]).averageRating;
                            counter++;
                            sumDataBlock++;
                        }
               }
                cout << to_string((avgTotalAvgRating/sumDataBlock)) <<endl;
                cout << to_string(sumDataBlock) << endl;
                cout << to_string(cursor->keys[i].add_vect.size())<<endl;
           }
        }
        
    }
    return nullptr;
}
