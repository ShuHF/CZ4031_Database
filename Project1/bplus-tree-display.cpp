/// display tree
#include <iostream>

#include "bplus-tree.h"
using namespace std;

void BPTree::display(Node *cursor, bool fullTree){
    // print root node and its first child nodes
    if(fullTree == false){
        for (int i = 0;i<cursor->size+1 ; i++){
                if (i!=cursor->size) {
                    cout << "Root:" << " " << cursor->keys[i].value << "\n";
                }
                //cout << 1 << "\n";
                for (int j = 0; j<cursor->ptr[i]->size; j++){
                    cout << cursor->ptr[i]->keys[j].value << " ";
                }
                cout << "\n";
            }
    }
    // else, print whole tree
    else{
        //check if cursor is not null, print out the value of the key.
        if(cursor!=NULL){
            for(int i=0; i<cursor->size;i++){
                cout <<cursor->keys[i].value<<" ";
            }
            cout<<"/n";
            if(cursor->is_leaf!=true){ //not leaf
                for(int i=0;i<cursor->size+1;i++){
                    display(cursor->ptr[i], true);
                }
            }
        }
        else{
            cout << "No Tree";
        }
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
            return 0;
        }
}
