#pragma once
#pragma once
#ifndef INPUTDAEMON_H
#define INPUTDAEMON_H

#include "stdafx.h"

#include <mutex>
#include <iostream>
#include <ostream>
#include <vector>
#include <string>

#include "Message.h"
#include "Exceptions.h"


class InputDaemon
{
public:

	static InputDaemon* GetInst()
	{
		std::call_once(flag1, []() {new InputDaemon(); });
		return InputDaemon::myInstance;
	}

	static void getInput();

private:

	InputDaemon() {
		myInstance = this;
	}

	static InputDaemon* myInstance;
	static std::once_flag flag1;
	static std::mutex my_mutex;

};


#endif

