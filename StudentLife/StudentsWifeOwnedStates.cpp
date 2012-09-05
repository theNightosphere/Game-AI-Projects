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
	if( rand()%10 <= 5 ){
		if(!wife->GetFSM()->isInState(*wWaterPlants::Instance()) && !wife->GetFSM()->isInState(*wWork::Instance()) 
			&& !wife->GetFSM()->isInState(*wSleep::Instance())){
				wife->GetFSM()->ChangeState(wWaterPlants::Instance());
		}
	}
}

wSleep* wSleep::Instance()
{
	static wSleep instance;

	return &instance;
}

//Checks to see if the entity's location is home, and sends it home if the location is elsewhere.
void wSleep::Enter(StudentsWife* wife)
{
	if(wife->Location() != home)
	{
		std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Heading home!";
	
		wife->ChangeLocation(home);
	}
}

//The entity sleeps. Once the entity has slept for 8 hours, they wake up and transition to the Eat state.
void wSleep::Execute(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Zzzzzz";

	if(wife->GetSleepTime() >= 8){
		wife->GetFSM()->ChangeState(wEat::Instance());
	}
	wife->SleepMore(); // Increments entity's sleep counter by 2. 
}

//The entity wakes up and exits sleep. Its sleep counter is reset to 0.  
void wSleep::Exit(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Time to wake up!";

	wife->resetSleep();
}

wEat* wEat::Instance()
{
	static wEat instance;

	return &instance;
}

//The entity declares their intention to eat upon entering the Eat state
void wEat::Enter(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Time to eat!";

}

//The entity eats food and exits to a new state depending on whether 
void wEat::Execute(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Mmmm";

	if(wife->TimeForWork()){
		wife->GetFSM()->ChangeState(wWork::Instance());
	} else {
		wife->GetFSM()->ChangeState(wSpendFreeTime::Instance());
	}
}

//The entity announces how it enjoyed the food as it exits the Eat state. 
void wEat::Exit(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "That was good food!";
}

wSpendFreeTime* wSpendFreeTime::Instance()
{
	static wSpendFreeTime instance;

	return &instance;
}

//Entity spends free time at home. It checks to see if its current location is home and moves there if it isn't
void wSpendFreeTime::Enter(StudentsWife* wife)
{
	if(wife->Location() != home){
		std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Heading home to enjoy my free time!";

		wife->ChangeLocation(home);
	}
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "I can't wait to read this book.";

}

//The entity spends its free time by reading a book. It determines whether it is time for work, class, or sleep
//and changes its state accordingly
void wSpendFreeTime::Execute(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Reading my book...";

	if(wife->TimeForWork()){
		wife->GetFSM()->ChangeState(wWork::Instance());
	} else if(wife->TimeForSleep()){
		wife->GetFSM()->ChangeState(wSleep::Instance());
	}
}

//The entity exits the state SpendFreeTime and announces how enjoyable it was.
void wSpendFreeTime::Exit(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Well, that was fun!";
}

wWork* wWork::Instance()
{
	static wWork instance;

	return &instance;
}

//Entity enters the wWork state. 
void wWork::Enter(StudentsWife* wife)
{
	if(wife->Location() != work){
		std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Heading to work!";

		wife->ChangeLocation(work);
	}
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Time to start working.";

}

//The entity Works for 8 hours. Amount of hours worked is incremented by 2 each time Execute is called
void wWork::Execute(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Working...";
	wife->IncHoursWorked();
	if(wife->GetHoursWorked() >= 8){
		wife->GetFSM()->ChangeState(wSpendFreeTime::Instance());
	}
	
}

//The entity exits the state Work and announces how they're glad it is over.
void wWork::Exit(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "I'm glad work is over!";
	wife->resetHoursWorked();
}

wWaterPlants* wWaterPlants::Instance()
{
	static wWaterPlants instance;

	return &instance;

}

//Entity enters the Work state. 
void wWaterPlants::Enter(StudentsWife* wife)
{

	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Time to water the plants!";

}

//The entity waters some plants and then returns to its previous state. 
void wWaterPlants::Execute(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Watering the plants...";

	wife->GetFSM()->RevertToPreviousState();

}

//The entity exits the state Work and announces how they're glad it is over.
void wWaterPlants::Exit(StudentsWife* wife)
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "The plants are looking healthy!";
}