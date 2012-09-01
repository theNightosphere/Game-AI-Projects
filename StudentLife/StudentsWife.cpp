#include "StudentsWife.h"
#include "StudentsWifeOwnedStates.h"


StudentsWife::StudentsWife(int id, WorldClock* clock) : BaseGameEntity(id),
	myAmtOfSleep(2),
	myLocation(home)
{
	//Gives the StudentsWife entity a pointer to the global clock
	myClockPtr = clock;

	myStateMachine = new StateMachine<StudentsWife>(this);

	myStateMachine->SetCurrentState(Sleep::Instance());
}

