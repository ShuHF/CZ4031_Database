// Search keys in a B+ tree
#include <iostream>

#include "bplus-tree.h"
using namespace std;

Node* BPTree::search(int key){
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
        for(int i=0; i< cursor->size; i++){
            if(cursor->keys[i].value == key)
            {
                cout << to_string(cursor->keys[i].value) +  " Found!\n";

                /*cout <<"Size: "<< cursor->keys[i].add_vect.size() << "\n";
                printf("No. of Data Blocks: %d", cursor->keys[i].add_vect.size());
                printf("\n");

                for (int j = 0; j < cursor->keys[i].add_vect.size(); ++j) {
                            printf("Data Block: ");
                            printf("%p", (char *) cursor->keys[i].add_vect[j]);
                            printf("\n");
                            printf("Movie Name: ");
                            cout << (*(movieRatingReview *) cursor->keys[i].add_vect[j]).movieName << "\n";
                        }*/

                return cursor;
            }
        }
        
    }
    return nullptr;
}
