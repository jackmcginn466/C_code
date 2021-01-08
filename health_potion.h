#pragma once
#ifndef health_potion_HEADER
#define health_potion_HEADER

//forward declare dependencies
class players;
//include dependencies
#include "inventory_items.h"

//Derived class for a type of object you can have in an inventory - a health potion
class health_potion :public inventory_items
{
private:
    int number_in_inventory{};
    double heal_amount{ 100 };
    std::string name{ "Health Potion" };
public:
    health_potion();
    health_potion(int);
    ~health_potion();
    //Completes the desired effects of the potion on the chosen player which is input by a pointer in to this member function
    void complete_effect(players*);
    int get_number_in_inventory();
    std::string get_name();
};


#endif

