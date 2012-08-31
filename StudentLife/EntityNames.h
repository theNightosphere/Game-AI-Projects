#pragma once
#ifndef NAMES_H
#define NAMES_H

#include <string>

/**
 *	Name: EntityNames.h
 *
 *	Author: Reed Johnson
 *
 *	Date Modified: 8.31.2012
 *
 *	Description: Enumerates the different entities and provides a method to get an entity's name as a string
 */

enum {
	ent_Reed,
	ent_Amanda
};

inline std::string GetNameOfEntity(int n)
{
	switch(n)
	{
	case ent_Reed:
		return "Reed";

	case ent_Amanda:
		return "Amanda";

	default:
		return "Unknown!";
	}
}

#endif