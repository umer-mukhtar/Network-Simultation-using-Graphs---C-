#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <Windows.h>

#include "Vector.h"
#include "Devices.h"
#include "SplayTree.h"
#include "Queue.h"
#include "LinkedList.h"
#include "Graph.h"
#include "GlobalFunctions.h"
#include "Message.h"
#include "PriorityQueue.h"


//20I-0555 SAAD BIN FAROOQ
//20I-0696 UMER MUKHTAR
//20I-2473 MUHAMMAD HUZAIFA

using namespace std;

Graph<string> networkGraph;
Vector<Router*> routers; //All the routers in the network
Vector<Machine*> machines; //All the machines in the network
int routingTableType;
class Network
{
public:
	int keys = 100;
public:
	Network() {}
	void initiate()
	{
		populateGraph();
		populateRoutersMachines();
		initializeRoutingTables();
	}
	void initializeRoutingTables() {
		for (int i = 0; i < routers.size(); i++) {
			while (routers.get(i)->RT.size() != 0) {
				routers.get(i)->RT.popBack();
			}			
			routers.get(i)->LLRoutingTable.head = NULL;
			routers.get(i)->SplayRoutingTable.root = NULL;
		}
		for (int i = 0; i < machines.size(); i++) {
			for (int j = 0; j < routers.size(); j++) {
				RoutingTable temp(machines.get(i)->name);
				routers.get(j)->RT.pushBack(temp);
			}
		}
		//now the machines have been fed into the routing table.
		//to find the next best routers
		for (int i = 0; i < machines.size(); i++) { //source machine
			for (int k = 0; k < machines.size(); k++) { //destination machines
				if (k != i) { 
					Vector<string> path = findPath(machines.get(i)->name, machines.get(k)->name);
					if (path.size() == 2) { //this means machines are connected to the same router
						for (int o = 0; o < routers.size(); o++) {
							if (routers.get(o)->routerName == path.get(0)) {
								for (int p = 0; p < routers.get(o)->RT.size(); p++) {
									if (routers.get(o)->RT.get(p).destination == machines.get(k)->name) {
										*(routers.get(o)->RT.get(p).outgoingQueue) = machines.get(k)->name;// routers.get(j)->routerName;
									}
								}
							}
						}
					}
					else {	
						for (int l = 0; l < path.size() - 1; l++) {
							for (int j = 0; j < routers.size(); j++) {
								if (path.get(l) == routers.get(j)->routerName) {
									for (int m = 0; m < routers.get(j)->RT.size(); m++) {
										if (machines.get(k)->name == routers.get(j)->RT.get(m).destination) {
											*(routers.get(j)->RT.get(m).outgoingQueue) = path.get(l + 1);// routers.get(j)->routerName;
										}
									}
								}
							}
						}
					}
				}
			}
		}

		//ASSIGNING KEYS HERE and SPLAY TREE here
		int key = 1;
		for (int i = 0; i < routers.size(); i++)
		{
			routers.get(i)->populateRoutingTables(key);
			//routers.get(i)->LLRoutingTable.display();
			//ADJUST SPLAY TREE HERE 
		}



	}

	void sendMessage(Message newMsg)
	{
		//Finding the machine for the message
		for (int i = 0; i < machines.size(); i++)
		{
			if (machines.get(i)->name == newMsg.source)
			{
				newMsg.trace = machines.get(i)->name;
				newMsg.trace += " ";
				machines.get(i)->addMsg(newMsg);
				return;
			}

		}

		cout << "The mentioned device name was not found in the network\n";
		return;
	}


	Vector<string> findPath(string source, string dest) {

		string path = networkGraph.applyDijkstra(source, dest); //Experimental, used for debugging
		Vector<string> temp = tokenizeString(path, ' '); 
		if (path != "") {
			removeSource(source, temp);
		}
		invertArray(temp);
		//for (int i = 0; i < temp.size(); i++) {
		//	cout << temp.get(i) << endl;
		//}

		return temp;
	}
	void populateGraph(string dat = "network.csv")
	{
		ifstream networkFile;
		networkFile.open(dat);
		string lineStr;
		getline(networkFile, lineStr);
		Vector<string> nodeArr = tokenizeString(lineStr, ',');
		for (int i = 0; i < nodeArr.size(); i++) {
			networkGraph.createVertex(nodeArr.get(i));
		}
		routingTableType = 1;
		while (!networkFile.eof()) {
			getline(networkFile, lineStr);
			if (lineStr == "") {
				continue;
			}
			Vector<string> edgeArr = tokenizeString(lineStr, ',');
			string currNode = edgeArr.get(0);
			edgeArr.remove(0);
			for (int i = 0; i < nodeArr.size(); i++) {
				if (edgeArr.get(i) != "?") {
					networkGraph.insertBidirectionalEdge(currNode, nodeArr.get(i), stringToIntDouble(edgeArr.get(i)));
				}
			}
		}
		networkFile.close();
	}
	void populateRoutersMachines()
	{
		ifstream networkFile;
		networkFile.open("network.csv");
		string lineStr;
		getline(networkFile, lineStr);
		Vector<string> nodeArr = tokenizeString(lineStr, ',');
		for (int i = 0; i < nodeArr.size(); i++)
		{
			if (nodeArr.get(i)[0] == 'R')
			{
				Router* newRouter = new Router(nodeArr.get(i));
				if (routingTableType == 1) {
					newRouter->isLinear = true;
				}
				else {
					newRouter->isLinear = false;
				}
				routers.pushBack(newRouter);
				
			}
			else
			{
				Machine* newMachine = new Machine(nodeArr.get(i));
				machines.pushBack(newMachine);
			}
		}
		networkFile.close();
	}

