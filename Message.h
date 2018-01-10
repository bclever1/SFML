#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>
#include  <functional>
#include "Exceptions.h"

using namespace std;

enum MessageType_e
{
	MessageType_unknown = 0,
	MessageType_red = 1,
	MessageType_yellow = 2,
	MessageType_blue = 3
};

class Message
{
public:
	Message(string, vector<std::function<void(error_message)>> f, MessageType_e, int);
	~Message();
	void Callback(error_message e);

	string myMessage;
	vector<std::function<void(error_message)>>myCallbacks;
	MessageType_e myMessageType;
	int myPriority;
};

struct Response
{
	string theMessage;
	vector<std::function<void(error_message)>>myCallbacks;
};

#endif