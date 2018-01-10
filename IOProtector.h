#pragma once
#pragma once
#ifndef IOPROTECTOR_H
#define IOPROTECTOR_H

#include "stdafx.h"

#include <mutex>
#include <iostream>
#include <ostream>
#include <vector>
#include <string>

#include "Message.h"
#include "Exceptions.h"


class threadSafeIOProtector
{
public:

	static threadSafeIOProtector* GetInst()
	{
		std::call_once(flag1, []() {new threadSafeIOProtector(); });
		return threadSafeIOProtector::myInstance;
	}

	static void print(std::string theStr)
	{
		std::lock_guard<std::mutex> guard(my_mutex);

		if (theStr == "")
		{
			int i = 0;
		}
		std::cout << theStr << std::endl << std::flush;
	}

	static void print(int theStr)
	{
		std::lock_guard<std::mutex> guard(my_mutex);
		std::cout << theStr << std::endl << std::flush;
	}

	static int getInt()
	{
		std::lock_guard<std::mutex> guard(my_mutex);

		int theResult;
		std::cin >> theResult;
		return theResult;
	}

private:

	threadSafeIOProtector() {
		myInstance = this;
	}

	static threadSafeIOProtector* myInstance;
	static std::once_flag flag1;
	static std::mutex my_mutex;

};


#endif