	void changeEdgeWeight(string device1, string device2, int weight)
	{
		networkGraph.updateEdge(device1, device2, weight);
		initializeRoutingTables();
	}

	//Checks if any remaining message left in the network
	bool isDone()
	{

		//checking for empty queues in all routers
		for (int i = 0; i < routers.size(); i++)
		{
			if (!routers.get(i)->incomingQueue->isEmpty())
				return false;
			if (!routers.get(i)->outgoingQueue->isEmpty())
				return false;
		}
		//checking for empty queues in all the machines connected
		for (int i = 0; i < machines.size(); i++)
		{
			if (!machines.get(i)->incomingQ.isEmpty())
				return false;
			if (!machines.get(i)->outgoingQ.isEmpty())
				return false;
		}

		return true;
	}
	//Sending of message to be managed using this function

	void addDataToTable(string router, string dest, string nextQ)
	{
		for (int i = 0; i < routers.size(); i++)
		{
			if (routers.get(i)->routerName == router)
			{
				RoutingTable* newTable = new RoutingTable;
				newTable->destination = dest;
				newTable->outgoingQueue = &nextQ;
				newTable->key = keys++;

				if (routers.get(i)->isLinear)
				{
					routers.get(i)->LLRoutingTable.insert(*newTable);
					return;
				}
				else
				{
					routers.get(i)->SplayRoutingTable.insert(*newTable);
					return;
				}
			}
		}

		cout << "The specified router was not found\n";
	}
	void removeDataFromTable(string router, string dest, string next)
	{
		for (int i = 0; i < routers.size(); i++)
		{
			if (routers.get(i)->routerName == router)
			{
				if (routers.get(i)->isLinear)
				{
					ListNode<RoutingTable>* curr = routers.get(i)->LLRoutingTable.head;

					while (curr)
					{
						if (curr->getData().destination == dest && *curr->getData().outgoingQueue == next)
						{

							break;
						}
						curr = curr->next;
					}

					if (curr)
					{
						routers.get(i)->LLRoutingTable.deleteNode(curr->getData());
						cout << "Delete successful\n";
					}
					else
						cout << "The routing table entry was not found\n";

					return;
				}
				else
				{
					SplayTreeNode<RoutingTable>* rem = routers.get(i)->SplayRoutingTable.searchCustom(dest);
					SplayTreeNode<RoutingTable>* del = routers.get(i)->SplayRoutingTable.deleteNode(rem->data);

					if (del == NULL)
						cout << "The Entry was not found!\n";
					else
						cout << "Delete successful\n";
					return;
				}
			}
		}
	}


} network;

bool simulationStarted = false;

bool dequeueOutgoing = false;

bool dontTerminate = true;
bool dontTerminate2 = true;

void updateIncomingQueues()
{
	while (1) {
		if (simulationStarted == true) {
			if (dequeueOutgoing == false) {
				dontTerminate2 = true;
				//Updating all the routers
				for (int i = 0; i < routers.size(); i++)
				{
					//We found a router with a non empty outgoing queue
					if (!routers.get(i)->outgoingQueue->isEmpty())
					{
						dequeueOutgoing = true;
					}

					//We found a router with a non empty incoming queue
					if (!routers.get(i)->incomingQueue->isEmpty())
					{
						routers.get(i)->addMsgToOutgoing();
					}
				}

				//Updating all the machines
				for (int i = 0; i < machines.size(); i++)
				{
					if (!machines.get(i)->incomingQ.isEmpty())
					{
						machines.get(i)->recieveMsg();
					}

					if (!machines.get(i)->outgoingQ.isEmpty())
					{
						dequeueOutgoing = true;
					}
				}
				dontTerminate2 = false;
			}
		}
	}
}

