
template<typename Key, typename Info>
void AVLTree<Key,Info> :: rotateLeft(AVLNode* &root) {    //rotation left

    if(root == nullptr) {
        cout << "Error: Element not exist!" << endl; 
        return;  
    } 

    if(root->right == nullptr) {
        cout << "Error: No right subtree!" << endl;    
        return;
    } 

    AVLNode *temp;
    temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root = temp;
}

template<typename Key, typename Info>
void AVLTree<Key,Info> :: rotateRight(AVLNode* &root) {   //rotation right

    if(root == nullptr) {
        cout << "Error: Element not exist!" << endl;
        return;
    }

    if(root->left == nullptr) {
        cout << "Error: No left subtree!" << endl; 
        return;   
    } 

    AVLNode *temp;
    temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root = temp;
}

template<typename Key, typename Info>
void AVLTree<Key,Info> :: balanceFromLeft(AVLNode* &root) {     //balance left

    AVLNode *temp;
    AVLNode *temp2;

    temp = root->left;

    switch (temp->bfactor) {

        case -1:
            root->bfactor = 0;
            temp->bfactor = 0;
            rotateRight(root);
            break;
        case 0:
            cout << "Error: Can't balance from left!" << endl;
            break;
        case 1:
            temp2 = temp->right;

            switch (temp2->bfactor) {

                case -1:
                    root->bfactor = 1;
                    temp->bfactor = 0;
                    break;
                case 0:
                    root->bfactor = 0;
                    temp->bfactor = 0;
                    break;
                case 1:
                    root->bfactor = 0;
                    temp->bfactor = -1;
                    break;
            }

            temp2->bfactor = 0;
            rotateLeft(temp);
            root->left = temp;
            rotateRight(root);
            break;
    }
}

template<typename Key, typename Info>
void AVLTree<Key,Info> :: balanceFromRight(AVLNode* &root) {    //balance right

    AVLNode *temp;
    AVLNode *temp2;

    temp = root->right;

    switch (temp->bfactor) {

        case -1:
            temp2 = temp->left;
            switch (temp2->bfactor) {

                case -1:
                    root->bfactor = 0;
                    temp->bfactor = 1;
                    break;
                case 0:
                    root->bfactor = 0;
                    temp->bfactor = 0;
                    break;
                case 1:
                    root->bfactor = -1;
                    temp->bfactor = 0;
                    break;
            }

            temp2->bfactor = 0;
            rotateRight(temp);
            root->right = temp;
            rotateLeft(root);
            break;
        case 0:
            cout << "Error: Can't balance from right!" << endl;
            break;
        case 1:
            root->bfactor = 0;
            temp->bfactor = 0;
            rotateLeft(root);
            break;
    }
}

template<typename Key, typename Info>
void AVLTree<Key,Info> :: insertIntoAVL(AVLNode* &root, AVLNode *newNode, bool& isTaller, bool& countRepeats) {     //adding node to tree
    
    if(root == nullptr) {
        root = newNode;
        isTaller = false;
        return;
    }

    if(root->nodeKey == newNode->nodeKey) {     //if already exist
        if(countRepeats) {
            count++; 
            root->nodeInfo = root->nodeInfo + 1;
        } 
        return;
    }
    
    if(newNode->nodeKey < root->nodeKey) {
        insertIntoAVL(root->left, newNode, isTaller, countRepeats);

        if(isTaller)
        switch (root->bfactor)
        {
            case -1:
                balanceFromLeft(root);
                isTaller = false;
                break;
            case 0:
                root->bfactor = -1;
                isTaller = true;
                break;
            case 1:
                root->bfactor = 0;
                isTaller = false;
                break;
        }
    }
    else {
        insertIntoAVL(root->right, newNode, isTaller, countRepeats);

        if(isTaller)
        switch (root->bfactor) {
            case -1:
                root->bfactor = 0;
                isTaller = false;
                break;
            case 0:
                root->bfactor = 1;
                isTaller = true;
                break;
            case 1:
                balanceFromRight(root);
                isTaller = false;
                break;
        }
    }
}

template<typename Key, typename Info>
void AVLTree<Key,Info> :: insert(const Key &k, const Info &i) {     //adding node to tree

    bool isTaller = false;
    AVLNode *newNode = new AVLNode;

    newNode->nodeKey = k;
    newNode->nodeInfo = i;
    newNode->bfactor = 0;
    newNode->left = nullptr;
    newNode->right = nullptr;
    bool countRepeats = false;

    insertIntoAVL(root, newNode, isTaller, countRepeats);
}

template<typename Key, typename Info>
void AVLTree<Key,Info> :: destroy(AVLNode* &temp) {     //delete part of tree
    if(temp == nullptr) return;

    destroy(temp->left);
    destroy(temp->right);
    delete temp;
    temp = nullptr;
}

