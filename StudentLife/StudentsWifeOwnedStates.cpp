#include "StudentsWifeOwnedStates.h"
#include "State.h"
#include "EntityNames.h"
#include "Locations.h"
#include "StudentsWife.h"
#include "MessageTypes.h"
#include "MessageDispatcher.h"
#include <iostream>
#include <ctime>
#include <string>

using std::cout;
/**
 *	Name: StudentsWifeOwnedStates.cpp
 *
 *	Author: Reed Johnson
 *
 *	Date Modified: 9.24.2012
 *
 *	Description: Implements the definitions of all the various actions associated with the StudentsWifeOwnedStates.
 */

WifesGlobalState* WifesGlobalState::Instance()
{
	static WifesGlobalState instance;

	return &instance;
}
//Determines how the wife Handles message in her global state. She doesn't. 
bool WifesGlobalState::OnMessage(StudentsWife* wife, const Telegram& msg)
{
	
	return false;
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

<<<<<<< HEAD
bool wSleep::OnMessage(StudentsWife* wife, const Telegram& msg)
{
	return false;
}

=======
>>>>>>> 5b25a19e9fc4ea4677fc543e5700084e73fe6282
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

<<<<<<< HEAD
bool wEat::OnMessage(StudentsWife* wife, const Telegram& msg)
{
	return false;
}

wSpendFreeTime* wSpendFreeTime::Instance()
{
=======
wSpendFreeTime* wSpendFreeTime::Instance()
{
>>>>>>> 5b25a19e9fc4ea4677fc543e5700084e73fe6282
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
<<<<<<< HEAD
{
	std::cout << "\n" << GetNameOfEntity(wife->ID()) << ": " << "Done reading my book!";
}

//If the entity is at home spending free time, she handles message by deciding to watch tv. 
bool wSpendFreeTime::OnMessage(StudentsWife* wife, const Telegram& msg)
{
	switch(msg.Msg)
	{
	case Msg_LetsWatchTV:
		{
			time_t currentTime = time(NULL);
			struct tm * displayTime = localtime( &currentTime);
			cout << "\nMessage handled by " << GetNameOfEntity(wife->ID())
				 << " at time: " << asctime(displayTime);
			cout << "\n" << GetNameOfEntity(wife->ID()) <<
				": I'm going to watch some TV...";

			wife->GetFSM()->ChangeState(wWatchTV::Instance());
		}

		return true;

	}

	return false;
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

bool wWork::OnMessage(StudentsWife* wife, const Telegram& msg)
=======
>>>>>>> 5b25a19e9fc4ea4677fc543e5700084e73fe6282
{
	return false;
}

<<<<<<< HEAD
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

bool wWaterPlants::OnMessage(StudentsWife* wife, const Telegram& msg)
{
	return false;
}

wWatchTV* wWatchTV::Instance()
{
	static wWatchTV instance;

	return &instance;
}

void wWatchTV::Enter(StudentsWife* wife)
{
	//if not already watching TV, start watching
	if(!wife->WatchingTV())
	{
		cout << "\n" << GetNameOfEntity(wife->ID())
			 << ": Turning on the TV!";

		//send a delayed message to myself so that I know when to stop watching TV
		Dispatch->DispatchMessage(1,		//Time delay
								  wife->ID(), //sender ID
								  wife->ID(), //receiver ID
								  Msg_DoneWithTV, //The message
								  0);	//No additional info

		wife->setWatchingTV(true);
	}
}

void wWatchTV::Exit(StudentsWife* wife)
{
	cout << "\nBetter get back to something else!";
}

bool wWatchTV::OnMessage(StudentsWife* wife, const Telegram& msg)
{
	switch(msg.Msg)
	{
	case Msg_DoneWithTV:
		{
		time_t currentTime = time(NULL);
		struct tm * displayTime = localtime( &currentTime );
		cout << "\nMessage received by " << GetNameOfEntity(wife->ID()) <<
			" at time: " << asctime(displayTime);
		cout << "\n" << GetNameOfEntity(wife->ID()) << ": That was fun!";

		//Tell husband we're done watching TV
		Dispatch->DispatchMessage(0, wife->ID(),
								  ent_Reed,
								  Msg_DoneWithTV,
								  0);

		wife->setWatchingTV(false);

		wife->GetFSM()->ChangeState(wSpendFreeTime::Instance());
		}
	}
	return false;
=======
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
>>>>>>> 5b25a19e9fc4ea4677fc543e5700084e73fe6282
}