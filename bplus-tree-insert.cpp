/// Insert a record into B+ tree.
#include <iostream>

#include "bplus-tree.h"
using namespace std;

void BPTree::insert(int x)
    {
        // if no root, create a new B+ tree root
        if(root==NULL)
        {
            root = new Node(maxKeys);
            root->keys[0] = x;
            root->is_leaf = true;
            root->size = 1;
        }
        // else, traverse the nodes to insert
        else
        {
            Node* cursor = root;
            Node* parent; // keep track of parent

            while(cursor->is_leaf == false) // not leaf node
            {
                parent = cursor;
                for(int i = 0; i < cursor->size; i++)
                {
                    if(x < cursor->keys[i]){ // if key you want to insert is smaller
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
                while(x > cursor->keys[i] && i < cursor->size)
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
                int virtualNode[maxKeys+1];

                // copy keys to virtualNode
                for(int i = 0; i < maxKeys; i++)
                {
                    virtualNode[i] = cursor->keys[i];
                }
                int i = 0, j;
                while(x > virtualNode[i] && i < maxKeys) i++;
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

/*    void BPTree::insertInternal(int x, Node* cursor, Node* child)
    {
        if(cursor->size < maxKeys)
        {
            //if cursor is not full
            //find the correct position for new key
            int i = 0;
            while(x > cursor->keys[i] && i < cursor->size) i++;
            //make space for new key
            for(int j = cursor->size;j > i; j--)
            {
                cursor->keys[j] = cursor->keys[j-1];
            }//make space for new pointer
            for(int j = cursor->size+1; j > i+1; j--)
            {
                cursor->ptr[j] = cursor->ptr[j-1];
            }
            cursor->keys[i] = x;
            cursor->size++;
            cursor->ptr[i+1] = child;
             cout<<"Inserted key in an Internal node successfully\n";
        }
        else
        {
            // cout<<"Inserted key in an Internal node successfully\n";
            // cout<<"Overflow in internal node!\nSplitting internal node\n";
            //if overflow in internal node
            //create new internal node
            Node* newInternal = new Node(maxKeys);
            //create virtual Internal Node;
            int virtualKey[maxKeys+1];
            Node* virtualPtr[maxKeys+2];
            for(int i = 0; i < maxKeys; i++)
            {
                virtualKey[i] = cursor->keys[i];
            }
            for(int i = 0; i < maxKeys+1; i++)
            {
                virtualPtr[i] = cursor->ptr[i];
            }
            int i = 0, j;
            while(x > virtualKey[i] && i < maxKeys) i++;
            //make space for new key
            for(int j = maxKeys+1;j > i; j--)
            {
                virtualKey[j] = virtualKey[j-1];
            }
            virtualKey[i] = x;
            //make space for new ptr
            for(int j = maxKeys+2;j > i+1; j--)
            {
                virtualPtr[j] = virtualPtr[j-1];
            }
            virtualPtr[i+1] = child;
            newInternal->is_leaf = false;
            //split cursor into two nodes
            cursor->size = (maxKeys+1)/2;
            newInternal->size = maxKeys-(maxKeys+1)/2;
            //give elements and pointers to the new node
            for(i = 0, j = cursor->size+1; i < newInternal->size; i++, j++)
            {
                newInternal->keys[i] = virtualKey[j];
            }
            for(i = 0, j = cursor->size+1; i < newInternal->size+1; i++, j++)
            {
                newInternal->ptr[i] = virtualPtr[j];
            }
            // m = cursor->key[cursor->size]
            if(cursor == root)
            {
                //if cursor is a root node, we create a new root
                Node* newRoot = new Node(maxKeys);
                newRoot->keys[0] = cursor->keys[cursor->size];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newInternal;
                newRoot->is_leaf = false;
                newRoot->size = 1;
                root = newRoot;
                //cout<<"Created new root\n";
            }
            else
            {
                //recursion
                //find depth first search to find parent of cursor
                insertInternal(cursor->keys[cursor->size] ,findParent(root,cursor) ,newInternal);
            }
        }
    }
*/
/*void BPTree::insert(int key)
{
    // if no root, create a new B+ tree root
    if(root == NULL)
    {
        root = new Node(maxKeys);
        root->keys[0] = key;
        root->is_leaf = true;
        root->size = 1;
        cout << "Root created!\n";
    }
    // else, traverse the nodes to insert
    else{
        Node *cursor = root;
        Node *parent; // keep track of parent

        while(cursor->is_leaf == false) // not leaf node
        {
            parent = cursor;
            for(int i=0; i< cursor->size; i++){
                if(key < cursor->keys[i]) // if key you want to insert is smaller
                    cursor = cursor->ptr[i];
                    break;
                if(i == cursor->size -1){ // if key larger
                    cursor = cursor->ptr[i+1];
                    break;
                }
            }
        }
        if(cursor->size < maxKeys) // if there is space in leaf node, insert key accordingly
        {
            int i = 0;
            while(key > cursor->keys[i] && i < cursor->size)
                i++;

            for(int j = cursor->size; j>i; j--){
                cursor->keys[j] = cursor->keys[j-1];
            }
            cursor -> keys[i] = key; // insert new key here
            cursor->size++;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size-1];
            cursor->ptr[cursor->size-1] = NULL;
        }
        else{ // else need to split node
            Node *newleaf = new Node(maxKeys);
            int virtualNode[maxKeys+1];

            // copy keys to virtualNode
            for(int i=0; i<maxKeys; i++){
                virtualNode[i] = cursor->keys[i];
            }
            int i=0, j;
            while(key > virtualNode[i] && i<maxKeys)
                i++;

            //insert new key
            for(int j = maxKeys + 1; j>i; j--){
                virtualNode[j] = virtualNode[j-1];
            }
            virtualNode[i] = key; // insert new key into virtualNode
            newleaf->is_leaf = true;

            // split into two leaf nodes
            cursor->size = (maxKeys+1)/2;
            newleaf->size = (maxKeys+1) - (maxKeys+1)/2;

            cursor->ptr[cursor->size] = newleaf;
            newleaf->ptr[newleaf->size] = cursor->ptr[maxKeys];
            cursor->ptr[maxKeys] = NULL;

            for(i=0; i< cursor->size; i++){
                cursor->keys[i] = virtualNode[i];
            }
            for(i=0, j=cursor->size; i< newleaf->size; i++, j++){
                newleaf->keys[i] = virtualNode[j];
            }

            //make new parent node
            if(cursor == root){
                Node *newRoot = new Node(maxKeys);
                newRoot->keys[0] = newleaf->keys[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newleaf;
                newRoot->is_leaf = false;
                newRoot->size = 1;
                root = newRoot;
            }
            else{ // insert new parent
                insertInternal(newleaf->keys[0], parent, newleaf);
            }
        }
    }
}*/

// update parent node to point at child nodes, and adds a parent if needed
void BPTree::insertInternal(int key, Node *cursor, Node *child){
    if(cursor->size < maxKeys) // if internal not full
    {
        // find position to insert key
        int i=0;
        while(key > cursor->keys[i] && i < cursor->size)
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

        // copy keys and pointers into the virtual lists
        float virtualKey[maxKeys + 1];
        Node *virtualPtr[maxKeys + 2];
        for(int i =0; i<maxKeys; i++){
            virtualKey[i] = cursor->keys[i];
        }
        for(int i =0; i<maxKeys + 1; i++){
            virtualPtr[i] = cursor->ptr[i];
        }

        // find position to insert key in virtual lists
        int i=0, j;
        while(key > virtualKey[i] && i<maxKeys)
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
            Node *newRoot = new Node(maxKeys); ///TODO maxKeys
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
