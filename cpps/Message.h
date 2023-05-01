#pragma once
#include <iostream>
#include <string>

using namespace std;

class Message
{
public:
	int msgID;
	int priority;
	string source;
	string dest;
	string payload;
	string trace;
public:
	Message(const Message& msg) {
		this->msgID = msg.msgID;
		this->priority = msg.priority;
		this->source = msg.source;
		this->dest = msg.dest;
		this->payload = msg.payload;
		this->trace = msg.trace;
	}
	Message(int id, int priority, string src, string dest, string data)
	{
		msgID = id;
		this->priority = priority;
		source = src;
		this->dest = dest;
		trace = "";
		payload = data;
	}
	Message()
	{
		msgID = -1;
		priority = -1;
		source = "";
		dest = "";
		payload = "";
		trace = "";
	}

};

