#include "stdafx.h"

#include "Caller.h"
#include <iostream>
#include <string>
#include  <functional>
#include "ThreadSafeClass.h"
#include "IOProtector.h"
#include "Exceptions.h"


//----------------------------------------------//
Caller::Caller(std::string s) : my_name(s) {}
Caller::~Caller() {}

//----------------------------------------------//
void Caller::TestSendMsgs()
{
	using std::placeholders::_1;
	std::function<void(error_message)> success_callback = std::bind(&Caller::Callback, this, SUCCESS);
	std::function<void(error_message)> fail_1_callback = std::bind(&Caller::Callback, this, ERROR_1);
	std::function<void(error_message)> fail_2_callback = std::bind(&Caller::Callback, this, ERROR_2);
	std::function<void(error_message)> fail_3_callback = std::bind(&Caller::Callback, this, ERROR_3);

	vector<std::function<void(error_message)>>cbs;
	cbs.push_back(success_callback);
	cbs.push_back(fail_1_callback);
	cbs.push_back(fail_2_callback);
	cbs.push_back(fail_3_callback);

	myMessages.push_back(new Message(string(my_name + "_0"), cbs,  MessageType_unknown, -1));
	myMessages.push_back(new Message(string(my_name + "_1"), cbs,  MessageType_red, -1));
	myMessages.push_back(new Message(string(my_name + ""), cbs,  MessageType_blue, -1));
	myMessages.push_back(new Message(string(my_name + "_3"), cbs,  MessageType_yellow, -1));
	myMessages.push_back(new Message(string(my_name + "_4"), cbs,  MessageType_unknown, 1));
	myMessages.push_back(new Message(string(my_name + "_5"), cbs,  MessageType_yellow, 1));
	myMessages.push_back(new Message(string(my_name + "_6"), cbs,  MessageType_blue, 2));
	myMessages.push_back(new Message(string(my_name + "_7"), cbs,  MessageType_blue, 3));
	myMessages.push_back(new Message(string(my_name + "_8"), cbs,  MessageType_red, 4));
	myMessages.push_back(new Message(string(my_name + "_9"), cbs,  MessageType_red, 0));
	myMessages.push_back(new Message(string(my_name + "_10"), cbs,  MessageType_yellow, 1));
	myMessages.push_back(new Message(string(my_name + "_10"), cbs, MessageType_yellow, -11));
	myMessages.push_back(new Message(string(my_name + "_10"), cbs, MessageType_yellow, -2));
	myMessages.push_back(new Message(string(my_name + "_10"), cbs, MessageType_yellow, 300));

    std:string emptyString = "";
	myMessages.push_back(new Message(emptyString, cbs, MessageType_yellow, 2));


	vector<thread*>myThreads;

	for (int i = 0; i < myMessages.size(); ++i)
	{
		SendMsg(myMessages[i]);
	}
}

//----------------------------------------------//
void Caller::TestGetMsgs()
{
	using std::placeholders::_1;
	std::function<void(error_message)> success_callback = std::bind(&Caller::Callback, this, SUCCESS);
	std::function<void(error_message)> fail_1_callback = std::bind(&Caller::Callback, this, ERROR_1);
	std::function<void(error_message)> fail_2_callback = std::bind(&Caller::Callback, this, ERROR_2);
	std::function<void(error_message)> fail_3_callback = std::bind(&Caller::Callback, this, ERROR_3);

	vector<std::function<void(error_message)>>cbs;
	cbs.push_back(success_callback);
	cbs.push_back(fail_1_callback);
	cbs.push_back(fail_2_callback);
	cbs.push_back(fail_3_callback);

	myMessages.push_back(new Message(string(my_name + "_0"), cbs, MessageType_unknown, -1));
	myMessages.push_back(new Message(string(my_name + "_1"), cbs, MessageType_red, -1));
	myMessages.push_back(new Message(string(my_name + ""), cbs, MessageType_blue, -1));
	myMessages.push_back(new Message(string(my_name + "_3"), cbs, MessageType_yellow, -1));
	myMessages.push_back(new Message(string(my_name + "_4"), cbs, MessageType_unknown, 1));
	myMessages.push_back(new Message(string(my_name + "_5"), cbs, MessageType_yellow, 1));
	myMessages.push_back(new Message(string(my_name + "_6"), cbs, MessageType_blue, 2));
	myMessages.push_back(new Message(string(my_name + "_7"), cbs, MessageType_blue, 3));
	myMessages.push_back(new Message(string(my_name + "_8"), cbs, MessageType_red, 4));
	myMessages.push_back(new Message(string(my_name + "_9"), cbs, MessageType_red, 0));
	myMessages.push_back(new Message(string(my_name + "_10"), cbs, MessageType_yellow, 1));
	myMessages.push_back(new Message(string(my_name + "_10"), cbs, MessageType_yellow, -1));
	myMessages.push_back(new Message(string(my_name + "_10"), cbs, MessageType_yellow, -2));
	myMessages.push_back(new Message(string(my_name + "_10"), cbs, MessageType_yellow, -3));
	myMessages.push_back(new Message(string(my_name + "_10"), cbs, MessageType_yellow, -5));

	vector<thread*>myThreads;

	for (int i = 0; i < myMessages.size(); ++i)
	{
		Response* theResp = GetMsg(myMessages[i]->myMessageType);
		if (theResp)
		{
			std::string s(theResp->theMessage);
			threadSafeIOProtector::GetInst()->print(s);
		}
		else
		{
			std::string s("Not found!");
			threadSafeIOProtector::GetInst()->print(s);
		}
	}
}

//----------------------------------------------//
void Caller::SendMsg(Message* theMessage)
{
	threadSafeSingleton::GetInst()->NewMessage(theMessage);
}

//----------------------------------------------//
Response* Caller::GetMsg(MessageType_e theType)
{
	return threadSafeSingleton::GetInst()->GetRequest(theType);
}

//----------------------------------------------//
void Caller::Callback(error_message theErrorMessage)
{
	std::string s(ERR_MSG(theErrorMessage));
	threadSafeIOProtector::GetInst()->print(s);
}