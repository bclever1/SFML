#pragma once

#include <exception> 

using namespace std;

class Invalid_Message : public exception {
public:
	const char * what() const throw()
	{
		return "Invalid Message Exception\n";
	}
};

class Invalid_Message_String : public exception {
public:
	const char * what() const throw()
	{
		return "Invalid Message String Exception\n";
	}
};

class Invalid_Message_Type : public exception {
public:
	const char * what() const throw()
	{
		return "Invalid Message Type Exception\n";
	}
};

class Invalid_Message_Priority : public exception {
public:
	const char * what() const throw()
	{
		return "Invalid Message Priority Exception\n";
	}
};

enum error_message
{
	SUCCESS,
	ERROR_1,
	ERROR_2,
	ERROR_3
};

#define ERR_MSG(x) (\
    (x) == SUCCESS        ? " SUCCESS " : \
    (x) == ERROR_1        ? " Invalid_Message_String " : \
    (x) == ERROR_2        ? " Invalid_Message_Type " : \
    (x) == ERROR_3        ? " Invalid_Message_Priority " : \
    " UNKNOWN ERROR CODE")