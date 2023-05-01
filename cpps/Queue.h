#pragma once
#include <iostream>
#include <string>

using namespace std;

//Simple FIFO Queue

template <class T>
class QueueNode {
public:
    T data;
    QueueNode<T>* next;

    template <class U>
    friend class Queue;
public:
    QueueNode() {
        next = NULL;
    }
    QueueNode(T data) {
        this->data = data;
        next = NULL;
    }
};

template <class T>
class Queue {
public:
    QueueNode<T>* front;
    QueueNode<T>* rear;
    int numOfQueueNodes;
public:
    Queue() {
        front = NULL;
        rear = NULL;
        numOfQueueNodes = 0;
    }
    void enqueue(T value) {
        QueueNode<T>* newQueueNode = new QueueNode<T>(value);
        if (isEmpty()) {
            front = newQueueNode;
            rear = newQueueNode;
        }
        else {
            rear->next = newQueueNode;
            rear = newQueueNode; //we need to change rear
        }
        numOfQueueNodes++;
    }
    T dequeue() {
        QueueNode<T>* tempQueueNode = new QueueNode<T>;

        T tempData;
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return tempQueueNode->data;
        }
        else {
            tempData = front->data;
            tempQueueNode = front->next;
            delete front;
            front = tempQueueNode;
            numOfQueueNodes--;
            if (!numOfQueueNodes) {
                rear = NULL;
            }
        }
        return tempData;
    }
    T peek() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return NULL;
        }
        return front->data;
    }
    bool isEmpty() {
        return !numOfQueueNodes;
    }
    void makeNull() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    void display() {
        if (front == NULL) {
            return;
        }
        QueueNode<T>* currentQueueNode = front;
        do {
            cout << currentQueueNode->data << " ";
            currentQueueNode = currentQueueNode->next;
        } while (currentQueueNode != rear);
        cout << currentQueueNode->data << " ";
        cout << endl;
    }
};

