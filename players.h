#pragma once
#ifndef PLAYERS_HEADER
#define PLAYERS_HEADER
#include<memory>
#include<iostream>
//forward declare dependencies
class monsters;

//include dependencies
#include "Characters.h"

//Abstract base class for all the players you can use in the game
class players : public characters
{
public:
    //Overwrite output operator to display status of character when ouput
    friend std::ostream& operator<<(std::ostream& output, players& myobject);
    virtual ~players() {}
    virtual void fight_choice(const std::vector<std::shared_ptr<monsters>>*, const std::vector<std::shared_ptr<players>>*) = 0;
    virtual double get_stamina() = 0;
    virtual void choice_output() = 0;
    virtual void clear_active_effects() = 0;
    virtual void heal(double amount) = 0;
    virtual void heal_stamina(double amount) = 0;
};

//Overwriting output operator for players to display its status
inline std::ostream& operator<<(std::ostream& output, players& myobject)
{
    output << myobject.get_name() << " (HP: " << myobject.get_health() << " ST:" << myobject.get_stamina() << ", effects: ";
    //For loop runs through all the active effects on the player so they can all be output
    for (size_t i{}; i < (myobject.show_effects()).size(); i++) {
        output << myobject.show_effects()[i].first << " ";
    }
    output << ")";
    return output;
}

#endif




