#include "stdafx.h"
#include "WindowManager.h"
#include "MyWindow.h"
std::once_flag WindowManager::flag1;
std::mutex WindowManager::my_mutex;

WindowManager* WindowManager::myInstance = NULL;
vector<thread*>* WindowManager::myWindows = NULL;

void WindowManager::NewWindow(std::string the_title)
{
	std::lock_guard<std::mutex> guard(my_mutex);

	MyWindow* W = new MyWindow();
	WindowManager::myWindows->push_back(new thread(&MyWindow::Display, W, the_title));
}