void updateOutgoingQueue()
{
	while (1) {
		if (simulationStarted == true) {
			if (dequeueOutgoing == true) {
				dontTerminate = true;
				Sleep(2000);
				//Updating all the routers
				for (int i = 0; i < routers.size(); i++)
				{
					//We found a router with a non empty outgoing queue
					while (!routers.get(i)->outgoingQueue->isEmpty())
					{
						string destName = routers.get(i)->outgoingQueue->front->data.dest;
						string nextQueue = routers.get(i)->getNextDevice(destName);

						//If the next queue is a router then we find that router and update its incoming queue
						for (int j = 0; j < routers.size(); j++)
						{
							if (nextQueue == routers.get(j)->routerName)
							{
								routers.get(j)->addMsg(routers.get(i)->outgoingQueue->dequeue());
							}
						}

						//If the next queue is a machine queue, then we find that machine and enqueue the message into it's incoming queue
						for (int j = 0; j < machines.size(); j++)
						{
							if (nextQueue == machines.get(j)->name)
							{
								//Dequeue the message from the current router to the next machine
								machines.get(j)->getMsg(routers.get(i)->outgoingQueue->dequeue());
							}
						}

					}
				}

				//Updating all the machines
				for (int i = 0; i < machines.size(); i++)
				{
					if (!machines.get(i)->incomingQ.isEmpty())
					{
						machines.get(i)->recieveMsg();
					}

					if (!machines.get(i)->outgoingQ.isEmpty())
					{
						//We search for the router needed and add it to its incoming queue
						for (int j = 0; j < routers.size(); j++)
						{
							//if the router and graph are adjacent
							if (networkGraph.isAdjacent(routers.get(j)->routerName, machines.get(i)->name))
							{
								//forwards the message from the the outgoing queue of the machine to the incoming queue of the router
								routers.get(j)->addMsg(machines.get(i)->outgoingQ.dequeue());
								//routers.get(i)->incomingQueue->enqueue(machines.get(i)->outgoingQ.dequeue());
							}
						}

					}

				}
				dequeueOutgoing = false;
				dontTerminate = false;
			}
		}
	}
}

//bool terminateProgram = false;

bool simulationComplete = false;

void terminator() {
	while (1) {
		while (!simulationComplete) {
			if (dontTerminate == false && dontTerminate2 == false) {
				if (network.isDone()) {
					Sleep(2000);
					cout << "\n*****   *****   TERMINATING SIMULATION   *****   *****" << endl << endl;
					simulationComplete = true;
					dontTerminate = true;
					dontTerminate2 = true;
					dequeueOutgoing = false;
					simulationStarted = false;
				}
			}
		}
	}
}

