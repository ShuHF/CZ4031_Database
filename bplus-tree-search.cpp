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
                if(key < cursor->keys[i])
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
            if(cursor->keys[i] == key)
            {
                cout << "Key Found!\n";
                return cursor;
            }
        }
        return nullptr;
    }
}

void BPTree::searchRange(int lower, int upper){
    // if tree is empty
    if(root == NULL)
        cout << "B+ Tree is empty!\n";
    else{
        Node *cursor = root;

        while(cursor->is_leaf == false) // traverse till we reach a leaf node 
        {
            for(int i=0; i<cursor->size; i++)
            {
                if(lower < cursor->keys[i])
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
        bool stop = false;
        while(stop == false){
            int i;
            for(i=0; i<cursor->size; i++){
                if(cursor->keys[i] > upper)
                {
                    stop = true;
                    break;
                }
                if(cursor->keys[i] >= lower && cursor->keys[i] <= upper)
                {
                    cout << cursor->ptr[i] << endl;
                }
            }
            if(cursor->keys[i] != upper)
            {
                cursor = cursor->ptr[cursor->size]; //cursor to be next left node
            }
            else
                stop = true;
        }
    }
}
