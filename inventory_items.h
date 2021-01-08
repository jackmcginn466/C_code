#pragma once
#ifndef INVENTORY_ITEMS_HEADER
#define INVENTORY_ITEMS_HEADER

#include<string>

//forward declare dependencies
class players;

//Abstract base class (interface) for the different objects the players can have in their inventorys
class inventory_items
{
public:
    virtual void complete_effect(players*) = 0;
    virtual int get_number_in_inventory() = 0;
    virtual ~inventory_items() {}
    virtual std::string get_name() = 0;
};

#endif






