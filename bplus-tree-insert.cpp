/// Insert a record into B+ tree.
#include <iostream>

#include "bplus-tree.h"
using namespace std;

void BPTree::insert(key_record x)
    {
        // if no root, create a new B+ tree root
        if(root==NULL)
        {
            root = new Node(maxKeys);
            root->keys[0] = x;
            root->is_leaf = true;
            root->size = 1;
            numNodes++;
        }
        // else, traverse the nodes to insert
        else
        {
            Node* cursor = root;
            Node* parent; // keep track of parent

            // search for same numVotes value and if same push back to add_vect
            Node* searchRes;
            searchRes = search(x.value, false, false, 0);
            if ( searchRes != nullptr){
                for(int i = 0; i < searchRes->size; i++)
                {
                    if(searchRes->keys[i].value == x.value)
                    {
                        searchRes->keys[i].add_vect.push_back(x.add_vect[0]);
                        break;
                    }
                }
                return;
            }

            while(cursor->is_leaf == false) // not leaf node
            {
                parent = cursor;
                for(int i = 0; i < cursor->size; i++)
                {
                    if(x.value < cursor->keys[i].value){ // if key you want to insert is smaller
                        cursor = cursor->ptr[i];
                        break;
                    }
                    if(i == cursor->size - 1){ // if key larger
                        cursor = cursor->ptr[i+1];
                        break;
                    }
                }
            }

            if(cursor->size < maxKeys) // if there is space in leaf node, insert key accordingly
            {
                int i = 0;
                while(x.value > cursor->keys[i].value && i < cursor->size)
                    i++;
                for(int j = cursor->size;j > i; j--){
                    cursor->keys[j] = cursor->keys[j-1];
                }

                cursor->keys[i] = x; // insert new key here
                cursor->size++;
                cursor->ptr[cursor->size] = cursor->ptr[cursor->size-1];
                cursor->ptr[cursor->size-1] = NULL;
            }

            else // else need to split nodes
            {
                Node* newLeaf = new Node(maxKeys);
                numNodes++;
                key_record virtualNode[maxKeys+1];

                // copy keys to virtualNode
                for(int i = 0; i < maxKeys; i++)
                {
                    virtualNode[i] = cursor->keys[i];
                }
                int i = 0, j;
                while(x.value > virtualNode[i].value && i < maxKeys) i++;
                for(int j = maxKeys+1;j > i; j--)
                {
                    virtualNode[j] = virtualNode[j-1];
                }
                virtualNode[i] = x; // insert key into virtualNode
                newLeaf->is_leaf = true;

                //split the cursor into two leaf nodes
                cursor->size = (maxKeys+1)/2;
                newLeaf->size = maxKeys+1-(maxKeys+1)/2;

                cursor->ptr[cursor->size] = newLeaf;
                newLeaf->ptr[newLeaf->size] = cursor->ptr[maxKeys];
                cursor->ptr[maxKeys] = NULL;

                for(i = 0; i < cursor->size; i++){
                    cursor->keys[i] = virtualNode[i];
                }
                for(i = 0, j = cursor->size; i < newLeaf->size; i++, j++){
                    newLeaf->keys[i] = virtualNode[j];
                }

                // create new root if cursor is root
                if(cursor == root)
                {
                    Node* newRoot = new Node(maxKeys);
                    numNodes++;
                    newRoot->keys[0] = newLeaf->keys[0];
                    newRoot->ptr[0] = cursor;
                    newRoot->ptr[1] = newLeaf;
                    newRoot->is_leaf = false;
                    newRoot->size = 1;
                    root = newRoot;
                }
                else
                {
                    insertInternal(newLeaf->keys[0],parent,newLeaf); // insert new parent
                }
            }
        }
    }


// update parent node to point at child nodes, and adds a parent if needed
void BPTree::insertInternal(key_record key, Node *cursor, Node *child){
    if(cursor->size < maxKeys) // if internal not full
    {
        // find position to insert key
        int i=0;
        while(key.value > cursor->keys[i].value && i < cursor->size)
            i++;

        // insert accordingly
        for(int j = cursor->size; j>i; j--){
            cursor->keys[j] = cursor->keys[j-1];
        }
        for(int j = cursor->size + 1; j>i; j--){
            cursor->ptr[j] = cursor->ptr[j-1];
        }
        cursor->keys[i] = key;
        cursor->size++;
        cursor->ptr[i+1] = child;
    }
    else{ // if full, split internal node and create new internal node
        Node *newInt = new Node(maxKeys);
        numNodes++;

        // copy keys and pointers into the virtual lists
        key_record virtualKey[maxKeys + 1];
        Node *virtualPtr[maxKeys + 2];
        for(int i =0; i<maxKeys; i++){
            virtualKey[i] = cursor->keys[i];
        }
        for(int i =0; i<maxKeys + 1; i++){
            virtualPtr[i] = cursor->ptr[i];
        }

        // find position to insert key in virtual lists
        int i=0, j;
        while(key.value > virtualKey[i].value && i<maxKeys)
            i++;

        for(int j = maxKeys+1; j>i; j--){
            virtualKey[j] = virtualKey[j-1];
        }
        virtualKey[i] = key;
        for(int j = maxKeys+2; j>i; j--){
            virtualPtr[j] = virtualPtr[j-1];
        }
        virtualPtr[i+1] = child;
        newInt->is_leaf = false; // set as false since internal node cannot be leaf node

        // split into two nodes
        cursor->size = (maxKeys+1) / 2;
        newInt->size = maxKeys - (maxKeys+1) / 2;

        // insert keys & pointers to new internal node
        for(i=0, j = cursor->size+1; i < newInt->size; i++, j++){
            newInt->keys[i] = virtualKey[j];
        }
        for(i=0, j = cursor->size+1; i < newInt->size+1; i++, j++){
            newInt->ptr[i] = virtualPtr[j];
        }

        // if current cursor = root, create a new root
        if(cursor == root){
            Node *newRoot = new Node(maxKeys); 
            numNodes++;
            newRoot->keys[0] = cursor->keys[cursor->size];
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInt;
            newRoot->is_leaf = false;
            newRoot->size = 1;
            root = newRoot;
        }
        else{ // split and make new internal node recursively
            insertInternal(cursor->keys[cursor->size], findParent(root, cursor), newInt);
        }
    }
}

// find parent node
Node *BPTree::findParent(Node *cursor, Node *child){
    Node *parent;

    if(cursor->is_leaf || (cursor->ptr[0])->is_leaf) // node is not internal/parent node
        return NULL;
    for(int i=0; i < cursor->size+1; i++){ //traverse through the nodes
        if(cursor->ptr[i] == child)
        {
            parent = cursor;
            return parent;
        }
        else
        {
            parent = findParent(cursor->ptr[i], child);
            if(parent != NULL)
                return parent;
        }
    }
    return parent;
}
