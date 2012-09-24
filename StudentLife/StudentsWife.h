/**
 *	Name: StudentsWife.h
 *
 *	Author: Reed Johnson
 *
 *	Date: 9.16.2012
 *
 *	Description: The prototype for the StudentsWife class, an intelligent agent that interacts with the Student.
 */
#pragma once
#ifndef	WIFE_H
#define	WIFE_H
#include "WorldClock.h"
#include "BaseGameEntity.h"
#include "State.h"
#include "StateMachine.h"
#include "Locations.h"
<<<<<<< HEAD
#include "MessageDispatcher.h"
=======
#include <iostream>
>>>>>>> 5b25a19e9fc4ea4677fc543e5700084e73fe6282


class StudentsWife : public BaseGameEntity
{
private:
	State<StudentsWife>*	myCurrentState;

	State<StudentsWife>* myGlobalState;

	State<StudentsWife>* myPreviousState;

	StateMachine<StudentsWife>* myStateMachine;

	//Pointer to the world clock. Is used to check time, never change it.
	WorldClock* myClockPtr;

	//Student's current location
	location_type	myLocation;

	//Integer representing number of hours entity has been sleeping
	int	myAmtOfSleep;

	//Integer representing number of hours entity has been working
	int myHoursWorked;

	bool isWatchingTV;
public:
	StudentsWife(int id, WorldClock* clock);
	~StudentsWife(){ delete myStateMachine; }

	void ChangeLocation(const location_type location) { myLocation = location; }
	
	location_type Location() const{ return myLocation; }

	int GetSleepTime()const{ return myAmtOfSleep; }

	//Called by Sleep::Execute() to simulate entity sleeping.
	void SleepMore(){ myAmtOfSleep += 2; }

	//Called by Sleep::Exit() to reset sleep value to 0. 
	void resetSleep(){ myAmtOfSleep = 0; }

	int GetHoursWorked() const { return myHoursWorked; }

	//Called by Work::Execute() to simulate entity working.
	void IncHoursWorked() { myHoursWorked += 2; }

	//Called by Work::Exit()
	void resetHoursWorked() { myHoursWorked = 0; }

	void Update();

	bool TimeForWork();
	bool TimeForSleep();
	bool HandleMessage(const Telegram& msg);
	bool WatchingTV() const{ return isWatchingTV; }

	void setWatchingTV(bool watchingOrNot){ isWatchingTV = watchingOrNot; }
	StateMachine<StudentsWife>* GetFSM() const{ return myStateMachine; }
};

#endif	

