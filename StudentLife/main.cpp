#include "Student.h"
#include "EntityNames.h"
#include <Windows.h>
#include "WorldClock.h"
#include "StudentsWife.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include <ctime>
#include <iostream>
int main()
{
	WorldClock clock;
	Student* Reed = new Student(ent_Reed, &clock);
	StudentsWife* Amanda = new StudentsWife(ent_Amanda, &clock);

	//Put the student into the Entity Manager
	EntityMgr->RegisterEntity(Reed);
	//Put the student's wife into the Entity Manager
	EntityMgr->RegisterEntity(Amanda);
	
	//Seed random number generator
	srand((unsigned) time(NULL));

	for(int i = 0; i < 50; i++){
		Reed->Update();
		Amanda->Update();
		Dispatch->DispatchDelayedMessages();
		clock.tick();
		Sleep(800);
	}

	//Cleanup
	delete Reed;
	delete Amanda;

	char n;
	
	//Hold for key press before exiting
	std::cin >> n;

	return 0;
}