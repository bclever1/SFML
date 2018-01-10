#include "stdafx.h"
#include "ThreadSafeClass.h"
#include "IOProtector.h"


std::once_flag threadSafeSingleton::flag1;
std::mutex threadSafeSingleton::my_mutex;

threadSafeSingleton* threadSafeSingleton::myInstance = NULL;
vector<Message*>* threadSafeSingleton::myMessages = NULL;
vector<std::string>* threadSafeSingleton::myOutboundMessages = NULL;

void threadSafeSingleton::NewMessage(Message* theMessage)
{
	try
	{
		std::lock_guard<std::mutex> guard(my_mutex);

		// Validate
		if (!theMessage)
		{
			Invalid_Message e;
			throw e;
		}

		if (theMessage->myMessage == "")
		{
			Invalid_Message_String e;
			throw e;
		}

		if (!(theMessage->myMessageType == MessageType_red ||
			theMessage->myMessageType == MessageType_yellow ||
			theMessage->myMessageType == MessageType_blue))
		{
			Invalid_Message_Type e;
			throw e;
		}

		if (!(theMessage->myPriority == 1 ||
			theMessage->myPriority == 2 ||
			theMessage->myPriority == 3))
		{
			Invalid_Message_Priority e;
			throw e;
		}

		// All validation checks passed, add the message to my message set.
		myMessages->push_back(theMessage);

		//  Respond to requester
		try
		{
			theMessage->Callback(SUCCESS);
		}
		catch (...)
		{
			std::string s = "Callback failed!" + theMessage->myMessage;
			threadSafeIOProtector::GetInst()->print(s);
			throw;
		}
	}
	catch (Invalid_Message e)
	{
		//???
		std::string s("Invalid message!!!");
		threadSafeIOProtector::GetInst()->print(s);
		throw;
	}
	catch (Invalid_Message_String e)
	{
		theMessage->Callback(ERROR_1);
	}
	catch (Invalid_Message_Type e)
	{
		theMessage->Callback(ERROR_2);
	}
	catch (Invalid_Message_Priority e)
	{
		theMessage->Callback(ERROR_3);
	}
	catch (...)
	{
		std::string ugly("UGLY!!!");
		ugly += ": " + theMessage->myMessage;
		threadSafeIOProtector::GetInst()->print(ugly);
	}
}

//----------------------------------------------//
Response* threadSafeSingleton::GetRequest(MessageType_e theMessageType)
{
	try
	{
		std::lock_guard<std::mutex> guard(my_mutex);

		if (!(theMessageType == MessageType_red ||
		  	  theMessageType == MessageType_yellow ||
			  theMessageType == MessageType_blue))
		{
			Invalid_Message_Type e;
			throw e;
		}

		// search myrequests based on instructions

		int theResponsePos = -1;

		for (int i = 0; i < myMessages->size(); ++i)
		{
			if ((*myMessages)[i]->myMessageType == theMessageType)
			{
				if (theResponsePos == -1)
				{
					theResponsePos = i;
				}
				else
				{
					if ((*myMessages)[theResponsePos]->myPriority < (*myMessages)[i]->myPriority)
					{
						theResponsePos = i;
					}
				}
			}
		}

		// Construct the return message and remove the element from the list
		
		if (0 <= theResponsePos && theResponsePos < myMessages->size())
		{
			Response* resp = new Response;
			
			resp->myCallbacks = (*myMessages)[theResponsePos]->myCallbacks;
			resp->theMessage = (*myMessages)[theResponsePos]->myMessage;
			myMessages->erase(myMessages->begin() + theResponsePos);

			return resp;
		}

		return nullptr;
	}
	catch (Invalid_Message_Type exp)
	{
		Response* resp = new Response;
		resp->theMessage = exp.what();
		return resp;
	}
	catch (...)
	{
		Response* resp = new Response;
		resp->theMessage = "UNKNOWN EXCEPTION";
		return resp;
	}
}