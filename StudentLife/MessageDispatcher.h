#pragma once
#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <set>
/**
 *	Name: MessageDispatcher.h
 *
 *	Author: Reed Johnson
 *
 *	Date Modified: 9.16.2012
 *
 *	Description: The prototype of the class which contains the methods that all entities use 
 *				 to dispatch and receive messages in the simulation. The prototype is taken almost directly from
 *				 Mat Buckland's source code in the file MessageDispatcher.h from the project WestWorldWithMessaging
 */
struct Telegram
{
	//the entity that sent this telegram
	int	sender;

	//The entity that is to receive this telegram
	int	receiver;

	//the message itself. These are all enumerated in the file
	//"MessageTypes.h"
	int	Msg;

	//Messages can be dispatched immediately or delayed for a specified amount of time.
	//If a delay is necessary, this field is stamped with the time the message should be dispatched.
	double dispatchTime;

	//any additional info that may accompany the message
	void* extraInfo;

	Telegram(double pDelay, int pSender, int pReceiver, int pMsg, void* pExtraInfo)
	{
		dispatchTime = pDelay;
		sender = pSender;
		receiver = pReceiver;
		Msg = pMsg;
		extraInfo = &pExtraInfo;
	}

	bool operator<(const Telegram& rhs) const
	{
		return (dispatchTime < rhs.dispatchTime);
	}
};
class BaseGameEntity;

class MessageDispatcher
{
private:

	//A std::set is used as the container for the delayed messages
	//because of the benefit of automatic sorting and avoidance of duplicates.
	//Messages are sorted by their dispatch time.
	std::set<Telegram> PriorityQ;

	//This method is utilized by DispatchMessage or DispatchDelayedMessages.
	//This method calls the message handling member function of the receiving entity,
	//pReceiver, with the newly created telegram
	void Discharge(BaseGameEntity* pReceiver, const Telegram& msg);

	MessageDispatcher(){}

public:
	
	//this class is a singleton
	static MessageDispatcher* Instance();

	//send a message to another agent.
	void DispatchMessage(double delay, int sender, int receiver, int msg, void* ExtraInfo);

	//send out any delayed messages. This method is called each time through the main game loop.
	void DispatchDelayedMessages();
};

//to make life easier...
#define Dispatch MessageDispatcher::Instance()

#endif