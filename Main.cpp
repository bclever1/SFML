#include "stdafx.h"

#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <stdlib.h>

#include "Caller.h"
#include "ThreadSafeClass.h"
#include "WindowManager.h"
#include "InputDaemon.h"

using namespace std;

int main()
{
	vector<thread*>myThreads;

	myThreads.push_back(new thread(&InputDaemon::getInput));

	for (int i = 0; i < 10; ++i)
	{
		//std::string s = std::to_string(i);

		//Caller C(s);

		//myThreads.push_back(new thread(&Caller::TestSendMsgs, C));
		//myThreads.push_back(new thread(&Caller::TestGetMsgs, C));

		std::string title("Window_");
		title += std::to_string(i);

		WindowManager::GetInst()->NewWindow(title);
	}

	for (int i = 0; i < myThreads.size(); ++i)
	{
		myThreads[i]->join();
	}


	return 0;
}