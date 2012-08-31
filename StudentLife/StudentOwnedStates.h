#pragma once
#ifndef	STUDENT_OWNED_STATES_H
#define	STUDENT_OWNED_STATES_H
/**
 *	Name: StudentOwnedStates.h
 *
 *	Date: 8.29.2012
 *
 *	Author: Reed Johnson
 *
 *	Description: A header file containing the various states a student may have.
 */

#include "State.h"

class Student;

//The entity sleeps until 8AM 
class Sleep : public State<Student>
{
private:
	Sleep(){}

	Sleep(const Sleep&);
	Sleep& operator=(const Sleep&);

public:
	//Class is a singleton
	static Sleep* Instance();

	virtual void Enter(Student* student);
	
	virtual void Execute(Student* student);

	virtual void Exit(Student* student);

};

//Entity eats food
class Eat: public State<Student>
{
private:
	Eat(){}

	Eat(const Eat&);
	Eat& operator=(const Sleep&);

public:
	static Eat* Instance();

	virtual void Enter(Student* student);

	virtual void Execute(Student* student);

	virtual void Exit(Student* student);

};

//The entity enjoys its free time by reading a book. 
class SpendFreeTime: public State<Student>
{
private:
	SpendFreeTime(){}

	SpendFreeTime(const SpendFreeTime&);
	SpendFreeTime& operator=(const SpendFreeTime&);
	
public:
	static SpendFreeTime* Instance();

	virtual void Enter(Student* student);

	virtual void Execute(Student* student);

	virtual void Exit(Student* student);

};

//The entity attends class. 
class AttendClass : public State<Student>
{
private:
	AttendClass(){}

	AttendClass(const AttendClass&);
	AttendClass& operator=(const AttendClass&);

public:
	static AttendClass* Instance();

	virtual void Enter(Student* student);

	virtual void Execute(Student* student);

	virtual void Exit(Student* student);
};

//The entity works at a job. 
class Work : public State<Student>
{
private:
	Work(){}

	Work(const Work&);
	Work& operator=(const Work&);

public:
	static Work* Instance();

	virtual void Enter(Student* student);

	virtual void Execute(Student* student);

	virtual void Exit(Student* student);
};

#endif

