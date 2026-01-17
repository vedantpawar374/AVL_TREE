// AVL_TREE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <cstddef>
#include<algorithm>
using namespace std;

class Node
{
public:
    int  data;
    Node* left;
    Node* right;
    Node(int x)
    {
        this->data = x;
        left = NULL;
        right = NULL;
    }
    Node()
    {
        left = NULL;
        right = NULL;
    }
};

class AVLTree
{
    Node* root;
public:
    AVLTree()
    {
        root = NULL;
    }
    void showRec()
    {
        inorderRec(root);
    }
    void inorderRec(Node* root)
    {
        if (root == NULL)
        {
            return;
        }
        inorderRec(root->left);
        cout << "   " << root->data;
        inorderRec(root->right);
    }
    int heightRec(Node* root)
    {
        if (root == NULL)
        {
            return 0;
        }
        return 1 + max(heightRec(root->left), heightRec(root->right));
    }
    int balFactor(Node* t)
    {
        if (t == NULL) return 0;
        return heightRec(t->left) - heightRec(t->right);
    }
    Node* rotateRight(Node* t)
    {
        if (t->left == NULL)
        {
            cout << "t->left is null";
            return t;
        }
        Node* p = t->left;
        t->left = p->right;
        p->right = t;
        return p;
    }
    Node* rotateLeft(Node* t)
    {
        if (t->right == NULL)
        {
            cout << "t->right is null";
            return t;
        }
        Node* p = t->right;
        t->right = p->left;
        p->left = t;
        return p;
    }
    Node* rotateLeftRight(Node* t)
    {
        if (t->left == NULL)
        {
            cout << "t->left is null";
            return t;
       }
        t->left = rotateLeft(t->left);
        t = rotateRight(t);
        return t;
    }
    Node* rotateRightLeft(Node* t)
    {
        if (t->right == NULL)
        {
            cout << "\nT->right is null";
            return t;
        }
        t->right = rotateRight(t->right);
        t = rotateLeft(t);
        return t;
    }
    void insert()
    {
        cout << "Keep entering data enter -1 to stop";
        int x;
        cin >> x;
        while (x != -1)
        {
            root = insertRec(root, x);
            cin >> x;
        }
    }
    Node* insertRec(Node* root, int x)
    {
        if (root == NULL)
        {
            return new Node(x);
        }
        else if (x < root->data)//x should be in the left subtree
        {
            root->left = insertRec(root->left, x);;
            //after inserting the node i have to check all the upper hirarchical nodes balance factor
            if (balFactor(root) == 2)//as the node is inserted at the left subtree the balance factor should be //2 for now 
            {
                //i have to check if the rotation is left left or left right;
                if (root->left->data > x)//x is at the left left from root (right rotation is required)
                {
                    root = rotateRight(root);   //also the term root->right will never be null in this case
                                               //bcz bacfactor(root) is 2
                }
                else//x is inserted at the right of the data (left right rotation
                {
                    root = rotateLeftRight(root);
                }
            }
        }
        else if (x > root->data)
        {
            //x is present at the right sub tree;
           root->right= insertRec(root->right, x);
           if (balFactor(root) == -2)
           {
               //check if right right rotatation or right left rotation
               if (root->right->data > x)//x is present in the left (right left rotation0
               {
                   root = rotateRightLeft(root);
               }
               else
               {
                   root = rotateLeft(root);
               }
           }
        }
        else
        {
            cout << "duplicate data is present";
        }
        return root;

    }
};
int main()
{
    std::cout << "Hello World!\n";
    AVLTree tree;
    tree.insert();
    tree.showRec();

}
