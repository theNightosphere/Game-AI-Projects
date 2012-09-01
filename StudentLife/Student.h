#pragma once
#ifndef	STUDENT_H
#define STUDENT_H


#include "BaseGameEntity.h"
#include "State.h"
#include "Locations.h"
#include "WorldClock.h"
#include "StateMachine.h"
/**
 *	Name: Student.h
 *
 *	Author: Reed Johnson
 *
 *	Date Modified: 8.31.2012
 *
 *	Description: The prototype of the Student class, a child of the BaseGameEntity class. 
 *				 The Student class is the intelligent agent in this StudentLife project. 
 */

class Student :
	public BaseGameEntity
{
private:
	//Pointer to current state
	State<Student>*	myCurrentState;

	State<Student>* myGlobalState;

	State<Student>* myPreviousState;

	StateMachine<Student>* myStateMachine;

	//Pointer to the world clock. Is used to check time, never change it.
	WorldClock* myClockPtr;

	//Student's current location
	location_type	myLocation;

	//Integer representing number of hours entity has been sleeping
	int	myAmtOfSleep;

	//Integer representing number of hours entity has been working
	int myHoursWorked;

public:
	Student(int id, WorldClock* clock);

	~Student(){ delete myStateMachine; }

	void Update();

	location_type Location() const{ return myLocation; }

	void ChangeLocation(const location_type location) { myLocation = location; }

	int GetSleepTime()const{ return myAmtOfSleep; }

	//Called by Sleep::Execute() to simulate entity sleeping.
	void SleepMore(){ myAmtOfSleep += 2; }

	//Called by Sleep::Exit() to reset sleep value to 0. 
	void resetSleep(){ myAmtOfSleep = 0; }

	bool TimeForWork();
	bool TimeForClass();
	bool TimeForSleep();
	bool ClassIsOver();

	int GetHoursWorked() const { return myHoursWorked; }

	//Called by Work::Execute() to simulate entity working.
	void IncHoursWorked() { myHoursWorked += 2; }

	//Called by Work::
	void resetHoursWorked() { myHoursWorked = 0; }

	//Returns this entity's State Machine. 
	StateMachine<Student>* GetFSM() const{ return myStateMachine; }

};

#endif
