#pragma once
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
/**
 *	Name: EntityManager.h
 *
 *	Author: Reed Johnson
 *
 *	Date Modified: 9.16.2012
 *
 *	Description: Provides an easy method to keep track of and get pointers to entities inside the simulation. 
 */
#include <cassert>
#include <map>
#include <string>

class BaseGameEntity;

class EntityManager
{
private:
	//Used to keep track of all the active entities in the simulation
	typedef std::map<int, BaseGameEntity*> EntityMap;

private:
	//To facilitate quick lookup the entities are stored in a std::map, in which the pointers
	//to entities are cross-referenced by their identifying number
	EntityMap	myEntityMap;

	EntityManager(){}

	//copy constructor and assignment should be private
	EntityManager(const EntityManager&);
	EntityManager& operator=(const EntityManager&);

public:

	static EntityManager* Instance();

	//this method stores a pointer to the entity in the std::vector
	//myEntities at the index position indicated by the entity's ID
	//(makes for faster access)
	void	RegisterEntity(BaseGameEntity* NewEntity);

	//returns a pointer to the entity with the ID given as a parameter
	BaseGameEntity* GetEntityFromID(int id)const;

	//this method removes the entity from the list
	void	RemoveEntity(BaseGameEntity* pEntity);
};

//proviades easy access to the instance of the EntityManager
#define EntityMgr EntityManager::Instance()

#endif

