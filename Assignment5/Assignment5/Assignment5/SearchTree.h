#pragma once
#include <algorithm>
#include <iostream>

using namespace std;

template <typename T> 
class TreeNode {
private:
    T value;
public:
    T key;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(T k, T v) {
        key = k;
        value = v;
        left = nullptr;
        right = nullptr;
        height = 1;
    }

    T getValue() {
        return value;
    }
};

template <typename T> class SearchTree {
private:
    TreeNode<T>* root;

    int height(TreeNode<T>* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int balanceFactor(TreeNode<T>* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    TreeNode<T>* rightRotate(TreeNode<T>* y) {
        TreeNode<T>* x = y->left;
        TreeNode<T>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height
            = max(height(y->left), height(y->right)) + 1;
        x->height
            = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    TreeNode<T>* leftRotate(TreeNode<T>* x) {
        TreeNode<T>* y = x->right;
        TreeNode<T>* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height
            = max(height(x->left), height(x->right)) + 1;
        y->height
            = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    TreeNode<T>* insertNode(TreeNode<T>* node, T key, T value) {
        if (node == nullptr)
            return new TreeNode<T>(key, value);

        if (key < node->key)
            node->left = insertNode(node->left, key, value);
        else if (key > node->key)
            node->right = insertNode(node->right, key, value);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
    TreeNode<T>* minValueNode(TreeNode<T>* node) {
        TreeNode<T>* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    TreeNode<T>* deleteNode(TreeNode<T>* root, T key) {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if ((root->left == nullptr)
                || (root->right == nullptr)) {
                TreeNode<T>* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else {

                TreeNode<T>* temp
                    = minValueNode(root->right);
                root->key = temp->key;
                root->right
                    = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = balanceFactor(root);

        if (balance > 1 && balanceFactor(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && balanceFactor(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1
            && balanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void inorder(TreeNode<T>* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << "(" << root->key << ", " << root->getValue() << ")" << " " << "  |  " << "Height: " << height(root) << endl;
            inorder(root->right);
        }
    }

    bool search(TreeNode<T>* root, T key){
        if (root == nullptr)
            return false;
        if (root->key == key)
            return true;
        if (key < root->key)
            return search(root->left, key);
        return search(root->right, key);
    }

    TreeNode<T>* findNode(TreeNode<T>* root, T key) {
        if (root == nullptr)
            return nullptr;
        if (root->key == key)
            return root;
        if (key < root->key)
            return findNode(root->left, key);
        return findNode(root->right, key);
    }

public:
    SearchTree()
        : root(nullptr)
    {
    }

    void insert(T key, T value) { 
        root = insertNode(root, key, value);
        printInorder();
    }

    void remove(T key) { 
        cout << "Removing key: " << key << endl;
        root = deleteNode(root, key); 
        printInorder();
    }

    bool search(T key) { 
        return search(root, key); 
    }

    int findHeight(T key) {
        TreeNode<T>* node = findNode(root, key);
        return height(node);
    }

    void printInorder(){
        inorder(root);
        cout << endl;
    }
};