#ifndef AVLTREE_H
#define AVLTREE_H

#include <algorithm>
#include <iomanip>

using namespace std;

template<typename Key, typename Info>
class AVLTree { 

    private:

    struct AVLNode {
        
        Key nodeKey;
        Info nodeInfo;
        int bfactor;
        AVLNode *left;
        AVLNode *right;
    };

    AVLNode* root;
    int count;

    void rotateLeft(AVLNode* &root);
    void rotateRight(AVLNode* &root);
    void balanceFromLeft(AVLNode* &root);
    void balanceFromRight(AVLNode* &root);
    void insertIntoAVL(AVLNode* &root, AVLNode *newNode, bool& isTaller, bool& countRepeats);   //if countRepeats true count copies, if false NOT count

    void destroy(AVLNode* &temp);
    void printRecurection(AVLNode *temp);
    void print2DRecurection(AVLNode* temp, int spacebetween = 0);
    void howMany(AVLNode* temp);

    void inorder(AVLNode *temp, ofstream& file);
    void backorder(AVLNode *temp, ofstream& file);

    public:

    AVLTree() { root = nullptr; count = 0; }
    AVLTree(const AVLTree<Key, Info>& t);
    ~AVLTree() { destroy(root); }

    void insert(const Key &k, const Info &i);
    void insertForCounter(const Key &k, const Info &i);     //insert node to tree & count repetatives
    
    void destroyTree() { destroy(root); }   //delete whole tree
    void print() { printRecurection(root); }    //print tree
    
    void copyTree(AVLNode* &copiedRoot, AVLNode* otherRoot);
    const AVLTree &operator =(const AVLTree<Key, Info> &t);

    int heightRecurection(AVLNode *temp) const;
    int height() { return heightRecurection(root); }
    int length() { howMany(root); return count; }
    void print2D() { print2DRecurection(root); }
    bool search(const Key& k, const Info& i) const;
    
    void printStream(ofstream& file, bool ascending);
      
};

#include "avltree.hpp"

#endif