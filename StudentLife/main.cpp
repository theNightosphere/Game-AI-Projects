#include "Student.h"
#include "EntityNames.h"
#include <Windows.h>
#include "WorldClock.h"
int main()
{
	WorldClock clock;
	Student student(ent_Reed, &clock);
	
	for(int i = 0; i < 50; i++){
		student.Update();
		clock.tick();
		Sleep(800);
	}

	return 0;
}