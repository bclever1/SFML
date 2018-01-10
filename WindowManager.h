#pragma once
#ifndef WINDOWMGR_H
#define WINDOWMGR_H

#include "stdafx.h"

#include <mutex>
#include <iostream>
#include <ostream>
#include <vector>
#include <string>

#include "Message.h"
#include "Exceptions.h"

class MyWindow;

class WindowManager
{
public:

	static WindowManager* GetInst()
	{
		std::call_once(flag1, []() {new WindowManager(); });
		return WindowManager::myInstance;
	}

	static void NewWindow(std::string the_title);
	//Response* GetRequest(MessageType_e theMessageType);

private:

	WindowManager() {
		myInstance = this;
		WindowManager::myWindows = new vector<thread*>();
	}

	static WindowManager* myInstance;
	static vector<thread*>* myWindows;
	static std::once_flag flag1;
	static std::mutex my_mutex;

};


#endif