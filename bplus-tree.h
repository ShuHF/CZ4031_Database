#ifndef BPLUS-TREE_H_INCLUDED
#define BPLUS-TREE_H_INCLUDED

struct key_record{
    float value;
    vector <void*> add_vect;
};

// A node in B+ tree
class Node {
    int size;                   // current number of keys in node
    bool is_leaf;               // whether this node is a leaf node
    key_record *keys;                  // pointer to array of keys in the node
    Node** ptr;
    friend class BPTree;

public:
    Node(int maxKeys) // Constructor
    {
        keys = new key_record[maxKeys];
        ptr = new Node*[maxKeys+1];
        is_leaf = true;
    }
};

class BPTree
{
    Node *root;
    void *rootAdd;
    int lvls; // no. of levels in this B+ tree
    int numNodes = 0;
    int maxKeys = 0;
    int numTimesDeleted = 0;
    std::size_t nodeSize; // Size of a node = Size of a block.

    //MemoryPool *disk;
    //MemoryPool *index;

    // Methods
    void insertInternal(key_record key, Node *cursor, Node *child);
    void removeInternal(key_record key, Node *cursor, Node *child);
    Node *findParent(Node *, Node *);

public:
    BPTree() // Constructor
    {
        root = NULL; // initialize root to NULL
        maxKeys = (blockSize - 4) / 8;
    }
    void insert(key_record);
    Node* search(int, bool);
    void remove(key_record);
    void display(Node *, bool);
    int height(Node *);
    Node *getRoot(){
        return root;
    };

    int getmaxKeys(){
        return maxKeys;
    }
    int getnumNodes(){
        return numNodes;
    }

};


#endif // BPLUS-TREE_H_INCLUDED