int main()
{
	cout << "*******************NETWORK******************" << endl << endl;

	cout << "Please select the routing table type: \n1) Linear List\n2) Splay Tree\nOption: ";
	cin >> routingTableType;
	cout << endl;
	//routingTableType = 1;

	network.initiate();
	//networkGraph.showGraphStructure();

	thread incQ(updateIncomingQueues);
	incQ.detach();
	thread outQ(updateOutgoingQueue);
	outQ.detach();
	thread term(terminator);
	term.detach();


	string command;
	while (1) {
		getline(cin, command);
		if (command == "exit") {
			break;
		}
		else {
			Vector<string> arr = tokenizeString(command, ' ');
			if (arr.get(0) == "send" && arr.get(1) == "msg") {
				simulationComplete = false;
				if (doesStringInclude(arr.get(2), ".txt")) {
					//text file
					cout << "Fetching data from file..." << endl;
					ifstream fp(arr.get(2));
					if (!fp.good())
					{
						cout << "Couldn't open specified file." << endl;
						break;
					}
					string things;

					cout << "\n*****   *****   SIMULATION STARTED   *****   *****" << endl << endl;

					while (!fp.eof())
					{
						getline(fp, things);
						Vector<string>tkn = tokenizeString(things, ':');
						if (tkn.size() != 5)
						{
							cout << "Invalid data was found in file\n";
							break;

						}
						Message* newMsg = new Message(stringToIntDouble(tkn.get(0)), stringToIntDouble(tkn.get(1)), tkn.get(2), tkn.get(3), tkn.get(4));
						network.sendMessage(*newMsg);
					}
					fp.close();
					simulationStarted = true;
				}
				else {
					cout << "\n*****   *****   SIMULATION STARTED   *****   *****" << endl << endl;
					Vector<string>tkn = tokenizeString(arr.get(2), ':');
					if (tkn.size() != 5)
					{
						cout << "Invalid data\n";
						break;

					}
					Message* newMsg = new Message(stringToIntDouble(tkn.get(0)), stringToIntDouble(tkn.get(1)), tkn.get(2), tkn.get(3), tkn.get(4));
					network.sendMessage(*newMsg);
					simulationStarted = true;
				}
			}
			else if (arr.get(0) == "displayRT") {
				for (int i = 0; i < routers.size(); i++) {
					cout << routers.get(i)->routerName << ":" << endl;
					routers.get(i)->RT.display();
					cout << endl;
				}
			}
			else if (arr.get(0) == "change" && arr.get(1) == "RT") {
				//change RT
				if (doesStringInclude(arr.get(4), ".csv"))
				{
					cout << "Fetching data from file..." << endl;
					ifstream fp(arr.get(2));
					if (!fp.good())
					{
						cout << "Couldn't open specified file." << endl;
						break;
					}
					string things;


					if (arr.get(3) == "add")
					{
						while (!fp.eof())
						{
							getline(fp, things);
							Vector<string>tkn = tokenizeString(things, ',');
							string router = arr.get(0);
							string dest = tkn.get(1);
							string nextQ = tkn.get(2);
							network.addDataToTable(router, dest, nextQ);
						}
					}
					else
					{
						while (!fp.eof())
						{
							getline(fp, things);
							Vector<string>tkn = tokenizeString(things, ',');
							string router = arr.get(2);
							string dest = tkn.get(0);
							string nextQ = tkn.get(1);

							network.removeDataFromTable(router, dest, nextQ);
						}
					}
					

					fp.close();
				}
				else
				{
					Vector<string>tkn = tokenizeString(arr.get(4), ',');
					
					if (arr.get(3) == "add")
					{
						string router = arr.get(2);
						string dest = tkn.get(0);
						string nextQ = tkn.get(1);

						network.addDataToTable(router, dest, nextQ);
					}
					//remove command
					else
					{
						string router = arr.get(2);
						string dest = tkn.get(0);
						string nextQ = tkn.get(1);

						network.removeDataFromTable(router, dest, nextQ);
					}

				}
			}
			else if (arr.get(0) == "print" && arr.get(1) == "path") {
				string from = arr.get(2);
				string to = arr.get(4);
				string path;
				if (from == "*")
				{
					for (int x = 0; x < machines.size(); x++) {
						if (machines.get(x)->name != to) {
							path = networkGraph.applyDijkstra(machines.get(x)->name, to);
							Vector<string> temp = tokenizeString(path, ' ');
							if (path != "") {
								removeSource(machines.get(x)->name, temp);
							}
							invertArray(temp);
							cout << machines.get(x)->name << " ";
							for (int y = 0; y < temp.size(); y++) {
								cout << temp.get(y) << " ";
							}
							cout << endl;
						}
					}
				}
				else if (to == "*")
				{
					for (int x = 0; x < machines.size(); x++) {
						if (machines.get(x)->name != from) {
							path = networkGraph.applyDijkstra(from, machines.get(x)->name);
							Vector<string> temp = tokenizeString(path, ' ');
							if (path != "") {
								removeSource(from, temp);
							}
							invertArray(temp);
							cout << from << " ";
							for (int y = 0; y < temp.size(); y++) {
								cout << temp.get(y) << " ";
							}
							cout << endl;
						}
					}
				}
				else
				{
					path = networkGraph.applyDijkstra(from, to);
					Vector<string> temp = tokenizeString(path, ' ');
					if (path != "") {
						removeSource(from, temp);
					}
					invertArray(temp);
					cout << from << " ";
					for (int y = 0; y < temp.size(); y++) {
						cout << temp.get(y) << " ";
					}
				}
				cout << endl;
			}
			else if (arr.get(0) == "change" && arr.get(1) == "edge") {
				if (doesStringInclude(arr.get(2), ".csv")) {
					cout << "Fetching data from file..." << endl;
					ifstream fp(arr.get(2));
					if (!fp.good())
					{
						cout << "Couldn't open specified file." << endl;
						break;
					}
					string things;
					while (!fp.eof())
					{
						getline(fp, things);
						Vector<string> tkn = tokenizeString(things, ',');
						if (tkn.size() != 3)
						{
							cout << "Invalid data was found in file\n";
							break;
						}
						network.changeEdgeWeight(tkn.get(0), tkn.get(1), stringToIntDouble(tkn.get(2)));
					}
					fp.close();
				}
				else {
					Vector<string> tkn = tokenizeString(arr.get(2), ',');
					network.changeEdgeWeight(tkn.get(0), tkn.get(1), stringToIntDouble(tkn.get(2)));
				}
			}
			else if (arr.get(0) == "show" && arr.get(1) == "graph" && arr.get(2) == "structure") {
				networkGraph.showGraphStructure();
			}
		}
	}	
}