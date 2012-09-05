#include "StudentsWife.h"
#include "StudentsWifeOwnedStates.h"


StudentsWife::StudentsWife(int id, WorldClock* clock) : BaseGameEntity(id),
	myAmtOfSleep(2),
	myLocation(home),
	myHoursWorked(0)
{
	//Gives the StudentsWife entity a pointer to the global clock
	myClockPtr = clock;

	myStateMachine = new StateMachine<StudentsWife>(this);

	myStateMachine->SetCurrentState(wSleep::Instance());
}

//Determines whether or not the entity has to work based on the following [boring] schedule:
//Sunday: (N/A)
//Monday: 08:00-16:00
//Tuesday: 08:00-16:00
//Wednesday: 08:00-16:00
//Thursday: 08:00-16:00
//Friday: 08:00-16:00
//Saturday: 08:00-16:00
bool StudentsWife::TimeForWork()
{
	int day = myClockPtr->getDay();
	int time = myClockPtr->getTime();

	switch(day){
		//Work mon-fri
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		return (time == 8) ? true : false;
		//Don't work sunday/saturday
	case 0:
	case 6:
	default:
		return false;
	}
}

//Returns true if the time is 10PM or later (22:00)
bool StudentsWife::TimeForSleep()
{
	int time = myClockPtr->getTime();
	
	return (time >= 22) ? true : false;
}

void StudentsWife::Update()
{
	myStateMachine->Update();
}