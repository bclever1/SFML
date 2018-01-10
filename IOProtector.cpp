#include "stdafx.h"
#include "IOProtector.h"


std::once_flag threadSafeIOProtector::flag1;
std::mutex threadSafeIOProtector::my_mutex;

threadSafeIOProtector* threadSafeIOProtector::myInstance = NULL;