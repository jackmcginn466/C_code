#pragma once
#ifndef MONSTERS_HEADER
#define MONSTERS_HEADER

#include<memory>
#include<iostream>

//forward declare dependencies
class players;
//include dependencies
#include "Characters.h"

//Abstract base class derived from characters for all the monsters you can meet in the game 
class monsters :public characters
{
public:
    //Overwrite output operator to display status of monster when ouput
    friend std::ostream& operator<<(std::ostream& output, monsters& myobject);
    virtual ~monsters() {}
    virtual void fight(const std::vector<std::shared_ptr<players>>*) = 0;
};

//Overwriting output operator for monsters to display its status
inline std::ostream& operator<<(std::ostream& output, monsters& myobject)
{
    output << myobject.get_name() << " (HP: " << myobject.get_health() << ", effects: ";
    //For loop runs through all the active effects on the player so they can all be output
    for (size_t i{}; i < (myobject.show_effects()).size(); i++) {
        output << myobject.show_effects()[i].first << " ";
    }
    output << ")";
    return output;
}
#endif




