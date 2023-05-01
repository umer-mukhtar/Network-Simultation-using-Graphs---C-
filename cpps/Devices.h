#pragma once
#include<iostream>
#include<string>
#include "Message.h"
#include "Vector.h"
#include "SplayTree.h"
#include "Queue.h"
#include "LinkedList.h"
#include "Graph.h"
#include "GlobalFunctions.h"
#include "Message.h"
#include "PriorityQueue.h"


using namespace std;


class RoutingTable
{
public:
	int key;
	string destination;
	string* outgoingQueue; //next best router
public:
	RoutingTable() {
		destination = "NULL";
		outgoingQueue = new string;
		*outgoingQueue = "NULL";
	}
	RoutingTable(string destination) {
		this->destination = destination;
		outgoingQueue = new string;
		*outgoingQueue = "NULL";
	}
	void display() {
		cout << destination << " " << *(outgoingQueue) << endl;
	}

	bool operator >(const RoutingTable &rt)
	{
		return key > rt.key;
	}
	bool operator <(const RoutingTable& rt)
	{
		return key < rt.key;
	}
	bool operator ==(const RoutingTable& rt)
	{
		return key == rt.key;
	}
	bool operator !=(const RoutingTable& rt)
	{
		return key != rt.key;
	}

};

ostream& operator<<(ostream& os, RoutingTable const& m) 
{
	return os << m.destination << " " << *m.outgoingQueue << endl;
}

class Router
{
public:
	string routerName;
	MaxHeap* incomingQueue; //incoming
	Queue<Message>* outgoingQueue;
	bool isLinear;
	Vector<RoutingTable> RT;

	List<RoutingTable> LLRoutingTable;
	SplayTree<RoutingTable> SplayRoutingTable;

public:
	Router()
	{
		routerName = "NONE";
		isLinear = true;
		outgoingQueue = new Queue<Message>;
		incomingQueue = new MaxHeap;
	}
	
	void populateRoutingTables(int& key)
	{

		if (isLinear)
		{
			for (int i = 0; i < RT.size(); i++)
			{
				RoutingTable r = RT.get(i);
				r.key = key++;
				RT.set(r, i);
				LLRoutingTable.insert(RT.get(i));
			}
		}
		else
		{
			//Assigning key to each router
			for (int i = 0; i < RT.size(); i++)
			{
				RoutingTable r = RT.get(i);
				r.key = key++;
				RT.set(r, i);
				SplayRoutingTable.insert(RT.get(i));
			}
		}
	}

	string getNextDevice(string dest)
	{
		if (isLinear)
		{
			ListNode<RoutingTable>* curr = LLRoutingTable.head;
			while (curr)
			{
				if (curr->getData().destination == dest)
					return *curr->getData().outgoingQueue;
				curr = curr->next;
			}
		}
		else
		{
			//return the outgoing queue for the destination mentioned
			return *SplayRoutingTable.searchCustom(dest)->data.outgoingQueue;
		}

		return "Not Found";
	}
	
	//Adds a message into the incoming prority queue of the router
	void addMsg(Message msg)
	{
		cout << "..Message (ID:" << msg.msgID << ", Payload: \"" << msg.payload << "\") has been added to incoming queue of " << this->routerName << "..\n";
		incomingQueue->enqueue(msg);
	}

	//Removes a message with highest priority from the priority queue and adds it to the outgoing queue of the router
	void addMsgToOutgoing()
	{
		if (incomingQueue->isEmpty())
			return;
		while (!incomingQueue->isEmpty()) {
			Message currentMsg = incomingQueue->dequeue();
			currentMsg.trace += routerName;
			currentMsg.trace += " ";
			cout << "..Message (ID:" << currentMsg.msgID << ", Payload: \"" << currentMsg.payload << "\") has been added to the outgoing queue of " << this->routerName << "..\n";
			outgoingQueue->enqueue(currentMsg);
		}
	}

	//returns the name of the device to which the message is to be forwarded, further routing done in the network class
	string getNextDevice()
	{
		if (outgoingQueue->isEmpty())
			return "NONE";

		cout << "..A message has left the outgoing Queue of " << this->routerName << "..\n";
		Message msgToForward = outgoingQueue->front->data;
		return msgToForward.dest;
	}


	Router(string n)
	{
		routerName = n;
		isLinear = true;
		incomingQueue = new MaxHeap;
		outgoingQueue = new Queue<Message>;
	}

};

class Machine
{
public:
	string name;
	Message* messages;
	Queue<Message> incomingQ;
	Queue<Message> outgoingQ;
public:
	Machine()
	{
		name = "NONE";
		messages = NULL;
	}
	Machine(string n)
	{
		name = n;
		messages = new Message[100];
	}

	//Send a message
	void addMsg(Message msg)
	{
		cout << "..New message (ID:" << msg.msgID << ", Payload: \"" << msg.payload << "\") has been added to outgoing queue of machine " << this->name << "..\n";
		outgoingQ.enqueue(msg);
	}
	//Get a message into the incoming queue, used by routers
	void getMsg(Message msg)
	{
		cout << "..Incoming message (ID:" << msg.msgID << ", Payload: \"" << msg.payload << "\") has been added to incoming queue of machine " << this->name << "..\n";
		incomingQ.enqueue(msg);
	}
	//Funtion gets the messages recived from the incoming queue, each call gets one message
	void recieveMsg() 
	{
		if (incomingQ.isEmpty())
			return;
		Message msg = incomingQ.dequeue();
		msg.trace += name;
		cout << "..Message (ID:" << msg.msgID << ", Payload: \"" << msg.payload << "\") has been recieved and read by machine " << this->name << ".." << endl;
		cout << "Trace: " << msg.trace << endl;
	}
};