template<typename Key, typename Info>       
void AVLTree<Key,Info> :: printRecurection(AVLNode *temp) {     //recurection function for printing
    if(temp == nullptr) return;

    printRecurection(temp->left); 
    cout << temp->nodeKey << " " << temp->nodeInfo << endl;    
    printRecurection(temp->right);
}

template<typename Key, typename Info>  
void AVLTree<Key,Info> :: copyTree(AVLNode* &copiedRoot, AVLNode* otherRoot) {      //copying tree
    
    if(otherRoot == nullptr) copiedRoot = nullptr;

    else {
    copiedRoot = new AVLNode;
    copiedRoot->nodeInfo = otherRoot->nodeInfo;
    copiedRoot->nodeKey = otherRoot->nodeKey;

    copyTree(copiedRoot->left, otherRoot->left);
    copyTree(copiedRoot->right, otherRoot->right);
    }
}

template<typename Key, typename Info>
AVLTree<Key, Info> :: AVLTree(const AVLTree<Key, Info>& t) {    //copy constructor

    if (t.root == nullptr) {
        root = nullptr;
        return;
    }
    
    copyTree(root, t.root);
}

template<typename Key, typename Info>
const AVLTree<Key, Info>& AVLTree<Key, Info> :: operator=(const AVLTree<Key, Info>& t) {    //assignment operator

    if(this != &t) {
        if (root != nullptr) destroy(root);
        if (t.root == nullptr) root = nullptr;
        else copyTree(root, t.root);
    }
    
    return *this;
}

template<typename Key, typename Info>
int AVLTree<Key,Info> :: heightRecurection(AVLNode *temp) const {   //height of tree

    if (temp == nullptr) return 0;
    else
    return 1 + max(heightRecurection(temp->left), heightRecurection(temp->right));
}

template<typename Key, typename Info>
void AVLTree<Key,Info> :: print2DRecurection(AVLNode* temp, int spacebetween) {    //printing tree in 2D recurection

    if(temp != nullptr){

        if(temp->right) print2DRecurection(temp->right, spacebetween+4);
        if(spacebetween) cout << setw(spacebetween) << ' ';

        if(temp->right) cout<<" /\n" << setw(spacebetween) << ' ';
        cout<< temp->nodeKey << ":" << temp->nodeInfo << endl;

        if(temp->left) {
            cout << setw(spacebetween) << ' ' <<" \\\n";
            print2DRecurection(temp->left, spacebetween+4);
        }
    }
}

template<typename Key, typename Info>
bool AVLTree<Key,Info> :: search(const Key& k, const Info& i) const {   //searching tree for node with such key&info

   AVLNode *temp;
   bool exist = false;

   if(root == nullptr) {
       cout << "Error: Empty tree!" << endl;
       return false;
   }
   
   temp = root;
   while (temp != nullptr && !exist) {
        if (temp->nodeInfo == i && temp->nodeKey == k) exist = true;
        else if (temp->nodeKey > k) temp = temp->left;
        else temp = temp->right;
   }

   return exist;
}

template<typename Key, typename Info>
void AVLTree<Key,Info> :: inorder(AVLNode *temp, ofstream& file) {    //printing to txt in ascending order
    if(temp != nullptr) {
        inorder(temp->left, file);
        file << temp->nodeKey << ":" << temp->nodeInfo <<endl; 
        inorder(temp->right, file);
    }
}

template<typename Key, typename Info>
void AVLTree<Key,Info> :: backorder(AVLNode *temp, ofstream& file) {    //printing to txt in descending order 
    if(temp != nullptr) {
        backorder(temp->right, file);
        file << temp->nodeKey << ":" << temp->nodeInfo <<endl;
        backorder(temp->left, file);
    }
}

template<typename Key, typename Info>
void AVLTree<Key,Info> :: printStream(ofstream& file, bool ascending) {     //printing tree into txt

    if(!file.is_open()) {
        cout << "Error: File not loaded!" << endl;
        return;
    }

    if(ascending == true)inorder(root, file);
    else backorder(root, file);
}

template<typename Key, typename Info>
void AVLTree<Key,Info> :: howMany(AVLNode *temp) {    //how many nodes in tree
    if(temp != nullptr) {
        howMany(temp->left);
        count++; 
        howMany(temp->right);
    }
}

template<typename Key, typename Info>
void AVLTree<Key,Info> :: insertForCounter(const Key &k, const Info &i) {     //adding node & with repeats 

    bool isTaller = false;
    AVLNode *newNode = new AVLNode;

    newNode->nodeKey = k;
    newNode->nodeInfo = i;
    newNode->bfactor = 0;
    newNode->left = nullptr;
    newNode->right = nullptr;
    bool countRepeats = true;

    insertIntoAVL(root, newNode, isTaller, countRepeats);
}