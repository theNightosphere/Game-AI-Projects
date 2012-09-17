#include "EntityManager.h"
#include "BaseGameEntity.h"
/**
 *	Name: EntityManager.cpp
 *
 *	Author: Reed Johnson
 *
 *	Date Modified: 9.16.2012
 *
 *	Description: Implements the definition of the method prototypes from EntityManger.h
 *				 Implementation taken directly from Mat Buckland's source in the file EntityManager.cpp from
 *				 the project WestWorldWithMessaging.
 */

EntityManager* EntityManager::Instance()
{
  static EntityManager instance;

  return &instance;
}

//------------------------- GetEntityFromID -----------------------------------
//-----------------------------------------------------------------------------
BaseGameEntity* EntityManager::GetEntityFromID(int id)const
{
  //find the entity
  EntityMap::const_iterator ent = myEntityMap.find(id);

  //assert that the entity is a member of the map
  assert ( (ent !=  myEntityMap.end()) && "<EntityManager::GetEntityFromID>: invalid ID");

  return ent->second;
}

//--------------------------- RemoveEntity ------------------------------------
//-----------------------------------------------------------------------------
void EntityManager::RemoveEntity(BaseGameEntity* pEntity)
{    
  myEntityMap.erase(myEntityMap.find(pEntity->ID()));
} 

//---------------------------- RegisterEntity ---------------------------------
//-----------------------------------------------------------------------------
void EntityManager::RegisterEntity(BaseGameEntity* NewEntity)
{
  myEntityMap.insert(std::make_pair(NewEntity->ID(), NewEntity));
}
