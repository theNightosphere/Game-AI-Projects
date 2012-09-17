#include "StudentOwnedStates.h"
#include "Student.h"
#include "State.h"
#include "EntityNames.h"
#include "Locations.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityManager.h"
#include <iostream>
#include <ctime>
/**
 *	Name: StudentOwnedStates.cpp
 *
 *	Author: Reed Johnson
 *
 *	Date Modified: 9.16.2012
 *
 *	Description: Implements the definitions of all the various actions associated with the StudentOwnedStates.
 */
using std::cout;

//Returns the instance of the Sleep state
Sleep* Sleep::Instance()
{
	static Sleep instance;

	return &instance;
}

//Checks to see if the entity's location is home, and sends it home if the location is elsewhere.
void Sleep::Enter(Student* student)
{
	if(student->Location() != home)
	{
		std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Heading home!";
	
		student->ChangeLocation(home);
	}
}

//The entity sleeps. Once the entity has slept for 8 hours, they wake up and transition to the Eat state.
void Sleep::Execute(Student* student)
{
	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Zzzzzz";

	if(student->GetSleepTime() >= 8){
		student->GetFSM()->ChangeState(Eat::Instance());
	}
	student->SleepMore(); // Increments entity's sleep counter by 2. 
}

//The entity wakes up and exits sleep. Its sleep counter is reset to 0.  
void Sleep::Exit(Student* student)
{
	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Time to wake up!";

	student->resetSleep();
}

bool Sleep::OnMessage(Student* student, const Telegram&)
{
	return false;
}

//Returns an instance of the Eat state
Eat* Eat::Instance()
{
	static Eat instance;

	return &instance;
}

//The entity declares their intention to eat upon entering the Eat state
void Eat::Enter(Student* student)
{
	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Time to eat!";

}

//The entity eats food and exits to a new state depending on whether 
void Eat::Execute(Student* student)
{
	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Mmmm";

	if(student->TimeForWork()){
		student->GetFSM()->ChangeState(Work::Instance());
	} else if (student->TimeForClass()){
		student->GetFSM()->ChangeState(AttendClass::Instance());
	} else {
		student->GetFSM()->ChangeState(SpendFreeTime::Instance());
	}
}

//The entity announces how it enjoyed the food as it exits the Eat state. 
void Eat::Exit(Student* student)
{
	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "That was good food!";
}

bool Eat::OnMessage(Student* student, const Telegram&)
{
	return false;
}

//Return an instance of the SpendFreeTime state
SpendFreeTime* SpendFreeTime::Instance()
{
	static SpendFreeTime instance;
	
	return &instance;
}

//Entity spends free time at home. It checks to see if its current location is home and moves there if it isn't
void SpendFreeTime::Enter(Student* student)
{
	if(student->Location() != home){
		std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Heading home to enjoy my free time!";

		student->ChangeLocation(home);
	}
	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "I can't wait to read this book.";

	//See if wife wants to watch TV.
	Dispatch->DispatchMessage(0,	//time delay
							  student->ID(),	//Sender ID
							  ent_Amanda,		//Receiver ID
							  Msg_LetsWatchTV,	//Message
							  NULL);			//No additional info

}

//The entity spends its free time by reading a book. It determines whether it is time for work, class, or sleep
//and changes its state accordingly
void SpendFreeTime::Execute(Student* student)
{
	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Reading my book...";

	if(student->TimeForWork()){
		student->GetFSM()->ChangeState(Work::Instance());
	} else if(student->TimeForClass()){
		student->GetFSM()->ChangeState(AttendClass::Instance());
	} else if(student->TimeForSleep()){
		student->GetFSM()->ChangeState(Sleep::Instance());
	}
}

//The entity exits the state SpendFreeTime and announces how enjoyable it was.
void SpendFreeTime::Exit(Student* student)
{
	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Well, that was fun!";
}

bool SpendFreeTime::OnMessage(Student* student, const Telegram& msg)
{
	time_t currentTime = time(NULL);
	struct tm * displayTime = localtime(&currentTime);
	switch(msg.Msg)
	{
	case Msg_DoneWithTV:
		
		cout << "\nMessage handled by " << GetNameOfEntity(student->ID())
			<< " at time: " << asctime(displayTime);

		cout << "\n" << GetNameOfEntity(student->ID()) <<
			": Alright, I'll watch something now!";

		student->GetFSM()->ChangeState(WatchTV::Instance());

		return true;
	}
	return false;
}

//Returns the instance of the AttendClass state
AttendClass* AttendClass::Instance()
{
	static AttendClass instance;

	return &instance;
}

//The entity enters the AttendClass state. Checks if the entity is at school,
//and moves to school if it is not.
void AttendClass::Enter(Student* student)
{
	if(student->Location()){
		std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Headed to school to attend classes!";

		student->ChangeLocation(school);
	}

	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Time for class!";

}

//Entity takes notes until ClassIsOver is true, then determines whether it has to work, or has free time.
//The entity does not have night classes, so it should never have to switch to sleep state from AttendClass.
void AttendClass::Execute(Student* student)
{
	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Taking notes...";
	if(student->ClassIsOver()){
		if(student->TimeForWork()){
			student->GetFSM()->ChangeState(Work::Instance());
		} else {
			student->GetFSM()->ChangeState(SpendFreeTime::Instance());
		}
	}
}

//The entity announces how it is glad classes are over as it exits AttendClass state.
void AttendClass::Exit(Student* student)
{
	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Glad classes are over!";
}

bool AttendClass::OnMessage(Student* student, const Telegram&)
{
	return false;
}

//Returns the instance of the Work state.
Work* Work::Instance()
{
	static Work instance;

	return &instance;
}

//The entity prepares to enter the work state by determining whether or not its current location is work.
//If it is not at 'work', then it moves to that location.
void Work::Enter(Student* student)
{
	if(student->Location() != work){
		std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Heading to work!";
	
		student->ChangeLocation(work);
	}

	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Time to work!";
}

//The entity works until its internal counter of hoursworked has reached 8, then 
//determines whether it should enter SpendFreeTime, AttendClass, or Sleep
void Work::Execute(Student* student)
{
	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Working...";
	student->IncHoursWorked();
	if(student->GetHoursWorked() >= 8){
		if(student->TimeForClass()){
			student->GetFSM()->ChangeState(AttendClass::Instance());
		}else if(student->TimeForSleep()){
			student->GetFSM()->ChangeState(Sleep::Instance());
		} else { 
			student->GetFSM()->ChangeState(SpendFreeTime::Instance());
		}
	}
}

//The entity announces that it is glad work has ended before exiting the Work state
//Also returns the entity's hoursWorked to 0. 
void Work::Exit(Student* student)
{
	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "Glad work is over!";
	student->resetHoursWorked();
}

bool Work::OnMessage(Student* student, const Telegram&)
{
	return false;
}

//Returns the instance of the AttendClass state
WatchTV* WatchTV::Instance()
{
	static WatchTV instance;

	return &instance;
}

//The entity enters the watch TV state. 
void WatchTV::Enter(Student* student)
{

	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "I'll watch this show!";

}

//Entity watches TV for one cycle and returns to SpendFreeTime
void WatchTV::Execute(Student* student)
{
	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "I love this show...";
	
	student->GetFSM()->ChangeState(SpendFreeTime::Instance());
}

//The entity announces how it enjoyed the TV show as it exits the state. 
void WatchTV::Exit(Student* student)
{
	std::cout << "\n" << GetNameOfEntity(student->ID()) << ": " << "That was fun!";
}

bool WatchTV::OnMessage(Student* student, const Telegram&)
{
	return false;
}