#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class T>
class ListNode {
public:
    T value;
    ListNode<T>* next;
    ListNode(T value) {
        this->value = value;
        next = NULL;
    }
    ListNode() {}
    T getData() {
        return value;
    }
    void setData(T value) {
        this->value = value;
    }
    ListNode<T>* getNext() {
        return next;
    }
    void addToData(T value) { //adds a value to value
        this->value += value;
    }
};

template <class T>
class List {
public:
    ListNode<T>* head;
public:
    List() {
        head = NULL;
    }
    ListNode<T>* insert(T value) { //inserts at back of the node
        ListNode<T>* newNode = new ListNode<T>(value);
        if (head == NULL) {
            newNode->next = NULL;
            head = newNode;
            return newNode;
        }
        ListNode<T>* currentNode;
        currentNode = head;
        ListNode<T>* prevNode;
        prevNode = NULL;
        while (currentNode != NULL) {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
        newNode->next = NULL;
        prevNode->next = newNode;
        return newNode;
    }
    ListNode<T>* insert(T value, int index) {
        if (index < 0) {
            return NULL;
        }
        if (head == NULL) {
            if (index == 0) {
                ListNode<T>* newNode = new ListNode<T>(value);
                newNode->next = head; //head is NULL
                head = newNode;
                return newNode;
            }
            else {
                return NULL;
            }
        }
        int currentIndex = 1;
        ListNode<T>* currentNode = head;
        while (index > currentIndex && currentNode != NULL) {
            currentNode = currentNode->next;
            currentIndex++;
        }
        if (index > 0 && currentNode == NULL) {
            return NULL;
        }
        ListNode<T>* newNode = new ListNode<T>(value);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
        }
        else {
            newNode->next = currentNode->next;
            currentNode->next = newNode;
        }
        return newNode;
    }
    int findNode(T value) {
        int currentIndex = 1;
        ListNode<T>* currentNode = head;
        while (currentNode != NULL) {
            if (currentNode->value == value) {
                return currentIndex - 1;
            }
            currentNode = currentNode->next;
            currentIndex++;
        }
        return -1;
    }
    T getValue(int index) {
        int currentIndex = 0;
        ListNode<T>* currentNode = head;
        while (currentNode != NULL) {
            if (currentIndex == index) {
                return currentNode->value;
            }
            currentNode = currentNode->next;
            currentIndex++;
        }
        return NULL;
    }
    void add(T value, int index) { //adds T in the index (not inser)
        int currentIndex = 0;
        ListNode<T>* currentNode = head;
        while (currentNode != NULL) {
            if (currentIndex == index) {
                currentNode->addToData(value);
            }
            currentNode = currentNode->next;
            currentIndex++;
        }
    }
    ListNode<T>* deleteNode(T value) { //return the node next of previous node when a node gets deleted
        ListNode<T>* previousNode = NULL;
        ListNode<T>* currentNode = head;
        while (currentNode && currentNode->value != value) {
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
        if (currentNode) {
            if (previousNode) {
                previousNode->next = currentNode->next;
                delete currentNode;
                return previousNode->next;
            }
            else {
                head = currentNode->next;
                delete currentNode;
                return head;
            }
        }
        return NULL;
    }
    ListNode<T>* deleteNodeByIndex(int index) { //return the node next of previous node when a node gets deleted
        ListNode<T>* previousNode = NULL;
        ListNode<T>* currentNode = head;
        int currentIndex = 0;
        while (currentNode && index > currentIndex) {
            previousNode = currentNode;
            currentNode = currentNode->next;
            currentIndex++;
        }
        if (currentNode) {
            if (previousNode) {
                previousNode->next = currentNode->next;
                delete currentNode;
                return previousNode->next;
            }
            else {
                head = currentNode->next;
                delete currentNode;
                return head;
            }
        }
        return NULL;
    }
    ListNode<T>* getHead() {
        return head;
    }
    void swapNodes(int index1, int index2) {
        if (index1 == index2) {
            return;
        }
        int indexFirstNode = 0;
        int indexSecondNode = 0;
        ListNode<T>* firstNode = head;
        ListNode<T>* secondNode = head;
        ListNode<T>* prevNodeIndex1 = NULL;
        ListNode<T>* prevNodeIndex2 = NULL;
        while (firstNode != NULL) {
            if (indexFirstNode == index1) {
                break;
            }
            prevNodeIndex1 = firstNode;
            firstNode = firstNode->next;
            indexFirstNode++;
        }
        while (secondNode != NULL) {
            if (indexSecondNode == index2) {
                break;
            }
            prevNodeIndex2 = secondNode;
            secondNode = secondNode->next;
            indexSecondNode++;
        }
        if (firstNode == NULL || secondNode == NULL) {
            return;
        }
        if (index1 > 0 && index2 > 0) { //if both the nodes are not being pointed by head
            if (index1 - index2 == -1) { //two consecutive nodes
                prevNodeIndex1->next = secondNode;
                firstNode->next = secondNode->next;
                secondNode->next = firstNode;
            }
            else if (index1 - index2 == 1) {//two consecutive nodes
                secondNode->next = firstNode->next;
                firstNode->next = secondNode;
                prevNodeIndex2->next = firstNode;
            }
            else {
                prevNodeIndex1->next = secondNode;
                ListNode<T>* tempNode = secondNode->next;
                secondNode->next = firstNode->next;
                firstNode->next = tempNode;
                prevNodeIndex2->next = firstNode;
            }
        }
        else if (index1 == 0) { //1st node is being pointed by head
            //index2>index1
            prevNodeIndex2->next = firstNode;
            ListNode<T>* tempNode = firstNode->next;
            firstNode->next = secondNode->next;
            secondNode->next = tempNode;
            head = secondNode;
        }
        else { //2nd node is being pointed by head
            //index1>index2
            prevNodeIndex1->next = secondNode;
            ListNode<T>* tempNode = secondNode->next;
            secondNode->next = firstNode->next;
            firstNode->next = tempNode;
            head = firstNode;
        }
    }
    void display() {
        if (head == NULL) {
            return;
        }
        ListNode<T>* currentNode = head;
        while (currentNode != NULL) {
            cout << currentNode->value << " ";
            currentNode = currentNode->next;
        }
        cout << endl;
    }
    void insertAtHead(T value) {
        ListNode<T>* newNode = new ListNode<T>(value);
        newNode->next = head;
        head = newNode;
    }
    void makeNull() {
        ListNode<T>* currentNode = head;
        ListNode<T>* nextNode = NULL;
        while (currentNode != NULL) {
            nextNode = currentNode->getNext();
            delete currentNode;
            currentNode = nextNode;
        }
        head = NULL;
    }
    bool isEmpty() {
        if (head == NULL) {
            return true;
        }
        return false;
    }
};

