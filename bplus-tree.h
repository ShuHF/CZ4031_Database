#ifndef BPLUS-TREE_H_INCLUDED
#define BPLUS-TREE_H_INCLUDED

// A node in B+ tree
class Node {
    int size; // current number of keys in node
    bool is_leaf; // whether this node is a leaf node
    float *keys; // pointer to array of keys in the node
    Node** ptr;
    friend class BPTree;

public:
    Node(int maxKeys)
    {
        keys = new float[maxKeys];
        ptr = new Node*[maxKeys+1];
        is_leaf = true;
    }
};

//Node::Node(int maxKeys)
//{
//    keys = new float[maxKeys];
//    ptr = new Node*[maxKeys+1];
//    is_leaf = true;
//}

class BPTree
{
    Node *root;
    void *rootAdd;
    int lvls; // no. of levels in this B+ tree
    int numNodes;
    int maxKeys = 3;
    std::size_t nodeSize; // Size of a node = Size of a block.

    //MemoryPool *disk;
    //MemoryPool *index;

    // Methods
    void insertInternal(int key, Node *cursor, Node *child);
    void removeInternal(int key, Node *cursor, Node *child);
    Node *findParent(Node *, Node *);

public:
    BPTree()
    {
        root = NULL; // initialize root to NULL
    }
    void insert(int);
    void search(int);
    void remove(int);
    void display(Node *);
    int height(Node *);

    Node *getRoot(){
        return root;
    };

};


#endif // BPLUS-TREE_H_INCLUDED
