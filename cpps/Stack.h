#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class T>
class StackNode {
    T data;
    StackNode<T>* next;

    template <class U>
    friend class Stack;
public:
    StackNode() {
        next = NULL;
    }
    StackNode(T data) {
        this->data = data;
        next = NULL;
    }
};

template <class T>
class Stack {
    StackNode<T>* top;
public:
    Stack() {
        top = NULL;
    }
    void push(T value) {
        StackNode<T>* newNode = new StackNode<T>(value);
        newNode->next = top;
        top = newNode;
    }
    T pop() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return NULL;
        }
        StackNode<T>* tempNode;
        T tempData;
        tempNode = top;
        tempData = top->data;
        top = top->next;
        delete tempNode;
        return tempData;
    }
    bool isEmpty() {
        if (top == NULL) {
            return true;
        }
        else {
            return false;
        }
    }
    void display() {
        if (top == NULL) {
            return;
        }
        StackNode<T>* currentNode;
        currentNode = top;
        while (currentNode != NULL) {
            cout << currentNode->data << endl;
            currentNode = currentNode->next;
        }
    }
};