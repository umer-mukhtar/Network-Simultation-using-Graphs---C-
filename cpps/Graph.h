#pragma once
#include <iostream>
#include <string>
#include "Vector.h"
#include "PriorityQueue.h"
#include "GlobalFunctions.h"

using namespace std;

template <class T>
class AdjListNode {
public:
    T data;
    int id; //Used for dijkistra
    int distances;
    AdjListNode<T>* next;
    int weight;
    template <class U>
    friend class AdjList;
public:
    AdjListNode() {
        next = NULL;
        weight = -1;
        distances = 0;
        id = -1;
    }
    AdjListNode(T data) {
        this->data = data;
        next = NULL;
        distances = 0;
        weight = -1;
        id = -1;
    }
    AdjListNode(T data, int weight) {
        this->data = data;
        next = NULL;
        distances = 0;
        this->weight = weight;
        id = -1;
    }
};
template <class T>
class AdjList {
public:
    AdjListNode<T>* head;
public:
    AdjList() {
        head = NULL;
    }
    AdjListNode<T>* insert(T value) { //inserts at back of the node
        AdjListNode<T>* newNode = new AdjListNode<T>(value);
        if (head == NULL) {
            newNode->next = NULL;
            head = newNode;
            return newNode;
        }
        AdjListNode<T>* currentNode;
        currentNode = head;
        AdjListNode<T>* prevNode;
        prevNode = NULL;
        while (currentNode != NULL) {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
        newNode->next = NULL;
        prevNode->next = newNode;
        return newNode;
    }
    AdjListNode<T>* insert(T value, int index) {
        if (index < 0) {
            return NULL;
        }
        if (head == NULL) {
            if (index == 0) {
                AdjListNode<T>* newNode = new AdjListNode<T>(value);
                newNode->next = head; //head is NULL
                head = newNode;
                return newNode;
            }
            else {
                return NULL;
            }
        }
        int currentIndex = 1;
        AdjListNode<T>* currentNode = head;
        while (index > currentIndex && currentNode != NULL) {
            currentNode = currentNode->next;
            currentIndex++;
        }
        if (index > 0 && currentNode == NULL) {
            return NULL;
        }
        AdjListNode<T>* newNode = new AdjListNode<T>(value);
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
        AdjListNode<T>* currentNode = head;
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
        AdjListNode<T>* currentNode = head;
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
        AdjListNode<T>* currentNode = head;
        while (currentNode != NULL) {
            if (currentIndex == index) {
                currentNode->addToData(value);
            }
            currentNode = currentNode->next;
            currentIndex++;
        }
    }
    AdjListNode<T>* deleteNode(T value) { //return the node next of previous node when a node gets deleted
        AdjListNode<T>* previousNode = NULL;
        AdjListNode<T>* currentNode = head;
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
    AdjListNode<T>* deleteNodeByIndex(int index) { //return the node next of previous node when a node gets deleted
        AdjListNode<T>* previousNode = NULL;
        AdjListNode<T>* currentNode = head;
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
    AdjListNode<T>* getHead() {
        return head;
    }
    void swapNodes(int index1, int index2) {
        if (index1 == index2) {
            return;
        }
        int indexFirstNode = 0;
        int indexSecondNode = 0;
        AdjListNode<T>* firstNode = head;
        AdjListNode<T>* secondNode = head;
        AdjListNode<T>* prevNodeIndex1 = NULL;
        AdjListNode<T>* prevNodeIndex2 = NULL;
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
                AdjListNode<T>* tempNode = secondNode->next;
                secondNode->next = firstNode->next;
                firstNode->next = tempNode;
                prevNodeIndex2->next = firstNode;
            }
        }
        else if (index1 == 0) { //1st node is being pointed by head
            //index2>index1
            prevNodeIndex2->next = firstNode;
            AdjListNode<T>* tempNode = firstNode->next;
            firstNode->next = secondNode->next;
            secondNode->next = tempNode;
            head = secondNode;
        }
        else { //2nd node is being pointed by head
            //index1>index2
            prevNodeIndex1->next = secondNode;
            AdjListNode<T>* tempNode = secondNode->next;
            secondNode->next = firstNode->next;
            firstNode->next = tempNode;
            head = firstNode;
        }
    }
    void display() {
        if (head == NULL) {
            return;
        }
        AdjListNode<T>* currentNode = head;
        while (currentNode != NULL) {
            cout << currentNode->value << " ";
            currentNode = currentNode->next;
        }
        cout << endl;
    }
    void insertAtHead(T value) {
        AdjListNode<T>* newNode = new AdjListNode<T>(value);
        newNode->next = head;
        head = newNode;
    }
    void makeNull() {
        AdjListNode<T>* currentNode = head;
        AdjListNode<T>* nextNode = NULL;
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


//Priority Queue used to get the vertex with the smallest distance when using dijkstra function
//Vector based Queue
class MinPriorityQueue
{
    Vector<AdjListNode<string>*> arr;
public:
    MinPriorityQueue()
    {

    }
    void addItem(AdjListNode<string>* item)
    {
        arr.pushBack(item);
    }
    AdjListNode<string>* dequeue()
    {

        int min = arr.get(0)->distances;
        AdjListNode<string>* curr = arr.get(0);
        int idx = 0;

        for (int i = 0; i < arr.size(); i++)
        {
            if (arr.get(i)->distances < min)
            {
                curr = arr.get(i);
                min = curr->distances;
                idx = i;
            }
        }

        arr.remove(idx);
        return curr;
    }
    bool isEmpty()
    {
        return arr.size() == 0;
    }
};


template <class T>
class Graph {
public:
    Vector<AdjList<T>> arr;//As you can see graph node is not a pointer type as it is just a node(just contains the value of the node, not a pointer type)
    int numOfNodes;
public:
    Graph() {
        numOfNodes = 0;
    }
    T createVertex(T vertex) {
        AdjListNode<T>* newNode = new AdjListNode<T>(vertex);
        AdjList<T> newList;
        newList.head = newNode;
        arr.pushBack(newList);
        T temp = arr.get(numOfNodes).head->data;
        numOfNodes++;
        return temp;
    }
    void insertBidirectionalEdge(T src, T dest, int weight) {
        insertEdge(src, dest, weight);
        //insertEdge(dest, src, weight);
    }
    void insertEdge(T src, T dest,int weight) {
        for (int i = 0; i < numOfNodes; i++) {
            if (arr.get(i).head->data == src) {
                AdjListNode<T>* newNode = new AdjListNode<T>(dest, weight);
                if (arr.get(i).head->next == NULL) {
                    arr.get(i).head->next = newNode;
                    return;
                }
                AdjListNode<T>* iterator = arr.get(i).head->next;
                while (iterator->next != NULL) {
                    iterator = iterator->next;
                }
                iterator->next = newNode;
            }
        }
    }
    void showGraphStructure() {
        if (arr.size() == 0) {
            cout << "Empty graph" << endl;
            return;
        }
        if (arr.get(0).head == NULL) {
            cout << "Empty graph" << endl;
            return;
        }
        for (int i = 0; i < numOfNodes; i++) {
            AdjListNode<T>* iterator = arr.get(i).head;
            cout << iterator->data << " -> ";
            iterator = iterator->next;
            while (iterator != NULL) {
                cout << iterator->data << "|" << iterator->weight << "|" << ",";
                iterator = iterator->next;
            }
            cout << "\b ";
            cout << endl;
        }
    }
    AdjListNode<T>* searchForNode(T n)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr.get(i).head->data == n)
                return arr.get(i).head;
        }

        return NULL;
    }

