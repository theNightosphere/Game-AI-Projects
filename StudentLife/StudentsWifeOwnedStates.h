#pragma once
#ifndef	WIFE_OWNED_STATES
#define	WIFE_OWNED_STATES
/**
 *	Name: StudentsWifeOwnedStates.h
 *
 *	Date: 9.4.2012
 *
 *	Author: Reed Johnson
 *
 *	Description: A header file containing the various states a student's wife may have.
 */

#include "State.h"

class StudentsWife;

class WifesGlobalState : public State<StudentsWife>
{
private:
	WifesGlobalState(){}

	WifesGlobalState(const WifesGlobalState&);
	WifesGlobalState& operator=(const WifesGlobalState&);
public:
	//this class is a singleton
	static WifesGlobalState* Instance();

	virtual void Enter(StudentsWife* wife){}

	virtual void Execute(StudentsWife* wife);

	virtual void Exit(StudentsWife* wife){}
};

//The entity sleeps until 8AM 
class wSleep : public State<StudentsWife>
{
private:
	wSleep(){}

	wSleep(const wSleep&);
	wSleep& operator=(const wSleep&);

public:
	//Class is a singleton
	static wSleep* Instance();

	virtual void Enter(StudentsWife* wife);
	
	virtual void Execute(StudentsWife* wife);

	virtual void Exit(StudentsWife* wife);

};

//Entity eats food
class wEat: public State<StudentsWife>
{
private:
	wEat(){}

	wEat(const wEat&);
	wEat& operator=(const wEat&);

public:
	static wEat* Instance();

	virtual void Enter(StudentsWife* wife);

	virtual void Execute(StudentsWife* wife);

	virtual void Exit(StudentsWife* wife);

};

class wSpendFreeTime: public State<StudentsWife>
{
private:
	wSpendFreeTime(){}

	wSpendFreeTime(const wSpendFreeTime&);
	wSpendFreeTime& operator=(const wSpendFreeTime&);
	
public:
	static wSpendFreeTime* Instance();

	virtual void Enter(StudentsWife* wife);

	virtual void Execute(StudentsWife* wife);

	virtual void Exit(StudentsWife* wife);

};

//The entity works at a job. 
class wWork : public State<StudentsWife>
{
private:
	wWork(){}

	wWork(const wWork&);
	wWork& operator=(const wWork&);

public:
	static wWork* Instance();

	virtual void Enter(StudentsWife* wife);

	virtual void Execute(StudentsWife* wife);

	virtual void Exit(StudentsWife* wife);
};

class wWaterPlants : public State<StudentsWife>
{
private:
	wWaterPlants(){}

	wWaterPlants(const wWaterPlants&);
	wWaterPlants& operator=(const wWaterPlants&);
public:
	static wWaterPlants* Instance();

	virtual void Enter(StudentsWife* wife);

	virtual void Execute(StudentsWife* wife);

	virtual void Exit(StudentsWife* wife);
};

#endif
