#include "Student.h"
#include "StudentOwnedStates.h"
#include <cassert>
/**
 *	Name: Student.cpp
 *
 *	Author: Reed Johnson
 *
 *	Date Modified: 8.31.2012
 *
 *	Description: Implements the definitions of all the methods associated with the Student class.
 */
Student::Student(int id, WorldClock* clock) : BaseGameEntity(id),
	myAmtOfSleep(2), //Clock starts at 0, so setting sleep at 2 assumes entity entered sleep at 10PM the previous day. 
	myHoursWorked(0),
	myCurrentState(Sleep::Instance())
{
	//Set the ptr to the world clock. This is never manipulated directly by Student, only polled.
	myClockPtr = clock;
}





void Student::ChangeState(State<Student>* newState)
{
	//Ensure both states are valid before attempting to call their methods
	assert(myCurrentState && newState);

	//Call the exit method of the current state
	myCurrentState->Exit(this);

	//Change state to new state
	myCurrentState = newState;

	//Call the enter method of the new state
	myCurrentState->Enter(this);
}

void Student::Update()
{

	if (myCurrentState){
		myCurrentState->Execute(this);
	}
}

//Entity determines if it has class at the current time. Schedule:
//Sunday - (N/A)
//Monday - 08:00 - 10:00
//Tuesday - 10:00 - 14:00
//Wednesday - 08:00 - 10:00, 14:00 - 16:00 (2PM-4PM)
//Thursday - (N/A)
//Friday - 10:00 - 12:00
//Saturday - (N/A)
bool Student::TimeForClass()
{
	int day = myClockPtr->getDay();
	int time = myClockPtr->getTime();
	switch(day){

	case 1://Monday
		return (time == 8) ? true : false;
	case 2://Tuesday
		return (time == 10) ? true : false;
	case 3://Wed
		return ((time == 8) || (time == 14)) ? true : false;
	case 5://Fri
		return (time == 10) ? true : false;

	case 0://Sun
	case 4://Thurs
	case 6://Sat
	default:
		return false; // Entity has no work on Sun/Thurs/Sat
	}
}

//Entity determines if class is over at the current time. Schedule:
//Sunday - (N/A)
//Monday - 08:00 - 10:00
//Tuesday - 10:00 - 14:00
//Wednesday - 08:00 - 10:00, 14:00 - 16:00 (2PM-4PM)
//Thursday - (N/A)
//Friday - 10:00 - 12:00
//Saturday - (N/A)
bool Student::ClassIsOver()
{
	int day = myClockPtr->getDay();
	int time = myClockPtr->getTime();
	switch(day){

	case 1://Monday
		return (time >= 10) ? true : false;
	case 2://Tuesday
		return (time >= 14) ? true : false;
	case 3://Wed
		return ((time >= 16) || (time == 10)) ? true : false;
	case 5://Fri
		return (time >= 12) ? true : false;

	case 0://Sun
	case 4://Thurs
	case 6://Sat
	default:
		return true; // Entity has no work on Sun/Thurs/Sat, so class is ALWAYS over on these days
	}
}

//Entity determines if it has work at the current time. Schedule:
//Sunday - 08:00 - 16:00
//Monday - 12:00 - 20:00
//Tuesday - (N/A)
//Wednesday - (N/A)
//Thursday - 10:00 - 18:00
//Friday - (N/A)
//Saturday - 14:00 - 22:00
bool Student::TimeForWork()
{
	int day = myClockPtr->getDay();
	int time = myClockPtr->getTime();
	switch(day){

	case 0://Sunday
		return (time == 8) ? true : false;
	case 1://Monday
		return (time == 12) ? true : false;
	case 4://Thursday
		return (time == 10) ? true : false;
	case 6://Saturday
		return (time == 14) ? true : false;

	case 2://Tues
	case 3://Wed
	case 5://Fri
	default:
		return false; // Entity has no work on Tues/Wed/Fri
	}
}

//The entity determines whether its time for sleep or not. 
//Returns true if the time is 20:00(10PM) or later
bool Student::TimeForSleep()
{
	int time = myClockPtr->getTime();
	
	return (time >= 20) ? true : false;

}