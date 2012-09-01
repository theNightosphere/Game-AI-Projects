#pragma once
#ifndef	WIFE_OWNED_STATES
#define	WIFE_OWNED_STATES
/**
 *	Name: StudentsWifeOwnedStates.h
 *
 *	Date: 8.31.2012
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
}

//The entity sleeps until 8AM 
class Sleep : public State<StudentsWife>
{
private:
	Sleep(){}

	Sleep(const Sleep&);
	Sleep& operator=(const Sleep&);

public:
	//Class is a singleton
	static Sleep* Instance();

	virtual void Enter(StudentsWife* wife);
	
	virtual void Execute(StudentsWife* wife);

	virtual void Exit(StudentsWife* wife);

};

//Entity eats food
class Eat: public State<StudentsWife>
{
private:
	Eat(){}

	Eat(const Eat&);
	Eat& operator=(const Sleep&);

public:
	static Eat* Instance();

	virtual void Enter(StudentsWife* wife);

	virtual void Execute(StudentsWife* wife);

	virtual void Exit(StudentsWife* wife);

};

class SpendFreeTime: public State<StudentsWife>
{
private:
	SpendFreeTime(){}

	SpendFreeTime(const SpendFreeTime&);
	SpendFreeTime& operator=(const SpendFreeTime&);
	
public:
	static SpendFreeTime* Instance();

	virtual void Enter(StudentsWife* wife);

	virtual void Execute(StudentsWife* wife);

	virtual void Exit(StudentsWife* wife);

};

//The entity works at a job. 
class Work : public State<StudentsWife>
{
private:
	Work(){}

	Work(const Work&);
	Work& operator=(const Work&);

public:
	static Work* Instance();

	virtual void Enter(StudentsWife* wife);

	virtual void Execute(StudentsWife* wife);

	virtual void Exit(StudentsWife* wife);
};

class WaterPlants : public State<StudentsWife>
{
private:
	WaterPLants(){}

	WaterPlants(const WaterPlants&);
	WaterPlants& operator=(const WaterPlants&);
public:
	static WaterPLants& Instance();

	virtual void Enter(StudentsWife* wife);

	virtual void Execute(StudentsWife* wife);

	virtual void Exit(StudentsWife* wife);
}

#endif
