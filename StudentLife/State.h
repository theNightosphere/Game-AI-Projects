#pragma once
#ifndef STATE_H
#define STATE_H


template <class entity_type>
class State
{
public:
	State(){}
	virtual ~State(){}

	//This is executed when the state is entered.
	virtual void Enter(entity_type*)=0;

	//This is called by update function each update
	virtual void Execute(entity_type*)=0;

	//This is executed when the state is exited.
	virtual void Exit(entity_type*)=0;
};

#endif

