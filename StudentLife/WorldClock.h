#pragma once
/**
 *	Name: WorldClock.h
 *
 *	Author: Reed Johnson
 *
 *	Date Modified: 8.30.2012
 *
 *	Description: Prototypes the WorldClock class which is used by the entities to keep track of time
 *				 and change their actions accordingly.
 */
class WorldClock
{
private:
	//Integer 0-6 corresponding to day of the week, starting with 0 on sunday
	int myDay;
	//Time of day, 0-23, 0 is 12AM. This value is always an hour.
	int myTime;
public:
	WorldClock(void);
	~WorldClock(void);

	void tick();
	int getDay() const { return myDay; }
	int getTime() const { return myTime; }
};