    void updateEdge(T v1, T v2, int w)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr.get(i).head->data == v1)
            {
                AdjListNode<T>* curr = arr.get(i).head;
                while (curr)
                {
                    if (curr->data == v2)
                    {
                        curr->weight = w;
                        break;
                    }
                    curr = curr->next;
                }

            }

            if (arr.get(i).head->data == v2)
            {
                AdjListNode<T>* curr = arr.get(i).head;
                while (curr)
                {
                    if (curr->data == v1)
                    {
                        curr->weight = w;
                        break;
                    }
                    curr = curr->next;
                }
            }
        }
    }
    //Assigns an id to all vertices in the graph
    void assignID()
    {
        for (int i = 0; i < numOfNodes; i++)
        {
            arr.get(i).head->id = i;
        }
        for (int i = 0; i < numOfNodes; i++)
        {
            AdjListNode<T>* curr = arr.get(i).head->next;
            while (curr)
            {
                for (int i = 0; i < numOfNodes; i++)
                {
                    if (curr->data == arr.get(i).head->data)
                        curr->id = arr.get(i).head->id;
                }
                curr = curr->next;
            }
        }
       
    }
    //Updates the distances of all the vertices of the graph based on shortest distance to from the source specified in applyDijkstra()
    void updateDistances(int* distances)
    {
        for (int i = 0; i < numOfNodes; i++)
        {
            arr.get(i).head->distances = distances[i];
        }
    }
    //helper function to display the path to vertex with id=k
    T displayPath(AdjListNode<T>** v, int k)
    {
        if (v[k] == NULL)
            return "";

        return (v[k]->data + " ") + displayPath(v, v[k]->id);
    }
    T applyDijkstra(T start, T end)
    {
        assignID(); //Assigns an ID to all of the nodes 
        AdjListNode<T>** p = new AdjListNode<T>*[numOfNodes]; 
        AdjListNode<T>* src = searchForNode(start); //Node of the source

        int* dist = new int[numOfNodes]; //Array of distances, indexes specifiy id numbers 
        for (int i = 0; i < numOfNodes; i++)
        {
            dist[i] = INT_MAX; //Assigning infinity to each of the vertices(devices)
        }
        dist[src->id] = 0; //Source distance is 0
        updateDistances(dist); //Distance is updated accordingly in the disctance variable found in AdjListNode
        
        p[src->id] = NULL; //No parent can exist of the source vertex
        Vector<string> visited; //Keeps track of visited vertices
        MinPriorityQueue Q; //Queue used for the algorithm, returns vertex with smallest distance

        for (int i = 0; i < numOfNodes; i++)
        {
            Q.addItem(arr.get(i).head); 
        }

        while (!Q.isEmpty())
        {
            AdjListNode<T>* u = Q.dequeue(); //Current node
            visited.pushBack(u->data);
            AdjListNode<T>* v = u->next;

            //Checking all adjacent vertices for the shortest paths and updating distances accordingly 
            while (v)
            {
                if (dist[v->id] > dist[u->id] + v->weight && !visited.checkForElement(v->data))
                {
                    dist[v->id] = dist[u->id] + v->weight;
                    p[v->id] = u;
                    updateDistances(dist);
                }
                v = v->next;
            }
        }
        updateDistances(dist);
       
        //Displaying all the generated path, storage of some form needs to be implemented
        string retStr = "";
        for (int i = 0; i < numOfNodes; i++)
        {
            retStr += displayPath(p, i); //Display the path from the source to the id(i) of another vertex
            //Displaying the last vertex(target vertex)
            for (int j = 0; j < numOfNodes; j++)
            {
                if (arr.get(j).head->id == i) {
                    retStr += arr.get(j).head->data;
                    if (arr.get(j).head->data == end) {
                        return retStr;
                    }
                }
            } 
            //Displaying the shortest distance from vertex with id(i) to the source
            //retStr += "\t Distance: " + intToString(dist[i]) + "\n";
            //cout << retStr;
            retStr = "";
        }
       
        //The function will likely return the path of the source to the specified destionation, however it can be changed based on implemetation of other parts(routing table)
        return " ";

    }
    bool isAdjacent(T v1, T v2) //checks if the two vertices are adjacent
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr.get(i).head->data == v1)
            {
                AdjListNode<T>* curr = arr.get(i).head;
                while (curr)
                {
                    if (curr->data == v2)
                        return true;
                    curr = curr->next;
                }
            }
        }

        return false;
    }
};