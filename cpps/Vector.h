#pragma once
#include <iostream>
#include <string>

using namespace std;
template <class T>
class Vector{
    T* arr;
    int capacity;
    int noOfElements;
public:
    Vector() {
        arr = new T[5]{};
        capacity = 5;
        noOfElements = 0;
    }
    ~Vector() {

    }
    void pushBack(T data) {
        if (capacity == noOfElements) {
            T* newArr = new T[capacity + 5];
            for (int i = 0; i < capacity; i++) {
                newArr[i] = arr[i];
            }
            //delete[] arr;
            capacity = capacity + 5;
            arr = newArr;
        }
        arr[noOfElements] = data;
        noOfElements++;
    }
    void set(T data, int index) {
        if (index >= noOfElements) {
            return;
        }
        else {
            arr[index] = data;
        }
    }
    //T get(int index)
    //{
    //    if (index >= noOfElements) {
    //        return NULL;
    //    }
    //    else {
    //        return arr[index];
    //    }
    //}
    T get(int index) //this get function doesnt work with index>=noOfElements
    {
        return arr[index];
    }
    void remove(int index) {
        //if (index >= noOfElements) {
        //    return;
        //}
        //else {
            T* newArr = new T[capacity];
            for (int i = 0, j = 0; i < noOfElements; i++, j++) {
                if (i == index) {
                    j--;
                }
                else {
                    newArr[j] = arr[i];
                }
            }
            //delete[] arr;
            arr = newArr;
            noOfElements--;
        //}
    }
    void popBack() {
        noOfElements--;
    }
    int size() { 
        return noOfElements; 
    }
    bool checkForElement(T item)
    {
        for (int i = 0; i < noOfElements; i++)
        {
            if (item == arr[i])
                return true;
        }

        return false;
    }
    void display()
    {
        for (int i = 0; i < noOfElements; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    void makeNull() {
        delete[] arr;
        arr = new T[5]{};
        capacity = 5;
        noOfElements = 0;
    }
    bool isEmpty() {
        if (noOfElements == 0) {
            return true;
        }
        return false;
    }
};