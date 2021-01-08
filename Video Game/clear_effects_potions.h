#pragma once
#ifndef clear_effect_potion_HEADER
#define clear_effect_potion_HEADER

//forward declare dependencies
class players;
//include dependencies
#include "inventory_items.h"

//Derived class for a type of object you can have in an inventory - a clear effects potion
class clear_effects_potion :public inventory_items
{
private:
    int number_in_inventory{};
    double heal_amount{ 100 };
    std::string name{ "Stamina Potion" };
public:
    clear_effects_potion();
    clear_effects_potion(int);
    ~clear_effects_potion();
    //Completes the desired effects of the potion on the chosen player which is input by a pointer in to this member function
    void complete_effect(players*);
    int get_number_in_inventory();
    std::string get_name();
};

#endif

