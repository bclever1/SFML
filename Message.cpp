#include "stdafx.h"

#include "Message.h"
#include "Exceptions.h"

#include <string>

using namespace std;

Message::Message(string theMessage, vector<std::function<void(error_message)>> f, MessageType_e theMessageType, int theMessagePriority):
	myMessage(theMessage),
	myMessageType(theMessageType),
	myPriority(theMessagePriority),
	myCallbacks(f)
{
}

Message::~Message()
{
}

void Message::Callback(error_message e)
{

	myCallbacks[(int)e](e);
}