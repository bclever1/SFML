#pragma once
#ifndef CALLER_H
#define CALLER_H

#include <thread>
#include <vector>
#include <string>
#include "Message.h"
#include "Exceptions.h"

using namespace std;

//----------------------------------------------//
class Caller
{
public:
	Caller(std::string s);
	~Caller();

	void SendMsg(Message* theMessage);
	Response* GetMsg(MessageType_e);

	//void CallCompleted(string theErrorMessage);
	void TestSendMsgs();
	void TestGetMsgs();

	void Callback(error_message theErrorMessage);
	
	vector<Message*>myMessages;

	std::string my_name;
};

#endif