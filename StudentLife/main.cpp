#include "Student.h"
#include "EntityNames.h"
#include <Windows.h>
#include "WorldClock.h"
#include "StudentsWife.h"
<<<<<<< HEAD
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
=======
int main()
{
	WorldClock clock;
	Student student(ent_Reed, &clock);
	StudentsWife wife(ent_Amanda, &clock);
>>>>>>> 5b25a19e9fc4ea4677fc543e5700084e73fe6282
	
	//Seed random number generator
	srand((unsigned) time(NULL));

	for(int i = 0; i < 50; i++){
<<<<<<< HEAD
		Reed->Update();
		Amanda->Update();

		Dispatch->DispatchDelayedMessages();

=======
		student.Update();
		wife.Update();
>>>>>>> 5b25a19e9fc4ea4677fc543e5700084e73fe6282
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