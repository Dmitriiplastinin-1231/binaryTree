#include <iostream>
#include <vector>

using namespace std;

class Node
{
    Node* left = nullptr;
    Node* right = nullptr;
    
    public:
    
    int key;
    int value;
    Node(int key, int value){this->key = key; this->value = value;};
    

    template <class T>
    T* insert(T* node, int key, int value){
        if (key < node->key)
        {
            if (node->left == nullptr) node->left = new T(key, value);
            else node->insert(node->left, key, value);
        } else if (key >= node->key)
        {
            if (node->right == nullptr) node->right = new T(key, value);
            else node->insert(node->right, key, value);
        } 
        return nullptr;
    }
    
    template <typename T>
    T* search(T* node, int key)
    {
        if (node == nullptr) return nullptr;
        if (node->key == key) return node;
        return (key < node->key)? search(node->left, key): search(node->right, key);
    }

    template <typename T>
    T* getMin(T* node)
    {
        return (node->left != nullptr)? getMin(node->left): node;
    }

    template <typename T>
    T* getMax(T* node)
    {
        return (node->right != nullptr)? getMin(node->right): node;
    }

    template <typename T>
    T* del (T* node, int key)
    {
        if (&node == nullptr) return nullptr;
        else if (key < node->key) node->left = del(node->left, key);
        else if (key > node->key) node->right = del(node->right, key);
        else{
            if (node->left == nullptr || node->right == nullptr)
            {            
                if (node->left == nullptr && node->right == nullptr) return nullptr;
                return (node->left == nullptr)? node->right: node->left;
            } else{
                auto* maxInLeft = getMax(node->left);
                node->key = maxInLeft->key;
                node->value = maxInLeft->value;
                node->left =  del(node->left, maxInLeft->key);
            }

        }
        return node;
    }

    template <typename T>
    void printTree(T* node)
    {
        if (node == nullptr) return;
        printTree(node->left);
        cout << node->value << endl;
        printTree(node->right);
    }
    
    template <typename T>
    void printTreeFirstChild(T* node)
    {
        if (node == nullptr) return;
        printTreeFirstChild(node->left);
        printTreeFirstChild(node->right);
        cout << node->value << endl;
    }

    template <typename T>
    void copyPrint (T* node)
    {
        if (node == nullptr) return;
        cout << node->value << endl;
        copyPrint(node->left);
        copyPrint(node->right);
    }
};

class AVLNode : public Node
{
    private:

    public:
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;

    AVLNode(int key, int value):Node(key, value){}
    int height = 0;

    int getHeight(AVLNode* node)
    {
        return node == nullptr? -1: node->height;
    }

    void updateHeight (AVLNode* node)
    {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    int getBalance(AVLNode* node)
    {
        return (node) ? getHeight(node->right) - getHeight(node->left) : 0;
    }

    void swap (AVLNode& a, AVLNode& b)
    {   
        if (!&a || !&b) return;
        int a_key = a.key;
        int a_value = a.value;
        a.key = b.key;
        a.value = b.value;
        b.key = a_key;
        b.value = a_value;
    }

    void rightRotate(AVLNode* node){
        swap(*node, *node->left);
        AVLNode* buffer = node->right;
        node->right = node->left;
        node->left = node->right->left;
        node->right->left = node->right->right;
        node->right->right = buffer;
        updateHeight(node->right);
        updateHeight(node);
    }

    void leftRotate(AVLNode* node){
        swap(*node, *node->right);
        AVLNode* buffer = node->left;
        node->left = node->right;
        node->right = node->left->right;
        node->left->right = node->left->left;
        node->left->left = buffer;
        updateHeight(node->left);
        updateHeight(node);
    }

    void balance(AVLNode* node)
    {
        int balance = getBalance(node);
        if (balance == -2)
        {
            if (getBalance(node->left) == 1)leftRotate(node->left);
            rightRotate(node);
        }
        else if (balance == 2)
        {
            if (getBalance(node->right) == -1)rightRotate(node->right);
            leftRotate(node);
        }
    }

    void insert(AVLNode* node, int key, int value)
    {
        Node::insert(node, key, value);
        updateHeight(node);
        balance(node);
    }
};

int main()
{

    AVLNode node = AVLNode(3, 3);
    node.insert(&node, 4, 4);
    node.insert(&node, 1, 1);
    node.insert(&node, 2, 2);
    node.insert(&node, 7, 7);
    node.insert(&node, 8, 8);
    node.insert(&node, 5, 5);

    
    cout << node.search(&node, 1) << endl;

    return 0;
}