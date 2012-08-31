#include "WorldClock.h"
/**
 *	Name: WorldClock.cpp
 *
 *	Author: Reed Johnson
 *
 *	Date Modified: 8.30.2012
 *
 *	Description: Implements the definitions of all the various actions associated with the WorldClock.
 */

WorldClock::WorldClock(void)
{
	myDay = 0;
	myTime = 0;
}


WorldClock::~WorldClock(void)
{
}

//Increments the world clock by 2 hours. If a new day has been reached (myTime == 0) then myDay is incremented.
//Use modulus to wrap time/day once they hit 24 and 7 respectively. 
void WorldClock::tick()
{
	myTime = (myTime + 2) % 24;

	if(myTime == 0){ myDay = (myDay + 1) % 7; }

}