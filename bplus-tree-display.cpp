/// display tree
#include <iostream>

#include "bplus-tree.h"
using namespace std;

void BPTree::display(Node *cursor){
    //check if cursor is not null, print out the value of the key.
    if(cursor!=NULL){
        for(int i=0; i<cursor->size;i++){
            cout <<cursor->keys[i]<<" ";
        }
        numNodes++;
        cout<<"/n";
        if(cursor->is_leaf!=true){ //not leaf
            for(int i=0;i<cursor->size+1;i++){
                display(cursor->ptr[i]);
            }
        }
    }
    else{
        cout << "No Tree";
    }
}

int BPTree::height(Node *cursor){
        if(cursor->is_leaf==false){
            return height(cursor->ptr[0])+1;
        }
        else if(cursor->is_leaf==true){
            return 1;
        }
        else{
            return NULL;
        }
}
