#pragma once
#ifndef	WIFE_OWNED_STATES
#define	WIFE_OWNED_STATES
/**
 *	Name: StudentsWifeOwnedStates.h
 *
 *	Date: 9.16.2012
 *
 *	Author: Reed Johnson
 *
 *	Description: A header file containing the various states a student's wife may have.
 */

#include "State.h"
#include "MessageDispatcher.h"

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
	virtual bool OnMessage(StudentsWife* wife, const Telegram& msg);

	virtual void Enter(StudentsWife* wife){}

	virtual void Execute(StudentsWife* wife);

	virtual void Exit(StudentsWife* wife){}
<<<<<<< HEAD

=======
>>>>>>> 5b25a19e9fc4ea4677fc543e5700084e73fe6282
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

	virtual bool OnMessage(StudentsWife* wife, const Telegram& msg);

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

	virtual bool OnMessage(StudentsWife* wife, const Telegram& msg);
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

	virtual bool OnMessage(StudentsWife* wife, const Telegram& msg);
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

	virtual bool OnMessage(StudentsWife* wife, const Telegram& msg);
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
<<<<<<< HEAD

	virtual bool OnMessage(StudentsWife* wife, const Telegram& msg);
};

class wWatchTV : public State<StudentsWife>
{
private:
	wWatchTV(){}

	wWatchTV(const wWatchTV&);
	wWatchTV& operator=(const wWatchTV&);
public:
	static wWatchTV* Instance();

	virtual void Enter(StudentsWife* wife);

	virtual void Execute(StudentsWife* wife){}

	virtual void Exit(StudentsWife* wife);

	virtual bool OnMessage(StudentsWife* wife, const Telegram& msg);
=======
>>>>>>> 5b25a19e9fc4ea4677fc543e5700084e73fe6282
};

#endif
