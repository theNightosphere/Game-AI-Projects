#include "Student.h"
#include "EntityNames.h"
#include <Windows.h>
#include "WorldClock.h"
#include "StudentsWife.h"
int main()
{
	WorldClock clock;
	Student student(ent_Reed, &clock);
	StudentsWife wife(ent_Amanda, &clock);
	
	for(int i = 0; i < 50; i++){
		student.Update();
		wife.Update();
		clock.tick();
		Sleep(800);
	}

	return 0;
}