#pragma once
#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H
/**
 *	Name: MessageTypes.h
 *
 *	Author: Reed Johnson
 *
 *	Date Modified: 9.16.2012
 *
 *	Description: Enumerates the different message types that can be dispatched by entities in the simulation. 
 */
enum message_type
{
	Msg_LetsWatchTV,
	Msg_DoneWithTV
};

inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_LetsWatchTV:
    
    return "LetsWatchTV"; 

  case Msg_DoneWithTV:
    
    return "DoneWithTV";

  default:

    return "Not recognized!";
  }
}

#endif