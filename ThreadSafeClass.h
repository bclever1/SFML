#pragma once
#ifndef TSC_H
#define TSC_H

#include "stdafx.h"

#include <mutex>
#include <iostream>
#include <ostream>
#include <vector>
#include <string>

#include "Message.h"
#include "Exceptions.h"

#define cout(x) threadSafeIOProtector(x)

class threadSafeSingleton
{
public:

	static threadSafeSingleton* GetInst()
	{
		std::call_once(flag1, []() {new threadSafeSingleton(); });
		return threadSafeSingleton::myInstance;
	}

	static void NewMessage(Message* theMessage);
	Response* GetRequest(MessageType_e theMessageType);
	

private:

	threadSafeSingleton() { 
		myInstance = this;
		threadSafeSingleton::myMessages = new vector<Message*>();
	}

	static threadSafeSingleton* myInstance;
	static vector<Message*>* myMessages;
	static vector<std::string>* myOutboundMessages;
	static std::once_flag flag1;
	static std::mutex my_mutex;

};


#endif