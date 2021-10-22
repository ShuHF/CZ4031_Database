/// Remove a record from B+ tree.
#include <iostream>

#include "bplus-tree.h"
using namespace std;

void BPTree::remove(key_record x) {
    if (root == NULL) { //root is empty
        cout << "The tree is empty";
    }
    else {
        Node *cursor = root;
        Node *parent;
        int left, right;
        while (cursor->is_leaf == false) { //not leaf node
            for (int i=0; i<cursor->size; i++) {
                parent = cursor;
                left = i-1;
                right = i+1;
                if (x.value<cursor->keys[i].value) { //remove value less than key value
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i==cursor->size-1) { 
                    left=i;
                    right=i+2;
                    cursor = cursor->ptr[i+1];
                break;
                }
            }
        }
        bool found = false;
        int position;
        for (position = 0; position < cursor->size; position++) {
            if (cursor->keys[position].value == x.value) { //get x position if found update to true
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Not found\n";
            return;
        }
        for (int i = position; i < cursor->size; i++) {
            cursor->keys[i] = cursor->keys[i + 1]; //update current key to next value
        }
        cursor->size--; //decrease cursor size
        if (cursor == root) { //when tree left with root node
            for (int i=0; i<maxKeys+1; i++) {
                cursor->ptr[i] = NULL; //update pointer to  null
            }
            if (cursor->size == 0) { //no more nodes in tree, tree is empty
                cout << "Tree died\n";
                delete[] cursor->keys;
                delete[] cursor->ptr;
                delete cursor;
                root = NULL;
            }
            return;
        }
        cursor->ptr[cursor->size] = cursor->ptr[cursor->size + 1]; //set current ptr value to last node
        cursor->ptr[cursor->size + 1] = NULL; //remove last node
        if (cursor->size >= (maxKeys + 1) / 2) { 
            return;
        }
        if (left >= 0) {
            Node *leftNode = parent->ptr[left]; //get left node
            if (leftNode->size >= (maxKeys + 1) / 2 + 1) { 
                for (int i = cursor->size; i > 0; i--) {
                    cursor->keys[i] = cursor->keys[i - 1];
                }
                cursor->size++; //ptr to next leaf
                cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
                cursor->ptr[cursor->size - 1] = NULL;
                cursor->keys[0] = leftNode->keys[leftNode->size - 1]; //transfer leaf
                leftNode->size--; //ptr to left sibling
                leftNode->ptr[leftNode->size] = cursor;
                leftNode->ptr[leftNode->size + 1] = NULL;
                parent->keys[left] = cursor->keys[0]; 
                return;
            }
        }
        if(right<= parent->size) {
            Node *rightNode = parent->ptr[right]; //get right node
            if(rightNode->size >= (maxKeys + 1) / 2 + 1) { 
                cursor->size++; //ptr to next leaf
                cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
                cursor->ptr[cursor->size-1] = NULL;
                cursor->keys[cursor->size-1] = rightNode->keys[0];
                rightNode->size--; //ptr to right sibling
                rightNode->ptr[rightNode->size] = rightNode->ptr[rightNode->size + 1];
                rightNode->ptr[rightNode->size + 1] = NULL;
                for (int i = 0; i < rightNode->size; i++) {
                    rightNode->keys[i] = rightNode->keys[i + 1];
                }
                parent->keys[right-1] = rightNode->keys[0];
                return;
            }
        }
        if (left>=0) {
            Node *leftNode = parent->ptr[left];
            for (int i = leftNode->size, j = 0; j < cursor->size; i++, j++) {
                leftNode->keys[i] = cursor->keys[j]; //move all keys to left sibling
            }
            leftNode->ptr[leftNode->size] = NULL;
            leftNode->size+=cursor->size;
            leftNode->ptr[leftNode->size] = cursor->ptr[cursor->size];
            removeInternal(parent->keys[left], parent, cursor); //remove parent node key
            delete[] cursor->keys;
            delete[] cursor->ptr;
            delete cursor;
        }
        else if (right<= parent->size) {
            Node *rightNode = parent->ptr[right];
            for (int i = cursor->size, j = 0; j < rightNode->size; i++, j++) {
                cursor->keys[i] = rightNode->keys[j];
            }
            cursor->ptr[cursor->size] = NULL;
            cursor->size += rightNode->size;
            cursor->ptr[cursor->size] = rightNode->ptr[rightNode->size];
            cout << "Merging two leaf nodes\n";
            numNodes--;
            numTimesDeleted++;
            removeInternal(parent->keys[right - 1], parent, rightNode);
            delete[] rightNode->keys;
            delete[] rightNode->ptr;
            delete rightNode;
        }
    }
}

void BPTree::removeInternal(key_record key, Node *cursor, Node *child){
    if(cursor == root){
        if(cursor -> size == 1){ //only left with 1 key
            if(cursor->ptr[1]==child){
                delete[] child->keys;
                delete[] child->ptr;
                delete child;
                root = cursor->ptr[0];
                delete[] cursor->keys;
                delete[] cursor->ptr;
                delete cursor;
                return;
            }
            else if(cursor->ptr[0]==child){
                delete[] child->keys;
                delete[] child->ptr;
                delete child;
                root = cursor->ptr[1];
                delete[] cursor->keys;
                delete[] cursor->ptr;
                delete cursor;
                return;
            }
        }
    }
    //get position of key x
    int position;
    for(position=0;position<cursor->size; position++){
        if(cursor->keys[position].value==key.value){
            break;
        }
    }
    //loop through the tree starting from the position of key x
    for(int i=position; i<cursor->size;i++){
        cursor->keys[i]=cursor->keys[i+1];//move keys forward
    }
    //get position of child of key
    for(position = 0;position<cursor->size+1; position++){
        if(cursor->ptr[position]==child){
            break;
        }
    }
    for(int i=position;i<cursor->size+1;i++){
        cursor->ptr[i]=cursor->ptr[i+1];
    }
    cursor->size--; //reduce cursor size
    if (cursor->size>=(maxKeys+1)/2-1){
        return;
    }
    if (cursor==root){
        return;
    }
    //get the parent node of the current node
    Node *parent = findParent(root, cursor);
    int left, right;
    //find the left and right sibling of the node
    for(position=0; position<parent->size+1; position++) {
        if (parent->ptr[position]==cursor) {
            left=position-1;
            right=position+1;
            break;
        }
    }
    if(left>=0){ //there is left sibling
        Node *leftNode=parent->ptr[left];
        if(leftNode->size>=(maxKeys+1)/2){ // check if there is space to transfer
            for(int i=cursor->size; i>0; i--){
                cursor->keys[i] = cursor->keys[i-1];
            }
            cursor->keys[0]=parent->keys[left];//move key from right sibling via parent
            parent->keys[left] = leftNode->keys[leftNode->size-1];
            for (int i=cursor->size+1; i>0; i--) {
                cursor->ptr[i] = cursor->ptr[i-1];
            }
            cursor->ptr[0] = leftNode->ptr[leftNode->size];
            cursor->size++;
            leftNode->size--;
            return;
        }
    }
    if (right<=parent->size) { //check for right sibling
        Node *rightNode=parent->ptr[right];
        if (rightNode->size >= (maxKeys + 1) / 2) { // check if there is space to transfer
            cursor->keys[cursor->size] = parent->keys[position]; //move key from right sibling via parent
            parent->keys[position] = rightNode->keys[0];
            for (int i = 0; i < rightNode->size - 1; i++) {
                rightNode->keys[i] = rightNode->keys[i + 1];
            }
            cursor->ptr[cursor->size + 1] = rightNode->ptr[0]; //move first ptr to cursor
            for (int i = 0; i < rightNode->size; ++i) {
                rightNode->ptr[i] = rightNode->ptr[i + 1];
            }
            cursor->size++;
            rightNode->size--;
            return;
        }
    }
    if (left>=0) { //merging if cannot transfer
        Node *leftNode = parent->ptr[left];
        leftNode->keys[leftNode->size] = parent->keys[left];
        for (int i = leftNode->size + 1, j = 0; j < cursor->size; j++) {
            leftNode->keys[i] = cursor->keys[j];
        }
        for (int i = leftNode->size + 1, j = 0; j < cursor->size + 1; j++) {
            leftNode->ptr[i] = cursor->ptr[j];
            cursor->ptr[j] = NULL;
        }
        leftNode->size += cursor->size + 1;
        cursor->size = 0;
        removeInternal(parent->keys[left], parent, cursor);
    }
    else if (right<=parent->size) {
        Node *rightNode = parent->ptr[right];
        cursor->keys[cursor->size] = parent->keys[right-1];
        for (int i=cursor->size+1, j=0; j<rightNode->size; j++) {
            cursor->keys[i] = rightNode->keys[j];
        }
        for (int i = cursor->size + 1, j = 0; j < rightNode->size + 1; j++) {
            cursor->ptr[i] = rightNode->ptr[j];
            rightNode->ptr[j] = NULL;
        }
        cursor->size += rightNode->size + 1;
        rightNode->size = 0;
        removeInternal(parent->keys[right-1], parent, rightNode);
    }
}
