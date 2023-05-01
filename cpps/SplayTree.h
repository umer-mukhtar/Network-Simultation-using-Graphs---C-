#pragma once
#include <iostream>
#include <string>

#include "Devices.h"

using namespace std;

template <class T>
class SplayTreeNode {
public:
    T data;
    SplayTreeNode<T>* left;
    SplayTreeNode<T>* right;
public:
    SplayTreeNode() {
        left = NULL;
        right = NULL;
    }
    SplayTreeNode(T data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

template <class T>
class SplayTree {
public:
    SplayTreeNode<T>* root;
public:
    SplayTree() {
        root = NULL;
    }
    ~SplayTree() {

    }
    SplayTreeNode<T>* deleteNode(T data) {
        if (root == NULL) {
            return NULL;
        }
        root = splayNode(root, data);
        SplayTreeNode<T>* tempNode;
        if (root->data != data) {
            return root;
        }
        if (root->left == NULL) {
            tempNode = root;
            root = root->right;
        }
        else { //root->left !=NULL
            tempNode = root;
            root = splayNode(root->left, data);
            root->right = tempNode->right;
        }
        delete tempNode;
        return root;
    }
    SplayTreeNode<T>* insert(T data) {
        if (root == NULL) {
            SplayTreeNode<T>* newNode = new SplayTreeNode<T>(data);
            root = newNode;
            return root;
        }
        else {
            root = splayNode(root, data);
            if (root->data == data) { //entry already present
                return root;
            }
            SplayTreeNode<T>* newNode = new SplayTreeNode<T>(data);
            if (root->data > data) {
                newNode->right = root;
                newNode->left = root->left;
                root->left = NULL;
            }
            else { //root->data < data 
                newNode->left = root;
                newNode->right = root->right;
                root->right = NULL;
            }
            root = newNode;
            return newNode;
        }
    }

    SplayTreeNode<T>* search(T data) {
        if (root == NULL) {
            return NULL;
        }
        root = splayNode(root, data);
        return root;
    }
    SplayTreeNode<T>* splayNode(SplayTreeNode<T>* currNode, T data)
    {
        if (currNode == NULL) {
            return currNode;
        }
        if (currNode->data == data) {
            return currNode;
        }
        else if (currNode->data < data)
        {
            if (currNode->right == NULL) {
                return currNode;
            }
            if (currNode->right->data > data) // zag-zig
            {
                currNode->right->left = splayNode(currNode->right->left, data);
                if (currNode->right->left != NULL) {
                    currNode->right = rightRotation(currNode->right);
                }
            }
            else if (currNode->right->data < data)// zag-zag
            {
                currNode->right->right = splayNode(currNode->right->right, data);
                currNode = leftRotation(currNode);
            }
            if (currNode->right == NULL) {
                return currNode;
            }
            else {
                return leftRotation(currNode);
            }
        }
        else if (currNode->data > data)
        {
            if (currNode->left == NULL) {
                return currNode;
            }
            if (currNode->left->data > data) //zig-zig
            {
                currNode->left->left = splayNode(currNode->left->left, data);
                currNode = rightRotation(currNode);
            }
            else if (currNode->left->data < data) // zig-zag
            {
                currNode->left->right = splayNode(currNode->left->right, data);
                if (currNode->left->right != NULL) {
                    currNode->left = leftRotation(currNode->left);
                }
            }
            if (currNode->left == NULL) {
                return currNode;
            }
            else {
                return rightRotation(currNode);
            }
        }
    }

    SplayTreeNode<T>* searchCustom(string data)
    {
        if (root == NULL) {
            return NULL;
        }
        root = splayCustomNode(root, data);
        return root;
    }
    SplayTreeNode<T>* splayCustomNode(SplayTreeNode<T>* currNode, string data)
    {
        if (currNode == NULL) {
            return currNode;
        }
        if (currNode->data.destination == data) {
            return currNode;
        }
        else if (currNode->data < data)
        {
            if (currNode->right == NULL) {
                return currNode;
            }
            if (currNode->right->data > data) // zag-zig
            {
                currNode->right->left = splayCustomNode(currNode->right->left, data);
                if (currNode->right->left != NULL) {
                    currNode->right = rightRotation(currNode->right);
                }
            }
            else if (currNode->right->data < data)// zag-zag
            {
                currNode->right->right = splayCustomNode(currNode->right->right, data);
                currNode = leftRotation(currNode);
            }
            if (currNode->right == NULL) {
                return currNode;
            }
            else {
                return leftRotation(currNode);
            }
        }
        else if (currNode->data > data)
        {
            if (currNode->left == NULL) {
                return currNode;
            }
            if (currNode->left->data > data) //zig-zig
            {
                currNode->left->left = splayCustomNode(currNode->left->left, data);
                currNode = rightRotation(currNode);
            }
            else if (currNode->left->data < data) // zig-zag
            {
                currNode->left->right = splayCustomNode(currNode->left->right, data);
                if (currNode->left->right != NULL) {
                    currNode->left = leftRotation(currNode->left);
                }
            }
            if (currNode->left == NULL) {
                return currNode;
            }
            else {
                return rightRotation(currNode);
            }
        }
    }


    SplayTreeNode<T>* rightRotation(SplayTreeNode<T>* nodePositionX) { //zag rotation
        SplayTreeNode<T>* nodePositionY;
        nodePositionY = nodePositionX->left;
        nodePositionX->left = nodePositionY->right;
        nodePositionY->right = nodePositionX;
        return nodePositionY;
    }
    SplayTreeNode<T>* leftRotation(SplayTreeNode<T>* nodePositionX) { //zig rotaion
        SplayTreeNode<T>* nodePositionY;
        nodePositionY = nodePositionX->right;
        nodePositionX->right = nodePositionY->left;
        nodePositionY->left = nodePositionX;
        return nodePositionY;
    }
};