#pragma once
#include <iostream>
#include <string>
#include "Message.h"
#include "Vector.h"
#include "Graph.h"

using namespace std;


// A utility function to swap two elements
template<typename T>
void swap(T* x, T* y)
{
    T temp = *x;
    *x = *y;
    *y = temp;
}

class MaxHeap
{
    Message* arr;
    int size;

    void swap(Message* x, Message* y)
    {
        Message temp = *x;
        *x = *y;
        *y = temp;
    }

    void MaxHeapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int largest = i;
        if (l < size && arr[l].priority > arr[i].priority)
            largest = l;
        if (r < size && arr[r].priority > arr[largest].priority)
            largest = r;
        if (largest != i)
        {
            swap(&arr[i], &arr[largest]);
            MaxHeapify(largest);
        }
    }
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }

    void decreaseKey(int i, Message* new_val)
    {
        arr[i] = *new_val;
        while (i != 0 && arr[parent(i)].priority < arr[i].priority)
        {
            swap(&arr[i], &arr[parent(i)]);
            i = parent(i);
        }
    }
    void deleteKey(int i)
    {
        decreaseKey(i, NULL);
        dequeue();
    }
public:
    MaxHeap()
    {
        size = 0;
        arr = new Message[100];
    }
    bool isEmpty()
    {
        return size == 0;
    }
    Message dequeue()
    {
        //if (size <= 0)
        //    return "";
        if (size == 1)
        {
            size--;
            return arr[0];
        }

        Message root = arr[0];
        arr[0] = arr[size - 1];
        size--;
        MaxHeapify(0);

        return root;
    }

    Message* getFront() {
        return &arr[0];
    }
    void enqueue(Message k)
    {
        size++;
        int i = size - 1;
        arr[i] = k;

        while (i != 0 && arr[parent(i)].priority < arr[i].priority)
        {
            swap(&arr[i], &arr[parent(i)]);
            i = parent(i);
        }
    }
    void display()
    {
        for (int i = 0; i < size; i++)
            cout << arr[i].priority << " ";

        cout << endl;

    }
};





