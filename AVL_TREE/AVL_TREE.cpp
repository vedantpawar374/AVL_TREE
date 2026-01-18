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
    //deleting a node from avl tree;
    void deleteNode()
    {
        int x;
        cout << "\nENter node to be deleted";
        cin >> x;
        root=deleteRec(root, x);
    }
    Node* deleteRec(Node* root, int x)
    {
        if (root == NULL)//data is not present
        {
            cout << "\ndata is not present ";
            return NULL;
        }
        if (root->data > x)
        {
            root->left = deleteRec(root->left, x);//x is less than root->data so x if present it should be at the left of the root
            //as this is calling the deleteRec fun it may happen while delting the down tree the balance factor of the upper tree may fall
            //i am deleting the node from the left side of the tree so balance falctor if misplaced it might be -2 
            if (balFactor(root) == -2)
            {
                   if(balFactor(root->right)==0 || balFactor(root->right)==-1)//
                   {
                       root = rotateLeft(root);
                   }
                   else//balfactor(t)==1
                   {
                       root = rotateRightLeft(root);
                   }
            }
            return root;
        }
        else if (root->data < x)//if x is greater then it is present at the right
        {
            root->right = deleteRec(root->right, x);
            if (balFactor(root) == 2)
            {
                if (balFactor(root->left) == 0 || balFactor(root->left) == 1)
                {
                    root = rotateRight(root);
                }
                else
                {
                    root = rotateLeftRight(root);
                }
            }
            return root;
        }
        //as data is not greater nor smaller then data is found;
        if (root->left == NULL && root->right == NULL)//leaf node 
        {
            delete root;
            return NULL;
        }
        //check for node with one child
        else if (root->left == NULL)//data is found at root;
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        //if these cases failed node to be deleted have both the childs
        else
        {
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right=deleteRec(root->right, temp->data);
            //after deleting from the right the balfactor might be unbalanced (deleted from right bal factor becomes 2)
            if (balFactor(root) == 2)
            {
                if (balFactor(root->right) == 1 || balFactor(root) == 0)
                {
                    root = rotateRight(root);
                }
                else// bal =-1
                {
                    root = rotateLeftRight(root);
                }
            }
            return root;
        }
    }
    Node* findMin(Node* root)
    {
        Node* temp = root;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }
};
int main()
{
    std::cout << "Hello World!\n";
    AVLTree tree;
    tree.insert();
    tree.showRec();
    tree.deleteNode();
    tree.showRec();
    tree.deleteNode();
    tree.showRec();
    tree.deleteNode();
    tree.showRec();

}
