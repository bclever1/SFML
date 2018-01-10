#include "stdafx.h"
#include "InputDaemon.h"
#include "IOProtector.h"

std::once_flag InputDaemon::flag1;
std::mutex InputDaemon::my_mutex;

InputDaemon* InputDaemon::myInstance = NULL;

void InputDaemon::getInput()
{
	std::lock_guard<std::mutex> guard(my_mutex);
	while (1)
	{
		int theResult;
		std::cin >> theResult;

		while (cin.fail())
		{
			std::string s("Integers only please.");
			threadSafeIOProtector::GetInst()->print(s);
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			
			std::cin >> theResult;
		}

		if (theResult == 0)
		{
			return;
		}
		else
		{
			std::string s("Input not 0.");
			threadSafeIOProtector::GetInst()->print(s);
		}
	}
}