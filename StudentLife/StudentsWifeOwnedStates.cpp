#include "StudentsWifeOwnedStates.h"
#include "State.h"
#include "EntityNames.h"
#include "Locations.h"
#include "StudentsWife.h"
#include <iostream>
#include <string>
/**
 *	Name: StudentsWifeOwnedStates.cpp
 *
 *	Author: Reed Johnson
 *
 *	Date Modified: 8.31.2012
 *
 *	Description: Implements the definitions of all the various actions associated with the StudentsWifeOwnedStates.
 */

WifesGlobalState* WifesGlobalState::Instance()
{
	static WifesGlobalState instance;

	return &instance;
}

//The entity randomly waters the plants. 1/10 chance. Will not water plants while at work or sleeping. 
void WifesGlobalState::Execute(StudentsWife* wife)
{
	if( rand() <= 1 ){
		if(!wife->GetFSM()->isInState(*WaterPlants::Instance()) && !wife->GetFSM()->isInState(*Work::Instance()) 
			&& !wife->GetFSM()->isInState(*Sleep::Instance())){
				wife->GetFSM()->ChangeState(WaterPlants::Instance());
		}
	}
}

//Returns the instance of the Sleep state
Sleep* Sleep::Instance()
{
	static Sleep instance;

	return &instance;
}

//Checks to see if the entity's location is home, and sends it home if the location is elsewhere.
void Sleep::Enter(StudentsWife* wife)
{
	if(wife->Location() != home)
	{
		std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Heading home!";
	
		wife->ChangeLocation(home);
	}
}

//The entity sleeps. Once the entity has slept for 8 hours, they wake up and transition to the Eat state.
void Sleep::Execute(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Zzzzzz";

	if(wife->GetSleepTime() >= 8){
		wife->GetFSM()->ChangeState(Eat::Instance());
	}
	wife->SleepMore(); // Increments entity's sleep counter by 2. 
}

//The entity wakes up and exits sleep. Its sleep counter is reset to 0.  
void Sleep::Exit(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Time to wake up!";

	wife->resetSleep();
}

//Returns an instance of the Eat state
Eat* Eat::Instance()
{
	static Eat instance;

	return &instance;
}

//The entity declares their intention to eat upon entering the Eat state
void Eat::Enter(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Time to eat!";

}

//The entity eats food and exits to a new state depending on whether 
void Eat::Execute(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Mmmm";

	if(wife->TimeForWork()){
		wife->GetFSM()->ChangeState(Work::Instance());
	} else {
		wife->GetFSM()->ChangeState(SpendFreeTime::Instance());
	}
}

//The entity announces how it enjoyed the food as it exits the Eat state. 
void Eat::Exit(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "That was good food!";
}

//Return an instance of the SpendFreeTime state
SpendFreeTime* SpendFreeTime::Instance()
{
	static SpendFreeTime instance;
	
	return &instance;
}

//Entity spends free time at home. It checks to see if its current location is home and moves there if it isn't
void SpendFreeTime::Enter(StudentsWife* wife)
{
	if(wife->Location() != home){
		std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Heading home to enjoy my free time!";

		wife->ChangeLocation(home);
	}
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "I can't wait to read this book.";

}

//The entity spends its free time by reading a book. It determines whether it is time for work, class, or sleep
//and changes its state accordingly
void SpendFreeTime::Execute(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Reading my book...";

	if(wife->TimeForWork()){
		wife->GetFSM()->ChangeState(Work::Instance());
	} else if(wife->TimeForSleep()){
		wife->GetFSM()->ChangeState(Sleep::Instance());
	}
}

//The entity exits the state SpendFreeTime and announces how enjoyable it was.
void SpendFreeTime::Exit(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Well, that was fun!";
}
